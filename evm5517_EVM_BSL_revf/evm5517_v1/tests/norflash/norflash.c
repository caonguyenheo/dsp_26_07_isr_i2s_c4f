/* 
 * Copyright (c) 2012 Texas Instruments Incorporated.  
 * Except for those rights granted to you in your license from TI, all rights
 * reserved.
 *
 * Software License Agreement
 * Texas Instruments (TI) is supplying this software for use solely and
 * exclusively on TI devices. The software is owned by TI and/or its suppliers,
 * and is protected under applicable patent and copyright laws.  You may not
 * combine this software with any open-source software if such combination
 * would cause this software to become subject to any of the license terms
 * applicable to such open source software.

 * THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
 * NO WARRANTIES APPLY TO THIS SOFTWARE, WHETHER EXPRESS, IMPLIED OR STATUTORY.
 * EXAMPLES OF EXCLUDED WARRANTIES ARE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE AND WARRANTIES OF NON-INFRINGEMENT,
 * BUT ALL OTHER WARRANTY EXCLUSIONS ALSO APPLY. FURTHERMORE, TI SHALL NOT,
 * UNDER ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, CONSEQUENTIAL
 * OR PUNITIVE DAMAGES, FOR ANY REASON WHATSOEVER.
 */


#include "norflash.h"
#include "evm5517_emif.h"
#include "evm5517.h"
#include "stdio.h"

#if(0)
static Uint32 device_flash_pages = 128;
static Uint32 device_flash_page_length = 0x20000;
static Uint32 device_flash_page_len_pow2 = 17;

/* INTEL_MICRON */
static Int32 device_page_alignment = 0;


Uint32 NorFlashBaseAddr = 0x400000 ;
#endif

/*
 *
 *  norflash_init( )
 *
 *      Setup Flash
 *
 */
Int16 norflash_init( )
{
	Int16 i;
	
	/* Reset Counter value */
	SYS_PRCNTR = 0x020;
	/* Reset all Modules */
	SYS_PRCNTRLR = 0x00fb;
	for(i=0; i<50; i++);
	
	/* Config EMIF - ASYNC-Wait Config Regsiters */
	EMIF_AWCCR1 = 0x0080;
	EMIF_AWCCR2  = 0x00E4;
	return 0;
}

/*
 *
 *  _FLASH_unlockBlocks( )
 *
 *      Flash unlock blocks ( Intel/Micron Flash )
 *
 */
Int16 _FLASH_unlockBlocks( Uint32 start, Uint32 length )
{
    Uint32 end = start + length - 1;
    Uint32 addr;
    volatile Uint16 *pblock;
    for ( addr = start ; addr <= end ; addr = _FLASH_nextPage( addr ) )
    {
        #if(1)
            pblock = ( volatile Uint16* )addr;
            *pblock = FLASH_CONFIG_BLOCK_LOCK_BITS;     // Lock Setup
            *pblock = FLASH_CLEAR_LOCK_BITS;            // Unlock Confirm
            *pblock = FLASH_READ_ARRAY;                 // Read Mode
        #else
            do /* Optional unlock + check */
            {
                pblock = ( volatile Uint16* )addr;
                *pblock = FLASH_CONFIG_BLOCK_LOCK_BITS; // Lock Setup
                *pblock = FLASH_CLEAR_LOCK_BITS;        // Lock Confirm
                *pblock = FLASH_READ_ID;                // Read Device ID
                pblock = ( volatile Uint16* )( addr + 2 );// Read Status
            } while ( ( *pblock & 0x03 ) != 0 );
            *pblock = FLASH_READ_ARRAY;                 // Read Mode
            *pblock = FLASH_CLEAR_STATUS;               // Clear status reg
        #endif
    }
    return 0;
}

/*
 *
 *  _FLASH_waitWhileBusy( )
 * 
 *      Wait for the Busy bit
 *
 */
Int16 _FLASH_waitWhileBusy( Uint32 timeout )
{
	Int16 status;
    Uint16 flashstatus;

    /* Poll status register until device ready.  Status register looks like
     * Bit 7 Device Ready (0=busy, 1=ready)
     * Bit 6 Erase Suspend Status (0=no suspend, 1=suspend)
     * Bit 5 Erase Status (0=success, 1=fail)
     * Bit 4 Program Status (0=success, 1=fail)
     * Bit 3 Write Buffer Abort (0=not aborted, 1=aborted)
     * Bit 2 Program Suspend Status (0=no suspend, 1=suspend)
     * Bit 1 Sector Lock Status (0=not locked, 1=locked)
     * Bit 0 Reserved
     */
     
    status = 0;
    flashstatus = 0;
    while(1)
    {
        ((volatile unsigned short*)FLASH_BASE)[0x555] = 0x70;  // Enter read status mode
        flashstatus = FLASH_BASE_PTR16;
        if (flashstatus & 0x80)
            break;
    }
    
    /* Check status */
    if (flashstatus & 0x20)
    {
        printf("Erase fail\n");
        status = -1;
    }
    if (flashstatus & 0x10)
    {
        printf("Program fail\n");
        status = -1;
    }
    if (flashstatus & 0x02)
    {
        printf("Sector locked\n");
        status = -1;
    }
 
    FLASH_BASE_PTR16 = 0xf0;  // Go back to normal read mode
 
	return status;
}




/*
 *
 *  _FLASH_getId( )
 *
 *      Read Flash IDs
 *
 */
Uint16 _FLASH_getId( Uint16* id)
{
    // Reset Flash Command
    ((volatile unsigned short*)FLASH_BASE)[0] = 0xf0;
    
    // Read Flash ID Command
    ((volatile unsigned short*)FLASH_BASE)[0x555] = 0xaa;
    ((volatile unsigned short*)FLASH_BASE)[0x2AA] = 0x55;
    ((volatile unsigned short*)FLASH_BASE)[0x555] = 0x90;
    
    // Read Flash IDs
    id[0] = *(volatile unsigned short *)FLASH_BASE;
    id[1] = *((volatile unsigned short *)FLASH_BASE + 0x1);
    id[2] = *((volatile unsigned short *)FLASH_BASE + 0xe);
    id[3] = *((volatile unsigned short *)FLASH_BASE + 0xf);
    
    // Reset Flash Command
    ((volatile unsigned short*)FLASH_BASE)[0] = 0xf0;
}

Uint32 erase_timeout = 0x10000000;

/*
 *
 *  norflash_erase( start, length )
 *      Erase Flash containing address ( start ) to ( start + length ).
 *      Flash can only erase entire blocks containing the range.
 *
 *      start  <- starting address
 *      length <- length in bytes
 *
 */
Int16 norflash_erase( Uint32 start, Uint32 length )
{
    Uint32 addr;
    Uint32 end;
    volatile Uint16 *addr16;

    end = start + length - 1;                   // Calculate end of range
    start &= 0xFFFFFFFE;                        // Align to 16-bit words

    /*
     *  Erase each Flash block in the range
     */
//    _FLASH_unlockBlocks(start, length);
    for ( addr = start ; addr <= end ; addr = _FLASH_nextPage( addr ) )
    {
        addr16 = ( volatile Uint16* )addr;
        
        // Clear status register
        ((volatile unsigned short*)FLASH_BASE)[0x555] = 0x71;

        // Erase Flash Sector Command
        ((volatile unsigned short*)FLASH_BASE)[0x555] = 0xaa;
        ((volatile unsigned short*)FLASH_BASE)[0x2AA] = 0x55;
        ((volatile unsigned short*)FLASH_BASE)[0x555] = 0x80;
        ((volatile unsigned short*)FLASH_BASE)[0x555] = 0xaa;
        ((volatile unsigned short*)FLASH_BASE)[0x2AA] = 0x55;
        *addr16 = 0x30;
               
        if ( _FLASH_waitWhileBusy( erase_timeout ) )
        {
            *((volatile unsigned short*)FLASH_BASE) = 0xf0;  // Read mode
            return -1;                      // Timeout/Error occured
        }
    }
    *((volatile unsigned short*)FLASH_BASE) = 0xf0;  // Read mode
    return 0;
}



Uint32 write_timeout = 0x00020000;

/*
 *
 *  norflash_write( src, dst, length )
 *      Write to Flash address [dst] the data at a non-Flash address [src]
 *      for [length] #bytes.
 *
 *      src     <- source address
 *      dest    <- destination address
 *      length  <- length in bytes
 *
 */
Int16 norflash_write( Uint32 src, Uint32 dst, Uint32 length )
{
    Uint32 i;
    Uint16* psrc16;
    Uint16* pdst16;
    Uint16 word_to_write = 0;

    /*
     *  Align to 8 or 16 bits
     */
    psrc16 = ( Uint16* )src;
    pdst16 = ( Uint16* )dst;
    length &= 0xFFFFFFFE;

    for ( i = 0 ; i < length ; i += 2 )
    {
        /* Program one 16-bit word */
        ((volatile unsigned short*)FLASH_BASE)[0x555] = 0xaa;
        ((volatile unsigned short*)FLASH_BASE)[0x2AA] = 0x55;
        ((volatile unsigned short*)FLASH_BASE)[0x555] = 0xa0;
//        *pdst16 = FLASH_WORD_PROGRAM;
        *pdst16 = *psrc16++;

        /* Wait for operation to complete */
        if ( _FLASH_waitWhileBusy( write_timeout ) )
            return -1;
        EVM5517_waitusec( 100 );
        pdst16++;
    }
    return 0;
}


/*
 *
 *  _FLASH_getPageLength( )
 *
 *      What is the page Length?
 *
 */
Int32 _FLASH_getPageLength( )
{
    return 0x10000;
}

/*
 *
 *  _FLASH_nextPage( )
 * 
 *      Get Next Page of Flash.  This is only used b/c the Intel Flash being
 *      contains 4 smaller pages in the TOP or BOTTOM page.  This breaks
 *      the assumption that each page is the same size, thus we need to
 *      compute what the next page is.
 *
 */
Uint32 _FLASH_nextPage( Uint32 addr )
{
    Uint32 flash_offset;        // Offset in Flash
    Uint32 flash_major_page;    // Full size page
    Uint32 flash_minor_page;    // Quarter size page

    /* Go to first page */
    if ( addr < FLASH_BASE )
        return FLASH_BASE;

    /* Last Page, no where left to go */
    if ( addr >= FLASH_END_OR_RANGE )
        return FLASH_END_OR_RANGE;

    /* Compute offset and page */
    flash_offset = addr - FLASH_BASE;
    flash_major_page = flash_offset >> FLASH_PAGESIZE_POW2;
    addr = FLASH_BASE + (flash_major_page + 1) * FLASH_PAGESIZE;

    return addr;
}

/*
 *
 *  norflash_read( src, dst, length )
 *      Read from Flash address ( src ) to the data at non-Flash address
 *      ( dst ) for ( length ) bytes.
 *
 *      src     <- source address
 *      dest    <- destination address
 *      length  <- length in bytes
 *
 */
Int16 norflash_read( Uint32 src, Uint32 dst, Uint32 length )
{
    Uint32 i;
    Uint16* psrc16 = ( Uint16* )src;
    Uint16* pdst16 = ( Uint16* )dst;

    /*
     *  Set to Read Mode
     */
    *((volatile unsigned short*)FLASH_BASE) = 0xf0;  // Read mode

    /*
     *  Read Data to Buffer
     */
    for ( i = 0 ; i < length ; i += 2 )
        *pdst16++ = *psrc16++;

    return 0;
}


/*
 *
 *  norflash_checksum( start, length )
 *      Compute the checksum from ( start ) to ( start + length ).  The
 *      checksum is a 32-bit cumulative sum of each 8-bit byte in the
 *      range.
 *
 *      start  <- starting address
 *      length <- length in bytes
 *
 */
Uint32 norflash_checksum( Uint32 start, Uint32 length )
{
    Uint32 i;
    Uint32 checksum32 = 0;
    Uint8* ptr = ( Uint8* )start;

    /*
     *  Set to Read Mode
     */
    *((volatile unsigned short*)FLASH_BASE) = 0xf0;  // Read mode

    /*
     *  Compute Checksum by adding each byte up
     */
    for ( i = 0 ; i < length ; i++ )
        checksum32 += *ptr++;

    return checksum32;
}

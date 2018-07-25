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


#include "evm5517.h"
#include "spiflash.h"
#include "stdio.h"

static Uint8 spirombuf[spiflash_PAGESIZE + 8];
static Uint8 statusbuf[8];


/*
 *  spirom_init( )
 */
void spirom_init( )
{
	Int16 i;
	/* Reset Counter value */
	SYS_PRCNTR = 0x04;
	
	/* Reset SPI Module */
	SYS_PRCNTRLR = 0x00ff;
	for(i=0;i<100;i++) {;}
	/* Enable SPICLK,RX,TX & CS0 */
	SYS_EXBUSSEL =(0x5<<12);

	//SPI init
	SPI_SPICC2 =   (0<<15); // Reset SPI
    SPI_SPICC1 =   0x0031;  // 2MHz input clock
    SPI_SPIDC1 =   0x0000;
    SPI_SPICR2 &= ~0x30F8;  // Enable CS0
    SPI_SPICR2 |=  0x0038;  // Set word length as 1-byte
    SPI_SPICC2 =   (1<<15); // Enable SPI
	while((SPI_SPISR1 & 0x0001) != 0) {}; // Wait for SPI ready
	
//	spirom_status_set( 0xc3 );  // Clear Block Protection
	
    return;
}

/*
 *  spirom_cycle(buf, len)
 *
 *  Execute a SPI spirom data transfer cycle.  Each byte in buf is shifted 
 *  out and replaced with data coming back from the spirom.
 */

void spirom_cycle(Uint8 *buf, Uint16 len)
{
    Uint16 i;

    SPI_SPICR1 = 0x0000 | len - 1;
    i = SPI_SPIDR2;  // Dummy read

   	/* Spirom access cycle */
	for (i = 0; i < len; i++)
	{
		SPI_SPIDR2 = buf[i] << 8;
		SPI_SPIDR1 = 0x0000;
        SPI_SPICR2 = 0x0039;  //  8-bit words, read
        while((SPI_SPISR1 & 0x0002) == 0) {};
        buf[i] = SPI_SPIDR2 & 0xff;
	}
	
	/* Wait for transfer to complete */
	while((SPI_SPISR1 & 0x0001) != 0) {};
	
//	EVM5517_waitusec(100);
}

/*
 *  spirom_status( )
 */
Uint16 spirom_status( )
{
    /* Issue read status command */
    statusbuf[0] = spiflash_CMD_RDSR;
    statusbuf[1] = 0;

	spirom_cycle(statusbuf, 5);

    return statusbuf[3];
}

/*
 *  spirom_status_set( val )
 */
Uint16 spirom_status_set( Uint8 val)
{
    /* Issue read status command */
    statusbuf[0] = spiflash_CMD_WRSR;
    statusbuf[1] = val;
    
	spirom_cycle(statusbuf, 2);

    return statusbuf[3];
}

/*
 *  spirom_read( src, dst, len )
 */
void spirom_read( Uint32 src, Uint32 dst, Uint32 length )
{
    Int32 i;
    Uint8 *psrc, *pdst;

	// Setup command
    spirombuf[0] = spiflash_CMD_READ;
    spirombuf[1] = ( src >> 16);
    spirombuf[2] = ( src >> 8 );
    spirombuf[3] = ( src >> 0 );

	// Execute spirom read cycle
	spirom_cycle(spirombuf, length + 6);

    // Copy returned data
    pdst = ( Uint8 * )dst;
    psrc = spirombuf + 6;
    for ( i = 0 ; i < length ; i++ )
        *pdst++ = *psrc++;

}

/*
 *  spiflash_erase( base, len )
 */
void spiflash_erase( Uint32 base, Uint32 length )
{
    Int32 bytes_left, bytes_to_erase, eraseaddr;

    eraseaddr = base;
    bytes_left = length;

    while (bytes_left > 0 )
    {
        // Limit erase unit to sector size
	    bytes_to_erase = bytes_left;
		if (bytes_to_erase > spiflash_SECTORSIZE)
		    bytes_to_erase = spiflash_SECTORSIZE;

        // Align to sector boundaries
        if ((eraseaddr & spiflash_SECTORSIZE) != ((eraseaddr + bytes_to_erase) & spiflash_SECTORMASK))
            bytes_to_erase -= (eraseaddr + bytes_to_erase) - ((eraseaddr + bytes_to_erase) & spiflash_SECTORMASK);

        // Issue WPEN
        spirombuf[0] = spiflash_CMD_WREN;
        spirom_cycle(spirombuf, 1);

#if(1)
        // Issue sector unprotect
        spirombuf[0] = spiflash_CMD_UNPROTECTSEC;
        spirombuf[1] = ( Uint8 )( eraseaddr >> 16 );
        spirombuf[2] = ( Uint8 )( eraseaddr >> 8 );
        spirombuf[3] = ( Uint8 )( eraseaddr );
        spirom_cycle(spirombuf, 4);
#endif
        // Issue WPEN
        spirombuf[0] = spiflash_CMD_WREN;
        spirom_cycle(spirombuf, 1);
        
        // Issue erase
        spirombuf[0] = spiflash_CMD_ERASESEC;
        spirombuf[1] = ( Uint8 )( eraseaddr >> 16 );
        spirombuf[2] = ( Uint8 )( eraseaddr >> 8 );
        spirombuf[3] = ( Uint8 )( eraseaddr );
        spirom_cycle(spirombuf, 4);

        /* Wait while busy */
        while( ( spirom_status( ) & 0x01 ) );

        /* Get ready for next iteration */
        bytes_left -= bytes_to_erase;
        eraseaddr += bytes_to_erase;
    }
}

/* 
 *  spirom_write( src, dst, len )
 */
void spirom_write( Uint32 src, Uint16 dst, Uint32 length )
{
    Int32 i;
    Int32 bytes_left;
    Int32 bytes_to_program;
    Uint16 *psrc;

    /* Establish source */
    psrc = ( Uint16 * )src;
    bytes_left = length;

    while ( bytes_left > 0 )
    {
        bytes_to_program = bytes_left;

        /* Most to program is spirom_CMD_BLOCKSIZE */
        if ( bytes_to_program > spiflash_PAGESIZE )
             bytes_to_program = spiflash_PAGESIZE;

        /* Make sure you don't run off the end of a block */
        if ( ( dst & spiflash_PAGEMASK ) != ( ( dst + bytes_to_program ) & spiflash_PAGEMASK ) )
            bytes_to_program -= ( dst + bytes_to_program ) - ( ( dst + bytes_to_program ) & spiflash_PAGEMASK );

        /* Issue WPEN */
        spirombuf[0] = spiflash_CMD_WREN;
        spirom_cycle(spirombuf, 1);

        /* Create command block for program operation */
        spirombuf[0] = spiflash_CMD_WRITE;
        spirombuf[1] = ( Uint8 )( dst >> 16 );
        spirombuf[2] = ( Uint8 )( dst >> 8 );
        spirombuf[3] = ( Uint8 )( dst );


        for ( i = 0 ; i < bytes_to_program ; i++ )
            spirombuf[4+i] = *psrc++;

        /* Execute write command */
        spirom_cycle(spirombuf, bytes_to_program + 4 );

        /* Wait while busy */
        while( ( spirom_status( ) & 0x01 ) );

        /* Get ready for next iteration */
        bytes_left -= bytes_to_program;
        dst += bytes_to_program;
    }
}



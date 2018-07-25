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


#include "spiflash.h"

static Uint8 spirombuf[SPIROM_PAGESIZE + 5];
static Uint8 statusbuf[8];

/* ------------------------------------------------------------------------ *
 *  spirom_init( )                                                          *
 * ------------------------------------------------------------------------ */
void spirom_init( )
{
    /* Reset SPI */
    MCSPI_SYSCONFIGL |= 0x02; // Bit is automatically reset by hardware
    /* Wait for reset to complete */
    while(MCSPI_SYSSTATUSL & 0x01 == 0x00);

    /* Configure MCSPI Module */
    MCSPI_MODULCTRLL = 0
	| ( 0 << 8 ) // Data managed by MCSPI_TX(i) and MCSPI_RX(i) registers
	| ( 0 << 7 ) // Multiple word access disabled
	| ( 0 << 4 ) // No delay for first spi transfer
	| ( 0 << 3 ) // Functional mode
	| ( 0 << 2 ) // Master
	| ( 0 << 1 ) // SPIEN is used as a chip select
	| ( 1 << 0 );// Only one channel will be used in master mode

    MCSPI_CH0CONFL = 0
	| ( 0 << 15 ) // DMA Read Request disabled 
	| ( 0 << 14 ) // DMA Write Request disabled 
	| ( 0 << 12 ) // Transmit and Receive mode 
	| ( 7 <<  7 ) // SPI word length = 8
	| ( 1 <<  6 ) // SPIEN is held high during the active state
	| ( 8 <<  2 ) // CLKD = 8 Clock devider 
	| ( 0 <<  1 ) // SPICLK is held high during the active state 
	| ( 0 <<  0 );// Data are latched on even numbered edges of SPICLK
    MCSPI_CH0CONFU = 0
	| ( 0 << 13 ) // Clock divider granularity of power of two
	| ( 1 << 12 ) // The buffer is used to receive data
	| ( 1 << 11 ) // The buffer is used to transmit data
	| ( 1 << 9  ) // 1.5 cycles between CS toggling and first or last edge of SPI clock
	| ( 0 << 8  ) // Start bit polarity
	| ( 0 << 7  ) // Disable start bit
	| ( 0 << 4  ) // SPIEN active between SPI words
	| ( 0 << 3  ) // Turbo is deactivated 
	| ( 1 << 2  ) // Data Line0 selected for reception
	| ( 1 << 1  ) // Data Line1 selected for transmission 
	| ( 0 << 0  );// No transmission on Data Line0 

    /* Enable MCSPI channel */
    MCSPI_MODULCTRLL = 0x01; // Enable Channel
}

/*
 *  spirom_cycle( buf, len )
 *
 *  Execute a SPI spirom data transfer cycle.  Each byte in buf is shifted
 *  out and replaced with data coming back from the spirom.
 */
void spirom_cycle( Uint8 *buf, Uint16 len )
{
    Uint16 i;
    
	/* Enable Channel */
	MCSPI_CH0CTRLL = 0x01;
    /* SPIROM access cycle */
    MCSPI_CH0CONFU |= 0x0010;
    for ( i = 0 ; i <= len ; i++ )
    {
    	
        /* Wait for transmit empty */
        while ( (MCSPI_CH0STATL & 0x02) == 0 );
        MCSPI_CH0TXL = buf[i];  // Write to RX buffer 0 ??? Use upper register
        /* Wait for receive data full */
        while ( (MCSPI_CH0STATL & 0x01) == 0 );          
        buf[i] = MCSPI_CH0RXL;  // Read from RX buffer 0    ??? Use upper register
        
    }
    MCSPI_CH0CONFU &= ~0x0010;
	/* Disable Channel */
	MCSPI_CH0CTRLL = 0x00;
}

/*
 *  spirom_status( )
 */
Uint8 spirom_status( )
{
    /* Issue read status command */
    statusbuf[0] = SPIROM_CMD_RDSR;
    statusbuf[1] = 0;

    spirom_cycle( statusbuf, 2 );

    return statusbuf[1];
}

/*
 *  spirom_read( src, dst, length )
 */
void spirom_read( Uint32 src, Uint32 dst, Uint32 length )
{
    Int32 i;
    Uint8 *psrc, *pdst;

    // Setup command
    spirombuf[0] = SPIROM_CMD_READ;
    spirombuf[1] = ( src >> 16 );
    spirombuf[2] = ( src >> 8 );
    spirombuf[3] = ( src >> 0 );

    // Execute spirom read cycle
    spirom_cycle( spirombuf, length + 4 );

    // Copy returned data
    pdst = ( Uint8 * )dst;
    psrc = spirombuf + 4;
    for ( i = 0 ; i < length ; i++ )
        *pdst++ = *psrc++;
}

/*
 *  spiflash_erase( base, len )
 */
void spirom_erase( Uint32 base, Uint32 length )
{
    Int32 bytes_left, bytes_to_erase, eraseaddr;

    eraseaddr = base;
    bytes_left = length;

    while (bytes_left > 0 )
    {
        // Limit erase unit to sector size
	    bytes_to_erase = bytes_left;
		if (bytes_to_erase > SPIROM_SECTORSIZE)
		    bytes_to_erase = SPIROM_SECTORSIZE;

        // Align to sector boundaries
        if ((eraseaddr & SPIROM_SECTORSIZE) != ((eraseaddr + bytes_to_erase) & SPIROM_SECTORMASK))
            bytes_to_erase -= (eraseaddr + bytes_to_erase) - ((eraseaddr + bytes_to_erase) & SPIROM_SECTORMASK);

        // Issue WPEN
        spirombuf[0] = SPIROM_CMD_WREN;
        spirom_cycle(spirombuf, 0);
        
        // Issue sector unprotect
        spirombuf[0] = SPIROM_CMD_UNPROTECTSEC;
        spirombuf[1] = ( Uint8 )( eraseaddr >> 16 );
        spirombuf[2] = ( Uint8 )( eraseaddr >> 8 );
        spirombuf[3] = ( Uint8 )( eraseaddr );
        spirom_cycle(spirombuf, 3);
        
        // Issue erase
        spirombuf[0] = SPIROM_CMD_ERASESEC;
        spirombuf[1] = ( Uint8 )( eraseaddr >> 16 );
        spirombuf[2] = ( Uint8 )( eraseaddr >> 8 );
        spirombuf[3] = ( Uint8 )( eraseaddr );
        spirom_cycle(spirombuf, 3);

        /* Wait while busy */
        while( ( spirom_status( ) & 0x01 ) );

        /* Get ready for next iteration */
        bytes_left -= bytes_to_erase;
        eraseaddr += bytes_to_erase;
    }
}

/*
 *  spirom_write( src, dst, length )
 */
void spirom_write( Uint32 src, Uint32 dst, Uint32 length )
{
    Int32 i;
    Int32 bytes_left;
    Int32 bytes_to_program;
    Uint8 *psrc;

    /* Establish source */
    psrc = ( Uint8 * )src;
    bytes_left = length;

    while ( bytes_left > 0 )
    {
        bytes_to_program = bytes_left;

        /* Most to program is SPIROM_CMD_BLOCKSIZE */
        if ( bytes_to_program > SPIROM_PAGESIZE )
             bytes_to_program = SPIROM_PAGESIZE;

        /* Make sure you don't run off the end of a block */
        if ( ( dst & SPIROM_PAGEMASK ) != ( ( dst + bytes_to_program ) & SPIROM_PAGEMASK ) )
            bytes_to_program -= ( dst + bytes_to_program ) - ( ( dst + bytes_to_program ) & SPIROM_PAGEMASK );

        /* Issue WPEN */
        spirombuf[0] = SPIROM_CMD_WREN;
        spirom_cycle( spirombuf, 0 );

        /* Create command block for program operation */
        spirombuf[0] = SPIROM_CMD_WRITE;
        spirombuf[1] = ( Uint8 )( dst >> 16 );
        spirombuf[2] = ( Uint8 )( dst >> 8 );
        spirombuf[3] = ( Uint8 )( dst );

        for ( i = 0 ; i < bytes_to_program ; i++ )
            spirombuf[4+i] = *psrc++;

        /* Execute write command */
        spirom_cycle( spirombuf, bytes_to_program + 3 );

        /* Wait while busy */
        while( ( spirom_status( ) & 0x01 ) );

        /* Get ready for next iteration */
        bytes_left -= bytes_to_program;
        dst += bytes_to_program;
    }
}

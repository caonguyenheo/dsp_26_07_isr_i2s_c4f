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
#include "evm5517_i2cgpio.h"
#include "spiflash.h"
#include "stdio.h"

static Uint8 tx[spiflash_PAGESIZE];
static Uint8 rx[spiflash_PAGESIZE];

/*
 *
 *  spirom_test( )
 *      SPI ROM test, write then verify the contents of the first 4 pages
 *
 */
Int16 spirom_test( )
{
    Uint16 i, j;
    Uint16* p8;

#if(1)
    /* Setup MUX for SPI Flash */	
	EVM5517_I2CGPIO_configLine(  5, 0 );
	EVM5517_I2CGPIO_writeLine(   5, 0 );  // SPI_I2S_S0 = 0

	EVM5517_I2CGPIO_configLine(  6, 0 );
	EVM5517_I2CGPIO_writeLine(   6, 0 );  // SPI_I2S_S1 = 0
#endif
	
	/* Initialize the SPI interface */
    spirom_init( );

    /* Erase target area in spiflash */
	spiflash_erase( 0, 4 * spiflash_PAGESIZE);

    /* Write to spiflash */
    for ( i = 0 ; i < 4 ; i++ )
    {
        /* Create the test pattern */
        p8 = ( Uint16* )tx;
        for ( j = 0 ; j < spiflash_PAGESIZE ; j++ )
            *p8++ = ( Uint8 )( j + i + 8 );

        /* Write a page */
        spirom_write( ( Uint32 )tx, i * spiflash_PAGESIZE, spiflash_PAGESIZE );
    }

	/* Clear receive buffer */
    for ( j = 0 ; j < spiflash_PAGESIZE ; j++ )
        rx[j] = 0;

    /* Read and verify spiflash */
    for ( i = 0 ; i < 4 ; i++ )
    {
        /* Read a page */
        spirom_read( i * spiflash_PAGESIZE, ( Uint32 )rx, spiflash_PAGESIZE );

        /* Check the pattern */
        p8 = ( Uint16* )rx;
        for ( j = 0 ; j < spiflash_PAGESIZE ; j++ )
            if ( *p8  != ((i + j + 8 ) & 0xFF))
                return 1;  // Fail
            else p8++;
        printf("    Page %d verified\n", i);
    }
    
    /* Retest first page with different pattern to validate erase */
	spiflash_erase( 0, spiflash_PAGESIZE);
    /* Create the test pattern */
    p8 = ( Uint16* )tx;
    for ( j = 0 ; j < spiflash_PAGESIZE ; j++ )
        *p8++ = ( Uint8 )( j + 4 );

    /* Write a page */
    spirom_write( ( Uint32 )tx, 0, spiflash_PAGESIZE );

    /* Read a page */
    spirom_read( 0, ( Uint32 )rx, spiflash_PAGESIZE );
    
    /* Check the pattern */
    p8 = ( Uint16* )rx;
    for ( j = 0 ; j < spiflash_PAGESIZE ; j++ )
        if ( *p8  != ((j + 4 ) & 0xFF))
            return 1;  // Fail
        else p8++;

    return 0;
}


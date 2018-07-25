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

static Uint8 tx[SPIROM_PAGESIZE];
static Uint8 rx[SPIROM_PAGESIZE];

/*
 *
 *  spirom_test( )
 *      SPI ROM test, write then verify the contents of the first 4 pages
 *
 */
Int16 mcspiflash_test( )
{
    Uint8 i, j;
    Uint8* p8;
    Uint16 error=0;

    /* Setup MUX for McSPI Flash */	
	EVM5517_I2CGPIO_configLine(  12, 0 );
	EVM5517_I2CGPIO_writeLine(   12, 0 );  // SEL0_MMC1_MCSPI = 0

	EVM5517_I2CGPIO_configLine(  13, 0 );
	EVM5517_I2CGPIO_writeLine(   13, 1 );  // SEL1_MMC1_MCSPI = 1

    /* Configure EBSR for McSPI */
    SYS_EXBUSSEL &= ~0x0C00;  // Clear SP1MODE
    SYS_EXBUSSEL |=  0x0400;  // Set SP1MODE to McSPI

    /* Initialize the SPI interface */
    spirom_init( );

    /* Erase target area in spiflash */
	spirom_erase( 0, 4 * SPIROM_PAGESIZE);

    /* Write to spirom */
    for ( i = 0 ; i < 4 ; i++ )
    {
        /* Create the test pattern */
        p8 = ( Uint8* )tx;
        for ( j = 0 ; j < SPIROM_PAGESIZE ; j++ )
            *p8++ = ( Uint8 )( j + i );

        /* Write a page */
        spirom_write( ( Uint32 )tx, i * SPIROM_PAGESIZE, SPIROM_PAGESIZE );
    }

    /* Clear receive buffer */
    for ( j = 0 ; j < SPIROM_PAGESIZE ; j++ )
        rx[j] = 0;

    /* Read and verify spirom */
    for ( i = 0 ; i < 4 ; i++ )
    {
        /* Read a page */
        spirom_read( i * SPIROM_PAGESIZE, ( Uint32 )rx, SPIROM_PAGESIZE );

        /* Check the pattern */
        p8 = ( Uint8* )rx;
        for ( j = 0 ; j < SPIROM_PAGESIZE ; j++ )
            if ( ( *p8++ ) != (( i + j )& 0xFF) )
                error++;  // Fail

    }

    return error;
}


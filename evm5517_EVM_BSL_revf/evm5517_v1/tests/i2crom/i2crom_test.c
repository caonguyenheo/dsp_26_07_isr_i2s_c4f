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
#include "i2crom.h"
#include "stdio.h"

static Uint8 tx[4][EEPROM_PAGE_SIZE];
static Uint8 rx[4][EEPROM_PAGE_SIZE];

/*
 *
 *  eeprom_test( )
 *      I2C EEPROM test, write then verify the contents of the first 4
 *      pages.
 *
 */
Int16 i2crom_test( )
{
    Int16 i, j;
    Int16 errors = 0;

    Uint16 pages = 4;
    Uint16 page_size = EEPROM_PAGE_SIZE;

    Uint8 *p8;
    Uint32 src, dst;

    /* Initialize I2C */
	EVM5517_I2C_init( );

    /* Create the test pattern */
    p8 = ( Uint8* )tx;
    for ( i = 0 ; i < pages * page_size ; i++ )
        *p8++ = i;

    /* Clear RX buffer */
    p8 = ( Uint8* )rx;
    for ( i = 0 ; i < pages * page_size ; i++)
        *p8++ = 0;

    /* Write 1 page at a time */
    for ( i = 0 ; i < pages ; i++ )
    {
        src = ( Uint32 )&tx[i];
        dst = i * page_size;

        if ( i2crom_write( src, dst, page_size ) )
            return 1;

        EVM5517_wait( 50000 );
    }

    /* Read 1 page at a time */
    for ( i = 0 ; i < pages ; i++ )
    {
        src = i * page_size;
        dst = ( Uint32 )&rx[i];

        if ( i2crom_read( src, dst, page_size ) )
            return 2;

        EVM5517_wait( 25000 );
    }

    /* Verify tx & rx */
    for ( i = 0 ; i < pages ; i++ )
    {
        errors = 0;

        for ( j = 0 ; j < page_size ; j++ )
            if ( tx[i][j] != rx[i][j] )
                errors++;

        if ( errors == 0 )
            printf( "    Page %d: PASS\n", i );
        else
            printf( "    Page %d: FAIL\n", i );
    }

    return errors;
}

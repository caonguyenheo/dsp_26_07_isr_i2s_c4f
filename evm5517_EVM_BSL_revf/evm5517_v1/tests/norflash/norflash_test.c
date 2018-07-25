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


/*
 *  NOR Flash Test
 *
 */

#include "stdio.h"
#include "norflash.h"

static Uint32 buf_len = 512;
static Uint16 rx[512];
static Uint16 tx[512];

/*
 *
 *  norflash_test( )
 *
 */
Int16 norflash_test( )
{
    Int32 i = 0, j = 0;
    Int16 errors = 0;

    Uint32 npages;
    Uint32 nbytes;

    Uint16 *p16, id[4];
    Uint32 addr;
    
    /* Initialize Flash */
    norflash_init();
    
    _FLASH_getId( &id[0] );
    printf("Manufacturer ID is: %x \nDevice ID is:     %x\n", id[0], id[1]);

    npages = FLASH_PAGES;
        
    /* ---------------------------------------------------------------- *
     *  Erase                                                           *
     * ---------------------------------------------------------------- */
    printf( "     Erasing Flash [%d-%d] pages\n", 0, /*npages*/7 );

    /* Erase all bytes of Flash */
    for ( i = 0 ; i < npages ; i += 8 )
    {
        printf( "     Erasing ( Pg: %d-%d of %d )\n", i, i + 7, /*npages*/7 );
        errors = norflash_erase( FLASH_BASE + ( i * FLASH_PAGESIZE ), 8 * FLASH_PAGESIZE );

        /* Check errors */
        if ( errors )
        {
            printf( "     Error: Erasing code %d\n", errors );
            return ( errors | 0x8000 );
        }
    }

    /* ---------------------------------------------------------------- *
     *  Write                                                           *
     * ---------------------------------------------------------------- */
    printf( "     Writing Flash [%d-%d] words\n", 0, 512/*nbytes*/ );

    i = 0;

    /* Iterate through all bytes */
    for ( addr = FLASH_BASE ; addr < FLASH_BASE + /*nbytes*/buf_len ; addr += buf_len )
    {
        /* Create write pattern */
        p16 = ( Uint16* )tx;
        for ( j = 0 ; j < buf_len ; j += 4 )
            *p16++ = ( (addr >> 8) + j + i );

        /* Write the pattern to Flash */
        errors = norflash_write( ( Uint32 )tx, addr, buf_len );

        /* Check errors */
        if ( errors )
        {
            printf( "    Error: Writing code %d\n", errors );
            return ( errors | 0x8000 );
        }

        /* Write first page, then the beginning of each other page */
        if ( ( addr - FLASH_BASE ) >= FLASH_PAGESIZE )
        {
            addr += ( FLASH_PAGESIZE - buf_len );
            i = ( i + 1 ) & 3;
        }
    }

    /* ---------------------------------------------------------------- *
     *  Read                                                            *
     * ---------------------------------------------------------------- */
    printf( "     Reading Flash [%d-%d] words\n", 0, 512/*nbytes*/ );

    i = 0;

    /* Iterate through all bytes */
    for ( addr = FLASH_BASE ; addr < FLASH_BASE + buf_len/*nbytes*/ ; addr += buf_len )
    {
        /* Read from Flash */
        errors = norflash_read( addr, ( Uint32 )rx, buf_len );

        /* Check pattern */
        p16 = ( Uint16* )rx;
        for ( j = 0 ; j < buf_len ; j += 4 )
            if ( *p16++ != ( (addr >> 8) + j + i ) )
                return ( j | 0x8000 );

        /* Check errors */
        if ( errors )
        {
            printf( "     Error: Reading code %d\n", errors );
            return ( errors | 0x8000 );
        }

        /* Read first page, then the beginning of each other page */
        if ( ( addr - FLASH_BASE ) >= FLASH_PAGESIZE )
        {
            addr += ( FLASH_PAGESIZE - buf_len );
            i = ( i + 1 ) & 3;
        }
    }

    printf( "     Erasing 1st Flash page\n" );

    /* Erase first page of Flash before exiting */
    norflash_erase( FLASH_BASE, FLASH_PAGESIZE );

    /* Test Passed */

    return 0;
}

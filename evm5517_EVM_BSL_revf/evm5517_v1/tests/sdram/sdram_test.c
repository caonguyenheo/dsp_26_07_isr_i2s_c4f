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
#include "stdio.h"

Uint32 sdram_base;
Uint32 sdram_size;


Uint16 memfill16( Uint32 start, Uint32 len, Uint32 val )
{
    Uint32 i;
    Uint32 end = start + len;
    Uint32 errorcount = 0;
	Uint16 *pdata;

    /* Write Pattern */
	pdata = (Uint16 *)start;
    for ( i = start; i < end; i += 1 )
    {
        *pdata++ = val;
    }

    /* Read Pattern */
	pdata = (Uint16 *)start;
    for ( i = start; i < end; i += 1 )
    {
        if ( *pdata++ != val )
        {
            errorcount++;
            break;
        }
    }

    return errorcount;
}

Uint16 memasdram16( Uint32 start, Uint32 len )
{
    Uint32 i;
    Uint32 end = start + len;
    Uint32 errorcount = 0;
	Uint16 *pdata;


    /* Write Pattern */
	pdata = (Uint16 *)start;
    for ( i = start; i < end; i ++ )
    {
	    *pdata++ = i & 0xFFFF;

    }

    /* Read Pattern */
	pdata  = (Uint16 *)start;
    for ( i = start; i < end; i ++ )
    {
        if ( *pdata++ != (i & 0xFFFF) )
        {
            errorcount++;
            break;
        }
    }

    return errorcount;
}

Uint16 meminvasdram16( Uint32 start, Uint32 len )
{
    Uint32 i;
    Uint32 end = start + len;
    Uint32 errorcount = 0;
	Uint16 *pdata;

    /* Write Pattern */
	pdata = (Uint16 *)start;
    for ( i = start; i < end; i ++ )
    {
        *pdata++ = (~i & 0xFFFF);
    }

    /* Read Pattern */
	pdata = (Uint16 *)start;
    for ( i = start; i < end; i ++ )
    {
        if ( *pdata++ != (~i & 0xFFFF)  )
        {
            errorcount++;
            break;
        }
    }

    return errorcount;
}


/*
 *
 *  sdram_test( )
 *      Test sdram memory, checks the data and asdramess lines are good.
 *
 */
#if 0 // Full test
Uint16 sdram_test( )
{
    Int16 errors = 0;

    sdram_base = 0x80000000;       // sdram memory
    sdram_size = 0x00100000;       // 1 MB

    printf( "  > Data test\n" );
    if ( memfill16( sdram_base, sdram_size, 0xFFFF ) )
        errors += 1;

    if ( memfill16( sdram_base, sdram_size, 0xAAAA ) )
        errors += 2;

    if ( memfill16( sdram_base, sdram_size, 0x5555 ) )
        errors += 4;

    if ( memfill16( sdram_base, sdram_size, 0x0000 ) )
        errors += 8;

    if ( errors )
	    printf( "        > Error = 0x%x\n", errors );

    sdram_base = 0x80100000;       // sdram memory
    sdram_size = 0x07ff0000;       // 127 MB

    return errors;
}
#endif
Uint16 sdram_test( )
{
    Int16 errors = 0;

    sdram_base = 0x028000;       // sdram memory
    sdram_size = 0x7B0000 / 2;       // 8 MB (Word address)

    printf( "  > Data test \n" );
    if ( memfill16( sdram_base, sdram_size, 0xFFFF ) )
        errors += 1;

    if ( memfill16( sdram_base, sdram_size, 0xAAAA ) )
        errors += 2;

    if ( memfill16( sdram_base, sdram_size, 0x5555 ) )
        errors += 4;

    if ( memfill16( sdram_base, sdram_size, 0x0000 ) )
        errors += 8;

    if ( errors )
	    printf( "        > Error = 0x%x\n", errors );


    sdram_base = 0x028000;       // sdram memory
    sdram_size = 0x7B0000 / 2;       // 8 MB (Word address)

    printf( "  > Address test\n" );
    if ( memasdram16( sdram_base, sdram_size ) )
        errors += 16;

    printf( "  > Inv Address test\n" );
    if ( meminvasdram16( sdram_base, sdram_size ) )
        errors += 16;

	printf("\n");

    return errors;
}

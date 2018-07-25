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


#include "stdio.h"
#include "evm5517.h"

/*
 *
 *  Testing Function
 *
 */
void TEST_execute( Int16 ( *funchandle )( ), char *testname, Int16 testid )
{
    Int16 status;

    /* Display test ID */
    printf( "%02d  Testing %s...\n", testid, testname );

    /* Call test function */
    status = funchandle( );

    /* Check for test fail */
    if ( status != 0 )
    {
        /* Print error message */
        printf( "     FAIL... error code %d... quitting\n", status );

        /* Software Breakpoint to Code Composer */
        SW_BREAKPOINT;
    }
    else
    {
        /* Print error message */
        printf( "    PASS\n" );
    }
}

extern Int16 oled_test( );

/*
 *
 *  main( )
 *
 */
void main( void )
{
    /* Initialize BSL */
    EVM5517_init( );

    printf("EXBUSSEL = %02x\n", SYS_EXBUSSEL);
    
    TEST_execute( oled_test, "OLED", 1 );

    printf( "\n***ALL Tests Passed***\n" );
    SW_BREAKPOINT;
}

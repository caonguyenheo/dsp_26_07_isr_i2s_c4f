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

void StopTest( );
extern Int16 i2cChecker_test( );

int  TestFail    = (int)-1;

/*
 *
 *  main( )
 *
 */
void main( void )
{
    /* Initialize BSL */
    EVM5517_init( );

    /* Display test ID */
    printf( "\nTesting I2C0 Checker...\n");

    /* Call test function */
    TestFail = i2cChecker_test( );

    /* Check for test fail */
    if ( TestFail != 0 )
    {
        /* Print error message */
        printf( "     FAIL... error code %d... quitting\n", TestFail );
    }
    else
    {
        /* Print pass message */
        printf( "    PASS\n" );
        printf( "\n***ALL Tests Passed***\n" );
    }

    StopTest();
}

void StopTest()
{
    //SW_BREAKPOINT;
    return;
}

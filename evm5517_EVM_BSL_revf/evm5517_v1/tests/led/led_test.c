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
#include "evm5517_led.h"

/*
 *
 *  led_test( )
 *      Running Eight LED test
 *
 */
Int16 led_test( )
{
    Int16 j;

    /* Initialize the LED module */
    EVM5517_LED_init( );

    /* Running LED test */
    for ( j = 0 ; j < 10 ; j++ )
    {
        EVM5517_LED_on( 0 );        // ON
        EVM5517_waitusec( 500000 ); // Wait 5 sec
        EVM5517_LED_off( 0 );       // OFF
        EVM5517_waitusec( 500000 ); // Wait 5 sec
    }

    /* Turn on LED to indicate a PASS */
    EVM5517_LED_on( 0 );

    return 0;
}


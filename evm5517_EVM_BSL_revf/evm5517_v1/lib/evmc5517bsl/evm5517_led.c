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
 *  EVM5517_LED_init( )
 *
 *      Clear LEDs 
 *
 */
Int16 EVM5517_LED_init( )
{
    /* Turn OFF all LEDs */
    return EVM5517_LED_off( 0 );
}


/*
 *
 *  EVM5517_LED_on( number )
 *
 *      number <- 0
 *
 */
Int16 EVM5517_LED_on(Uint16 number)
{
	asm(" bset XF");
	asm(" nop");
	asm(" nop");
	asm(" nop");
	asm(" nop");
	asm(" nop");

    return 0;
}

/*
 *
 *  EVM5517_LED_off( number )
 *
 *      number <- 0
 *
 */

Int16 EVM5517_LED_off(Uint16 number)
{
	asm(" bclr XF");
	asm(" nop");
	asm(" nop");
	asm(" nop");
	asm(" nop");
	asm(" nop");

    return 0;
}


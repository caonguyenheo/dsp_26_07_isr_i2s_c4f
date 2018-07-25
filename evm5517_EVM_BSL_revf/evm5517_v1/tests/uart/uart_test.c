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
#include "evm5517_uart.h"

#define preg1 *(volatile ioport Uint16*)(0x1c3a)
#define preg2 *(volatile ioport Uint16*)(0x1c3b)

/*
 *
 *  uart_test( )
 *      Simple UART loopback test.
 *      Will write then read back the byte sent to the RS232 connector.
 *
 */
Int16 uart_test()
{
    Int16 i, errors = 0;
    Uint8 rx[256];
    Uint8 tx[256];

    Int16 timeout = 0;
preg1 = 0;
preg2 = 0;

    /* Open Uart Handle */
    EVM5517_UART_open( );

    /* Setup buffers */
    for ( i = 0 ; i < 0x100 ; i++ )
    {
        tx[i] = i;
        rx[i] = 0;
    }

    /* UART Test */
    for ( i = 64 ; i < 96 ; i++ )
    {
        /* TX */
  //      timeout = test_timeout;
        while((UART_LSR & 0x60)==0);  // Wait for TX ready
    /*    {
            if ( timeout-- < 0 )
                return -1;
        }*/

        EVM5517_UART_putChar( tx[i] );    // Write 1 byte

        /* RX */
   //     timeout = test_timeout;
        while((UART_LSR & 0x01)==0);  // Wait for Rx ready
        /*{
            if ( timeout-- < 0 )
                return -1;
        }*/

        EVM5517_UART_getChar( &rx[i] );   // Read 1 byte
    }

    /* Compare TX & RX buffers */
    for ( i = 64 ; i < 96 ; i++ )
        if ( tx[i] != rx[i] )
            errors++;
    return errors;
}

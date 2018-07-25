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

/*
 *
 *  EVM5517_UART_open( divisor )
 *
 *      Open UART handle
 *
 */
Int16 EVM5517_UART_open( )
{
		Uint16 dummy;

        SYS_EXBUSSEL &= ~0xF000;   //
        SYS_EXBUSSEL |=  0x1000;   // Set parallel port to mode 1 (SPI, GPIO, UART, and I2S2)
        SYS_PRCNTRLR &= ~0x0080;   // Make sure UART is out of reset
        SYS_PCGCR1   &= ~0x0004;   // Enable UART clock
        UART_PWREMU_MGMT &= ~0xe000; // Place the UART transmitter and receiver in reset
        /*  
         * Configuring for baud rate of 115200
         * Divisor = UART input clock frequency / (Desired baud rate*16)
         * = 100MHz / 115200 / 16
         * = 54
         */

        UART_DLL = 0x36;  // Set baud rate
        UART_DLH = 0x00;
        
        UART_FCR = 0x0007;            // Clear UART TX & RX FIFOs
        UART_FCR = 0x0000;            // Non-FIFO mode
        UART_IER = 0x0007;            // Enable interrupts
        UART_LCR = 0x0003;            // 8-bit words,
                                      // 1 STOP bit generated,
                                      // No Parity, No Stick paritiy,
                                      // No Break control
        UART_MCR = 0x0000;            // RTS & CTS disabled,
                                      // Loopback mode disabled,
                                      // Autoflow disabled

        UART_PWREMU_MGMT = 0xe001;    // Enable TX & RX componenets

		// Clear any pre-existing characters
        dummy = UART_THR;
       /* while(1)
        {
        	while((UART_LSR & 0x60)==0);
        	UART_THR = 0x55;
        }*/
	    return 0;
}

/*
 *
 *  EVM5517_UART_putChar( uart_handle, data )
 *
 *      Send 1 byte of serial data
 *
 */
Int16 EVM5517_UART_putChar( Uint8 data )
{
    UART_THR = data;

    return 0;
}

/*
 *
 *  EVM5517_UART_getChar( uart_handle, data )
 *
 *      Recv 1 byte of serial data 
 *
 */
Int16 EVM5517_UART_getChar( Uint8* data )
{
    *data = UART_THR;

    return 0;
}


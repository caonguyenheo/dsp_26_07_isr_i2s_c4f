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

#define USBLDOCTRL         *( volatile ioport Uint16* )( 0x7004 )
#define CLKSTOP            *( volatile Uint16* )(0x1c3a) // CLKSTOP register
#define PCGCR_H            *( volatile Uint16* )(0x1c03) // PERIPHERAL CLOCK GATING CONFIGURATION REGISTER
#define PSRCR              *( volatile Uint16* )(0x1c04) // Peripheral Software Reset Counter Register
#define PRCR               *( volatile Uint16* )(0x1c05) // Peripheral Reset Control Register
#define IVPD               *( volatile Uint16* )(0x0049) // Interrupt vector pointer DSP
#define IVPH               *( volatile Uint16* )(0x004A) // Interrupt vector pointer HOST
#define IER0               *( volatile Uint16* )(0x0000) // Interrupt mask register 0; in C5505 spec, it is also called IMR0 
#define IER1               *( volatile Uint16* )(0x0045) // Interrupt mask register 1; in C5505 spec, it is also called IMR1
#define IFR0               *( volatile Uint16* )(0x0001) // Interrupt flag register 0 
#define IFR1               *( volatile Uint16* )(0x0046) // Interrupt flag register 1  
#define USBSCR             *( volatile ioport Uint16* )(0x1c32) //USB system control Register


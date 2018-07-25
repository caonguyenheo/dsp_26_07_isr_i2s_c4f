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

/* ------------------------------------------------------------------------ *
 *  SPI Controller                                                          *
 * ------------------------------------------------------------------------ */

#define SPICDR         *(volatile ioport Uint16*)(0x3000) // Clock Divider Register
#define SPICCR         *(volatile ioport Uint16*)(0x3001) // Clock Control Register
#define SPIDCR1        *(volatile ioport Uint16*)(0x3002) // Device Configuration Register 1
#define SPIDCR2        *(volatile ioport Uint16*)(0x3003) // Device Configuration Register 2
#define SPICMD1        *(volatile ioport Uint16*)(0x3004) // Command Register 1
#define SPICMD2        *(volatile ioport Uint16*)(0x3005) // Command Register 2
#define SPISTAT1       *(volatile ioport Uint16*)(0x3006) // Status Register 1
#define SPISTAT2       *(volatile ioport Uint16*)(0x3007) // Status Register 2
#define SPIDAT1        *(volatile ioport Uint16*)(0x3008) // Data Register 1
#define SPIDAT2        *(volatile ioport Uint16*)(0x3009) // Data Register 2

/* ------------------------------------------------------------------------ *
 *  Prototype                                                               *
 * ------------------------------------------------------------------------ */
void spi_init( );
void spi_cycle(Uint16 *buf, Uint16 len);




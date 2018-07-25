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
#include "spi.h"
#include "stdio.h"

/*
 *  spi_init( )
 */
void spi_init( )
{
	Int16 i;
	/* Reset Counter value */
	SYS_PRCNTR = 0x04;
	
	/* Reset SPI Module */
	SYS_PRCNTRLR = 0x00ff;
	for(i=0;i<100;i++) {;}
	/* Enable SPICLK,RX,TX & CS0 */
	SYS_EXBUSSEL =(0x5<<12);

	//SPI init
	SPICCR  &=  0x8000;  // Reset SPI
    SPICDR  =   0x0009;  // 10MHz SPI clock (100MHz/10)
    SPIDCR1 =   0x0004;  // CLK = rising edge
    SPICMD2 &= ~0x30F8;  // Enable CS0 and clear fields
    SPICMD2 |=  0x0040;  // Set word length as 9-bit
    SPICCR  =   0x8000;  // Enable SPI
	while((SPISTAT1 & 0x0001) != 0) {}; // Wait for SPI ready
	
    return;
}

/*
 *  spi_cycle(buf, len)
 * 
 *  Execute a SPI spirom data transfer cycle.  Each byte in buf is shifted
 *  out and replaced with data coming back from the spirom.
 */

void spi_cycle(Uint16 *buf, Uint16 len)
{
    Uint16 i;

    SPICMD1 = 0x0000 | len - 1;

   	/* Spirom access cycle */
	for (i = 0; i < len; i++)
	{
		SPIDAT2 = buf[i] << 7; // Lower 16-bit
		SPIDAT1 = 0x0000;      // Upper 16-bit
        SPICMD2 = 0x0042;      //  9-bit words, write
        
        /* Wait for character transfer to complete */
        while((SPISTAT1 & 0x0002) == 0) {};
        buf[i] = SPIDAT2 & 0xff;
	}
	
	/* Wait for transfer to complete */
	while((SPISTAT1 & 0x0001) != 0) {};
}

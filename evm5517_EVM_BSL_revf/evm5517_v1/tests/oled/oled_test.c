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


#include "spi.h"
#include "stdio.h"
#include "evm5517.h"
#include "evm5517_i2c.h"
#include "evm5517_i2cgpio.h"

void oledWrite( Uint16 type, Uint16 val);

#define CMD     0x000
#define DATA    0x100

static Uint16 writeBuff[64];

/*
 * oled_test()
 *     Color bar test for the OLED screen
 *
 */
Int16 oled_test()
{

	Int16 i,j;
	Uint16 regval;

	printf("SW11 MSP430_SPI_OEN must be configured to the ON position\n");

    /* Setup MUX for LCD SPI */	
	EVM5517_I2CGPIO_configLine( 6, 0 );
	EVM5517_I2CGPIO_writeLine(  6, 1 );
	EVM5517_I2CGPIO_configLine( 5, 0 );
	EVM5517_I2CGPIO_writeLine(  5, 0 );

	/* Reset LCD module */
    EVM5517_I2CGPIO_configLine( 7, 0 );
	EVM5517_I2CGPIO_writeLine(  7, 0 );
	EVM5517_I2CGPIO_writeLine(  7, 1 );
	EVM5517_waitusec(100000);

	/* Initialize SPI */
	spi_init( );
	
	/* Initialize OLED screen */
	oledWrite( 0xFD, CMD);   // Command Lock
	oledWrite( 0x12, DATA);
	
	oledWrite( 0xFD, CMD);   // Command Lock
	oledWrite( 0xB1, DATA);
	
	oledWrite( 0xAE, CMD);   // Sleep mode on
	
	oledWrite( 0xB3, CMD);   // Set Display freq/div
	oledWrite( 0xF1, DATA);
	
	oledWrite( 0xCA, CMD);   // Set Multiplex ratio
	oledWrite( 0x7F, DATA);
	
	oledWrite( 0xA2, CMD);   // Set Display offset
	oledWrite( 0x00, DATA);

	oledWrite( 0xA1, CMD);   // Set Display start line
	oledWrite( 0x00, DATA);

	oledWrite( 0xA0, CMD);   // Set Remap and color depth
	oledWrite( 0xb1, DATA);

	oledWrite( 0xB5, CMD);   // Set GPIO
	oledWrite( 0x00, DATA);


	oledWrite( 0xAB, CMD);   // Function slelction
	oledWrite( 0x01, DATA);
	
	writeBuff[0] =0xB4 | CMD;    // Set segment low voltage
	writeBuff[0] =0xA0 | DATA;   //
	writeBuff[0] =0xB5 | DATA;   // 
	writeBuff[0] =0x55 | DATA;   //		
	spi_cycle(writeBuff, 4);
	
	writeBuff[0] =0xC1 | CMD;    // Set contrast current
	writeBuff[0] =0xC8 | DATA;   //	
	writeBuff[0] =0x80 | DATA;   // 
	writeBuff[0] =0xC8 | DATA;   //	
	spi_cycle(writeBuff, 3);
	
	oledWrite( 0xC7, CMD);       // Set Master current control
	oledWrite( 0x0F, DATA);
	
	writeBuff[0] =0xB8 | CMD;    // Gamma Lookup table
	writeBuff[1] =0x2 | DATA;
    writeBuff[2] =0x3 | DATA;
    writeBuff[3] =0x4 | DATA;
    writeBuff[4] =0x5 | DATA;
    writeBuff[5] =0x6 | DATA;
    writeBuff[6] =0x7 | DATA;
    writeBuff[7] =0x8 | DATA;
    writeBuff[8] =0x9 | DATA;
    writeBuff[9] =0xa | DATA;
    writeBuff[10] =0xb | DATA;
    writeBuff[11] =0xc | DATA;
    writeBuff[12] =0xd | DATA;
    writeBuff[13] =0xe | DATA;
    writeBuff[14] =0xf | DATA;
    writeBuff[15] =0x10 | DATA;
    writeBuff[16] =0x11 | DATA;
    writeBuff[17] =0x12 | DATA;
    writeBuff[18] =0x13 | DATA;
    writeBuff[19] =0x15 | DATA;
    writeBuff[20] =0x17 | DATA;
    writeBuff[21] =0x19 | DATA;
    writeBuff[22] =0x1B | DATA;
    writeBuff[23] =0x1D | DATA;
    writeBuff[24] =0x1F | DATA;
    writeBuff[25] =0x21 | DATA;
    writeBuff[26] =0x23 | DATA;
    writeBuff[27] =0x25 | DATA;
    writeBuff[28] =0x27 | DATA;
    writeBuff[29] =0x2A | DATA;
    writeBuff[30] =0x2D | DATA;
    writeBuff[31] =0x30 | DATA;
    writeBuff[32] =0x33 | DATA;
    writeBuff[33] =0x36 | DATA;
    writeBuff[34] =0x39 | DATA;
    writeBuff[35] =0x3C | DATA;
    writeBuff[36] =0x3F | DATA;
    writeBuff[37] =0x42 | DATA;
    writeBuff[38] =0x45 | DATA;
    writeBuff[39] =0x48 | DATA;
    writeBuff[40] =0x4C | DATA;
    writeBuff[41] =0x50 | DATA;
    writeBuff[42] =0x54 | DATA;
    writeBuff[43] =0x58 | DATA;
    writeBuff[44] =0x5C | DATA;
    writeBuff[45] =0x60 | DATA;
    writeBuff[46] =0x64 | DATA;
    writeBuff[47] =0x68 | DATA;
    writeBuff[48] =0x6C | DATA;
    writeBuff[49] =0x70 | DATA;
    writeBuff[50] =0x74 | DATA;
    writeBuff[51] =0x78 | DATA;
    writeBuff[52] =0x7D | DATA;
    writeBuff[53] =0x82 | DATA;
    writeBuff[54] =0x87 | DATA;
    writeBuff[55] =0x8C | DATA;
    writeBuff[56] =0x91 | DATA;
    writeBuff[57] =0x96 | DATA;
    writeBuff[58] =0x9B | DATA;
    writeBuff[59] =0xA0 | DATA;
    writeBuff[60] =0xA5 | DATA;
    writeBuff[61] =0xAA | DATA;
    writeBuff[62] =0xAF | DATA;
    writeBuff[63] =0xB4 | DATA;
    spi_cycle(writeBuff, 64);

	oledWrite( 0xB1, CMD);      // Set Phase lenth
	oledWrite( 0x32, 0x100);

	writeBuff[0] =0xB2 | CMD;   // Enhance driving scheme capability
	writeBuff[0] =0xA4 | DATA;
	writeBuff[0] =0x00 | DATA;
	writeBuff[0] =0x00 | DATA;
    spi_cycle(writeBuff, 4);

	oledWrite( 0xBB, CMD);      // Set precharge voltage
	oledWrite( 0x17, DATA);

	oledWrite( 0xB6, CMD);      // Set second precharge period
	oledWrite( 0x01, DATA);

	oledWrite( 0xBE, CMD);      // Set VCOMH voltage
	oledWrite( 0x05, DATA);
	
	oledWrite( 0xA6, CMD);      // Set Display Mode
	oledWrite( 0xAF, CMD);      // Set Display Mode
    

    /* Display color bars on OLED screen */
	// RED
   	writeBuff[0] =0x15 | CMD;		    // Set Column Address
    writeBuff[1] =0x00 | DATA;		    // Default => 0x00 (Start Address)
    writeBuff[2] =0x1f | DATA;			// Default => 0x7F (End Address)		
	spi_cycle(writeBuff, 3);		
	
    writeBuff[0] =0x75 | CMD;			// Set Row Address
	writeBuff[1] =0x00 | DATA;			// Default => 0x00 (Start Address)
    writeBuff[2] =0x7f | DATA;			// Default => 0x7F (End Address)	
    spi_cycle(writeBuff, 3);	
    	
    writeBuff[0] =0x5C | CMD;			// Enable MCU to Write into RAM	 
    spi_cycle(writeBuff, 1);	
	for(i=0;i<32;i++)
	{
		for(j=0;j<128;j++)
		{
			writeBuff[0] = 0x00 | DATA;   // Set color; Darker to bright 
			writeBuff[1] = 0x00 | DATA;
			writeBuff[2] = j/2  | DATA;
			spi_cycle(writeBuff, 3);	
		}
	}	
    
    // BLUE
    writeBuff[0] =0x15 | CMD;		    // Set Column Address
    writeBuff[1] =0x20 | DATA;		    // Default => 0x00 (Start Address)
    writeBuff[2] =0x3f | DATA;			// Default => 0x7F (End Address)		
	spi_cycle(writeBuff, 3);	
	
    writeBuff[0] =0x75 | CMD;			// Set Row Address
	writeBuff[1] =0x00 | DATA;			// Default => 0x00 (Start Address)
    writeBuff[2] =0x7f | DATA;			// Default => 0x7F (End Address)	
    spi_cycle(writeBuff, 3);	
    	
    writeBuff[0] =0x5C | CMD;			// Enable MCU to Write into RAM	 
    spi_cycle(writeBuff, 1);	
	for(i=0;i<32;i++)
	{
		for(j=0;j<128;j++)
		{
			writeBuff[0] = j/2  | DATA;  // Set color; Darker to bright 
			writeBuff[1] = 0x00 | DATA;
			writeBuff[2] = 0x00 | DATA;
			spi_cycle(writeBuff, 3);	
		}
	}		

    // GREEN
    writeBuff[0] =0x15 | CMD;		    // Set Column Address
    writeBuff[1] =0x40 | DATA;		    // Default => 0x00 (Start Address)
    writeBuff[2] =0x5f | DATA;			// Default => 0x7F (End Address)		
	spi_cycle(writeBuff, 3);	
	
    writeBuff[0] =0x75 | CMD;			// Set Row Address
	writeBuff[1] =0x00 | DATA;			// Default => 0x00 (Start Address)
    writeBuff[2] =0x7f | DATA;			// Default => 0x7F (End Address)
    spi_cycle(writeBuff, 3);		
    	
    writeBuff[0] =0x5C | CMD;			// Enable MCU to Write into RAM	 
    spi_cycle(writeBuff, 1);	
	for(i=0;i<32;i++)
	{
		for(j=0;j<128;j++)
		{
			writeBuff[0] = 0x00 | DATA;      // Set color; Darker to bright 
			writeBuff[1] = j/2  | DATA;
			writeBuff[2] = 0x00 | DATA;
			spi_cycle(writeBuff, 3);	
		}
	}		

    // WHITE
    writeBuff[0] =0x15 | CMD;		    // Set Column Address
    writeBuff[1] =0x60 | DATA;		    // Default => 0x00 (Start Address)
    writeBuff[2] =0x7f | DATA;			// Default => 0x7F (End Address)	
    spi_cycle(writeBuff, 3);		
		
    writeBuff[0] =0x75 | CMD;			// Set Row Address
	writeBuff[1] =0x00 | DATA;			// Default => 0x00 (Start Address)
    writeBuff[2] =0x7f | DATA;			// Default => 0x7F (End Address)	
    spi_cycle(writeBuff, 3);	
    	
    writeBuff[0] =0x5C | CMD;			// Enable MCU to Write into RAM	 
    spi_cycle(writeBuff, 1);	
	for(i=0;i<32;i++)
	{
		for(j=0;j<128;j++)
		{
			writeBuff[0] =j / 2 | DATA;   // Set color; Darker to bright 
			writeBuff[1] =j / 2 | DATA;
			writeBuff[2] =j / 2 | DATA;
			spi_cycle(writeBuff, 3);	
		}
	}		 	
	
	return 0;
}

void oledWrite( Uint16 type, Uint16 val)
{
	writeBuff[0] = val | type;  // Command Lock
	spi_cycle(writeBuff, 1);
	
	return;
}

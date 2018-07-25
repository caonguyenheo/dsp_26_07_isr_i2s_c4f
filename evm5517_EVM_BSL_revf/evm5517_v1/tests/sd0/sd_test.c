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


#include "mmcsd.h"
#include "stdio.h"
#include "evm5517_i2cgpio.h"

Uint16 id[128];
Uint16 tx[128];
Uint16 rx[128];

/*
 *
 *  SD Init
 *
 */
void sd_init( )
{
}

/*
 *
 *  SD Card Detect
 *
 */
Int16 sd_card_detect( )
{
    Uint8 current_state;

	EVM5517_I2CGPIO_configLine(  10, 1 );
	return EVM5517_I2CGPIO_readLine(  10);
}

/*
 *
 *  SD Test
 *
 */
Uint16 sd_test( )
{
    Uint16 i;
    Uint16 errorflag    = 0;
    Uint32 relCardAddr  = 2;
    Uint32 cardAddr     = 4096;
    Uint32 blkLength    = 512;

    printf("SW6 VDD_IO1 must be ON, 3.3V required for SD card\n");
    MMCSD_cardStatusReg cardStatus;
    MMCSD_ConfigData    mmcsdConfig2 = {
        MMCSD_LITTLE_ENDIAN,  // write Endian
        MMCSD_LITTLE_ENDIAN,  // read Endian
        MMCSD_DAT3_DISABLE,   // Edge Detection disbale
        0,                    // SpiModeEnable
        0,                    // csEnable
        0,                    // spiCrcEnable
        0,
        0,                    // SpiModeEnable
        0,                    // csEnable
        0,                    // spiCrcEnable
        MMCSD_DATA_BUS_4,     // data bus width
        0xFF,                 // response timeout
        0xFFFF                // data read timeout
    };

    /*
     *  Fill tx buffer and clear rx buffer
     */
    for( i = 0 ; i < 128 ; i++ )
    {
        tx[i]= i;
        rx[i]= 0;
    }

    if ( sd_card_detect( ) )
    {
    	printf( "SD card not detected.\n" );
        return 1;
    }

    /* Setup MUX for MMC0 */	
	EVM5517_I2CGPIO_configLine(  8, 0 );
	EVM5517_I2CGPIO_writeLine(  8, 0 );

    if( MMCSD_initCard( &relCardAddr, &cardStatus, &mmcsdConfig2,
                         MMCSD_FIFOLEVEL_32BYTES ) )
    {
        printf( "SD Card Initialization failed\n" );
        return 1;
    }

    /*
     *  Write Block
     */
    if ( MMCSD_singleBlkWrite( cardAddr, ( Uint32* )tx, blkLength, 0 ) )
    {
        printf( "ERROR : SD Write block\n" );
        return 1;
    }

    /*
     *  Read Block
     */
    if ( MMCSD_singleBlkRead( cardAddr, ( Uint32* )rx, blkLength, 0 ) )
    {
        printf( "ERROR : SD Read block\n" );
        return 1;
    }

    /*
     * Compare tx and Rx Buffers
     */
    for ( i = 0 ; i < 128 ; i++ )
    {
        if ( rx[i] != tx[i] )
        {
            errorflag++;
            break;
        }
    }

    return errorflag;
}

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


#define AIC3204_I2C_ADDR 0x18

#include "evm5517.h"
#include "evm5517_gpio.h"
#include "evm5517_i2c.h"
#include "evm5517_i2cgpio.h"
#include "stdio.h"

extern Int16 aic3204_tone_headphone( );
extern Int16 aic3204_tone_stereo_out( );
extern Int16 aic3204_loop_stereo_in1( );
extern Int16 aic3204_loop_stereo_in2( );
extern Int16 aic3204_loop_mic_in( );

/*
 *
 *   AIC3204_rget( regnum, regval )
 *
 *      Return value of codec register regnum
 *
 */
Int16 AIC3204_rget(  Uint16 regnum, Uint16* regval )
{
    Int16 retcode = 0;
    Uint8 cmd[2];

    cmd[0] = regnum & 0x007F;       // 7-bit Device Address
    cmd[1] = 0;

    retcode |= EVM5517_I2C_write( AIC3204_I2C_ADDR, cmd, 1 );
    retcode |= EVM5517_I2C_read( AIC3204_I2C_ADDR, cmd, 1 );

    *regval = cmd[0];
    EVM5517_wait( 10 );
    return retcode;
}

/*
 *
 *   AIC3204_rset( regnum, regval )
 *
 *      Set codec register regnum to value regval
 *
 */
Int16 AIC3204_rset( Uint16 regnum, Uint16 regval )
{
    Uint8 cmd[2];
    cmd[0] = regnum & 0x007F;       // 7-bit Register Address
    cmd[1] = regval;                // 8-bit Register Data

    return EVM5517_I2C_write( AIC3204_I2C_ADDR, cmd, 2 );
}

/*
 *
 *  aic3204_test( )
 *
 */
Int16 aic3204_test( )
{
	Uint16 regval;
	Int16 i;

    /* Test Instructions */
	printf("For this test, make sure J27 (1-3=Off, 2-4=Off)\n");
    printf("                         J28 (1-3=Off, 2-4=Off)\n");
    printf("                         J29 (1-3=On,  2-4=On)\n");
    printf("                         J30 (1-3=On,  2-4=On)\n\n");

    /* Configure Serial Port 0 */
    SYS_EXBUSSEL &= ~0x7300;   // 
    SYS_EXBUSSEL |=  0x4100;   // Enable I2S2 pins

    /* Configure I2C mux for AIC3204-2 */	
    EVM5517_I2CGPIO_configLine(  2, 0 );
    EVM5517_I2CGPIO_writeLine(  2, 1 );  // SEL_I2C_S0 = 1

    EVM5517_I2CGPIO_configLine(  3, 0 );
    EVM5517_I2CGPIO_writeLine(  3, 0 );  // SEL_I2C_S1 = 0

//    EVM5517_I2CGPIO_configLine(  4, 0 );
//    EVM5517_I2CGPIO_writeLine(  4, 0 );  // HPI_ON = 0

    /* Configure SPI2 mux for AIC3204-2 */
	EVM5517_I2CGPIO_configLine(  5, 0 );
    EVM5517_I2CGPIO_writeLine(  5, 1 );  // SPI_I2S2_S0 = 1

    EVM5517_I2CGPIO_configLine(  6, 0 );
    EVM5517_I2CGPIO_writeLine(  6, 1 );  // SPI_I2S2_S1 = 1

    /* Release AIC3204 reset */
    EVM5517_I2CGPIO_configLine(  0, 0 );
    EVM5517_I2CGPIO_writeLine(  0, 0 );  // AIC_RST = 0

    /* Codec tests */
    printf( " -> 1 KHz Tone on Headphone.\n" );
    if ( aic3204_tone_headphone( ) )
        return 1;
       
    EVM5517_wait( 100 );  // Wait 
    printf( " -> 1 KHz Tone on Stereo OUT.\n" );
    if ( aic3204_tone_stereo_out( ) )
        return 1;
       
    EVM5517_wait( 100 );  // Wait    
    printf( "<-> Audio Loopback from Stereo IN 1 --> to HP\n" );
    if ( aic3204_loop_stereo_in1( ) )
        return 1;
        
    EVM5517_wait( 100 );  // Wait    
    printf( "<-> Audio Loopback from Stereo IN 2 --> to Stereo OUT\n" );
    if ( aic3204_loop_stereo_in2( ) )
        return 1;
    
    EVM5517_wait( 100 );  // Wait    
    printf( "<-> Microphone --> to HP\n" );
    if ( aic3204_loop_mic_in( ) )
        return 1;

	EVM5517_GPIO_setOutput( GPIO26, 0 );
    return 0;
}

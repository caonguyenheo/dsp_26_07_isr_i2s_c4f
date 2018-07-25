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

#include "stdio.h"
#include "evm5517.h"

extern Int16 AIC3204_rset( Uint16 regnum, Uint16 regval);

#define Rcv 0x08
#define Xmit 0x20

/*
 *
 *  aic3204_loop_mic_in( )
 *      Output the sound from the Microphone on the HEADPHONE jack
 *
 */
Int16 aic3204_loop_mic_in( )
{
    /* Pre-generated sine wave data, 16-bit signed samples */
    Int16 j, i = 0;
    Int16 sample, data1, data2, data3, data4;
   
     /* Configure AIC3204 */
    AIC3204_rset(  0, 0x00 );      // Select page 0
    AIC3204_rset(  1, 0x01 );      // Reset codec
    AIC3204_rset(  0, 0x01 );      // Point to page 1
    AIC3204_rset(  1, 0x08 );      // Disable crude AVDD generation from DVDD
    AIC3204_rset(  2, 0x00 );      // Enable Analog Blocks
    /* PLL and Clocks config and Power Up */
    AIC3204_rset(  0, 0x00 );      // Select page 0
    AIC3204_rset( 27, 0x00 );      // BCLK and WCLK is set as i/p to AIC3204(Slave)
    AIC3204_rset(  4, 0x07 );      // PLL setting: PLLCLK <- BCLK and CODEC_CLKIN <-PLL CLK
    AIC3204_rset(  6, 0x20 );      // PLL setting: J=32
    AIC3204_rset(  7, 0 );         // PLL setting: HI_BYTE(D = 0)
    AIC3204_rset(  8, 0 );         // PLL setting: LO_BYTE(D) = 0
    /* For 48 KHz sampling */
    AIC3204_rset(  5, 0x92 );      // PLL setting: Power up PLL, P=1 and R=2
    AIC3204_rset( 13, 0x00 );      // Hi_Byte(DOSR) for DOSR = 128 decimal or 0x0080 DAC oversamppling
    AIC3204_rset( 14, 0x80 );      // Lo_Byte(DOSR) for DOSR = 128 decimal or 0x0080
    AIC3204_rset( 20, 0x80 );      // AOSR for AOSR = 128 decimal or 0x0080 for decimation filters 1 to 6
    AIC3204_rset( 11, 0x88 );      // Power up NDAC and set NDAC value to 8
    AIC3204_rset( 12, 0x82 );      // Power up MDAC and set MDAC value to 2
    AIC3204_rset( 18, 0x88 );      // Power up NADC and set NADC value to 8
    AIC3204_rset( 19, 0x82 );      // Power up MADC and set MADC value to 2
    /* DAC ROUTING and Power Up */
    AIC3204_rset(  0, 0x01 );      // Select page 1
    AIC3204_rset( 12, 0x08 );      // LDAC AFIR routed to HPL
    AIC3204_rset( 13, 0x08 );      // RDAC AFIR routed to HPR
    AIC3204_rset(  0, 0x00 );      // Select page 0
    AIC3204_rset( 64, 0x02 );      // Left vol=right vol
    AIC3204_rset( 65, 0x00 );      // Left DAC gain to 0dB VOL; Right tracks Left
    AIC3204_rset( 63, 0xd4 );      // Power up left,right data paths and set channel
    AIC3204_rset(  0, 0x01 );      // Select page 1
    AIC3204_rset( 16, 0x06 );      // Unmute HPL , 6dB gain
    AIC3204_rset( 17, 0x06 );      // Unmute HPR , 6dB gain
    AIC3204_rset(  9, 0x30 );      // Power up HPL,HPR
    AIC3204_rset(  0, 0x00 );      // Select page 0
    EVM5517_wait( 500 );           // Wait
    /* ADC ROUTING and Power Up */
    AIC3204_rset(  0, 0x01 );      // Select page 1
    AIC3204_rset( 51, 0x40 );      // SetMICBIAS
    AIC3204_rset( 52, 0xc0 );      // STEREO 1 Jack
		                           // IN2_L to LADC_P through 40 kohm
    AIC3204_rset( 55, 0xc0 );      // IN2_R to RADC_P through 40 kohmm
    AIC3204_rset( 54, 0x03 );      // CM_1 (common mode) to LADC_M through 40 kohm
    AIC3204_rset( 57, 0xc0 );      // CM_1 (common mode) to RADC_M through 40 kohm
    AIC3204_rset( 59, 0x5f );      // MIC_PGA_L unmute
    AIC3204_rset( 60, 0x5f );      // MIC_PGA_R unmute
    AIC3204_rset(  0, 0x00 );      // Select page 0
    AIC3204_rset( 81, 0xc0 );      // Powerup Left and Right ADC
    AIC3204_rset( 82, 0x00 );      // Unmute Left and Right ADC
    
    AIC3204_rset( 0,  0x00 );    
    EVM5517_wait( 200 );           // Wait
        
    /* I2S settings */
    I2S2_SRGR = 0x0015;
    I2S2_ICMR = 0x0028;    // Enable interrupts
    I2S2_CR   = 0x8012;    // 16-bit word, Master, enable I2S
    
    /* Play Tone */
    for( i = 0 ; i < 5 ; i++ )
    {
        for ( j = 0 ; j < 1000 ; j++ )
        {
            for ( sample = 0 ; sample < 48 ; sample++ )
            {
				/* Read Digital audio input */
                data3 = I2S2_W0_MSW_R;
      	        data1 = I2S2_W0_LSW_R;
      	        data4 = I2S2_W1_MSW_R;
      	        data2 = I2S2_W1_LSW_R;
            	while((Rcv & I2S2_IR) == 0);  // Wait for interrupt
				I2S2_W0_MSW_W = data3;
      	        I2S2_W0_LSW_W = 0;
      	        I2S2_W1_MSW_W = data4;
      	        I2S2_W1_LSW_W = 0;
                while((Xmit & I2S2_IR) == 0);  // Wait for interrupt
            }
        }
    }
    /* Disble I2S */
    I2S2_CR = 0x00;
   
    return 0;
}

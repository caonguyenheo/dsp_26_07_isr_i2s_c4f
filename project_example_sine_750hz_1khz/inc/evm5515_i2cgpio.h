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


#include "evm5515.h"
#include "evm5515_i2c.h"

#define I2CGPIO_I2C_ADDR 0x21

/* I2C GPIO lines */
#define I2C_P01       0
#define I2C_P00       1
#define SW1           2
#define SW0           3
#define LED3          4
#define LED2          5
#define LED1          6
#define LED0          7
#define I2C_P10       8
#define I2C_P11       9
#define I2C_P12       10
#define FTDI_UARTn    11
#define BSP_SEL1_ENn  12
#define BSP_SEL1      13
#define BSP_SEL0_ENn  14
#define BSP_SEL0      15

/* I2C GPIO direction */
#define OUT           0
#define IN            1

/* I2C GPIO STATE */
#define LOW           0
#define HIGH          1 

/* ------------------------------------------------------------------------ *
 *  Prototypes                                                              *
 * ------------------------------------------------------------------------ */
Int16 EVM5515_I2CGPIO_configLine(  Uint16 line, Uint16 dir );
Int16 EVM5515_I2CGPIO_readLine(  Uint16 line );
Int16 EVM5515_I2CGPIO_writeLine(  Uint16 line, Uint16 val );
Int16 EVM5515_I2CGPIO_read(  Uint16 num, Uint16* val );
Int16 EVM5515_I2CGPIO_write( Uint16 num, Uint16 val );

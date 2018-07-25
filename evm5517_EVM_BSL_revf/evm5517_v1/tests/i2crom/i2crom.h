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


#include "evm5517_i2c.h"

/* ------------------------------------------------------------------------ *
 *  I2C Address                                                             *
 * ------------------------------------------------------------------------ */
#define EEPROM_I2C_ADDR             0x50

/* ------------------------------------------------------------------------ *
 *  EEPROM Memory Settings                                                  *
 * ------------------------------------------------------------------------ */
#define EEPROM_PAGE_SIZE            64
#define EEPROM_PAGE_SIZE_POW2       6
#define EEPROM_MAX_BURST_LEN        EEPROM_PAGE_SIZE

/* ------------------------------------------------------------------------ *
 *  Prototypes                                                              *
 * ------------------------------------------------------------------------ */
Int16 i2crom_init ( );
Int16 i2crom_read ( Uint32 src, Uint32 dst, Uint32 length );
Int16 i2crom_write( Uint32 src, Uint32 dst, Uint32 length );

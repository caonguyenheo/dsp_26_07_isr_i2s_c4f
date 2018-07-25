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
#include "i2crom.h"

/*
 *
 *  i2crom_init( )
 *      Initialize the I2C EEPROM
 *
 */
Int16 i2crom_init( )
{
    return EVM5517_I2C_init( );
}

/*
 *
 *  i2crom_read( src, dst, length )
 *      Read from the I2C EEPROM
 *
 */
Int16 i2crom_read( Uint32 src, Uint32 dst, Uint32 length )
{
    Uint8 addr[2];
    Uint8 *input = ( Uint8* )dst;

    addr[0] = src >> 8;         // HIGH address
    addr[1] = src & 0xff;       // LOW address

    /* Send 16-bit address */
    if ( EVM5517_I2C_write( EEPROM_I2C_ADDR, addr, 2 ) )
        return -1;

    /* Wait for EEPROM to process */
    EVM5517_waitusec( 1000 );

    /* Read data */
    if ( EVM5517_I2C_read ( EEPROM_I2C_ADDR, input, length ) )
        return -1;

    return 0;
}

/*
 *
 *  i2crom_write( src, dst, length )
 *      Write to the I2C EEPROM
 *
 */
Int16 i2crom_write( Uint32 src, Uint32 dst, Uint32 length )
{
    Uint16 i;
    Uint8 cmd[64 + 2];
    Uint8* psrc8 = ( Uint8* )src;
    Uint8* pdst8 = &cmd[2];

    cmd[0] = dst >> 8;       // HIGH address
    cmd[1] = dst & 0xff;     // LOW address

    /* Fill in data */
    for ( i = 0 ; i < length ; i++ )
        *pdst8++ = *psrc8++;

    /* Send 16-bit address and data */
    if ( EVM5517_I2C_write( EEPROM_I2C_ADDR, cmd, 2 + length ) )
        return -1;

    /* Wait for EEPROM to process */
    EVM5517_waitusec( 1000 );

    return 0;
}

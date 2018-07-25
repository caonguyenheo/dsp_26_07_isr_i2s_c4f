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
#include "evm5517_i2cgpio.h"

/*
 *
 *  EVM5517_I2CGPIO_configLine( line, dir )
 *
 *      Uint16 line        <-  I2C GPIO line (defined in EVM5517_i2cgpio.h)
 *      Uint16 dir         <-  I2C GPIO direction (defined in EVM5517_i2cgpio.h)
 * 
 *  Description
 *      Configure the I2C GPIO line as input or output.
 *
 */
Int16 EVM5517_I2CGPIO_configLine(  Uint16 line, Uint16 dir )
{
    Uint16 regnum;
    Uint16 regval;
    Uint16 bit = 0;
    
    if(line < 8)
        regnum = 6;
    else
    {
        regnum = 7;
        line = line - 8;
    }
        
    EVM5517_I2CGPIO_read(  regnum, &regval );
    
    bit = 1 << line;
    regval &= ~bit;
    dir = dir << line;
    regval = regval | dir; 
    
    EVM5517_I2CGPIO_write( regnum, regval );
    
    return 0;
}

/*
 *
 *  EVM5517_I2CGPIO_readLine( line )
 *
 *      Uint16 line        <-  I2C GPIO line (defined in EVM5517_i2cgpio.h)
 * 
 *      Returns:           ->  I2C GPIO STATE (defined in EVM5517_i2cgpio.h)
 * 
 *  Description
 *      Returns the state of I2C GPIO "line" as state high or low.
 *
 */
Int16 EVM5517_I2CGPIO_readLine(  Uint16 line )
{
    Uint16 regnum;
    Uint16 regval;
    
    if(line < 9)
        regnum = 0;
    else
    {
        regnum = 1;
        line = line - 8;
    }
    EVM5517_I2CGPIO_read(  regnum, &regval );
    
    return ((regval >> line) & 0x01);
}

/*
 *
 *  EVM5517_I2CGPIO_writeLine(  line, val )
 *
 *      Uint16 line        <-  I2C GPIO line  (defined in EVM5517_i2cgpio.h)
 *      Uint16 val         <-  I2C GPIO state (defined in EVM5517_i2cgpio.h)
 * 
 *  Description
 *      Sets the state of I2C GPIO "line" as state high or low.
 *
 */
Int16 EVM5517_I2CGPIO_writeLine(  Uint16 line, Uint16 val )
{
    Uint16 regnum;
    Uint16 regval;
    Uint16 bit = 0;
    
    if(line < 8)
        regnum = 2;
    else
    {
        regnum = 3;
        line = line - 8;
    }
        
    EVM5517_I2CGPIO_read(  regnum, &regval );
    
    bit = 1 << line;
    regval &= ~bit;
    val = val << line;
    regval = regval | val; 
    
    EVM5517_I2CGPIO_write( regnum, regval );
    
    return 0;
}

/*
 *
 *  EVM5517_I2CGPIO_read( regnum, *regval )
 *
 *      Uint16 regnum       <- I2C GPIO register number
 *      Uint16* regval      <- Pointer to store register value
 * 
 *  Description
 *      Return value of I2C GPIO register regnum to pointer revgal
 *
 */
Int16 EVM5517_I2CGPIO_read(  Uint16 regnum, Uint16* regval )
{
    Int16  retcode = 0;
    Uint8 cmd[2];

    cmd[0] = regnum & 0x007F;     // 7-bit Device Register
    cmd[1] = 0;

    /* Send AIC3204 register name */
    retcode |= EVM5517_I2C_write( I2CGPIO_I2C_ADDR, cmd, 1 );
    
    /* Return register value */
    retcode |= EVM5517_I2C_read( I2CGPIO_I2C_ADDR, cmd, 1 );
    *regval = cmd[0];
    EVM5517_waitusec( 50 );
    
    return retcode;
}

/*
 *
 *  EVM5517_I2CGPIO_write( regnum, regval )
 *
 *      Uint16 regnum       <- I2C GPIO register number
 *      Uint16 regval       <- Value to write into 8-bit register
 * 
 *  Description
 *      Writes the value regval to the I2C GPIO register regnum
 *
 */
Int16 EVM5517_I2CGPIO_write( Uint16 regnum, Uint16 regval )
{
    Uint8 cmd[2];
    
    cmd[0] = regnum & 0x007F;  // 7-bit Device Register
    cmd[1] = regval;           // 8-bit Register Data

    EVM5517_waitusec( 100 );

    /* Write to AIC3204 Register */
    return EVM5517_I2C_write( I2CGPIO_I2C_ADDR, cmd, 2 );
}


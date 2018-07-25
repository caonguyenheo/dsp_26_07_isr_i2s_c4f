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
#include "evm5517_i2c.h"
#include "stdio.h"

Uint8 check[20];
Uint8 found[20];
Uint8 num;
Uint8 cnt;

/*

 *  i2cChecker_test( )
 *    Checks if all the I2C devices are responsive. Also finds
 *    addresses unaccounted for.
 */
Int16 i2cChecker_test( )
{
    Int16 i, j, error = 0, find;
   	Uint8 cmd[5];

   	num = 3;
   	check[0] = 0x18;
   	check[1] = 0x21;
   	check[2] = 0x50;

   	printf("Printing out all valid I2C addresses\n");
   	printf("Install jumpers on JP7 2-4 and JP11 2-4 to add INA219 power measurement devices\n");
   	cnt = 0;

    for (i=1; i < 127; i++ )
    {
        /*I2C write*/
        cmd[0] = 3 & 0x007F;       // 7-bit Device Address
        cmd[1] = 0;
        j = EVM5517_I2C_write( i, cmd, 1 );
		if (j==0)
		{
		    printf("I2C address 0x%x is valid\n",i);
		    found[cnt] = i;
		    cnt++;
		}
		else
		{
            EVM5517_I2C_reset( );
		}
		
		EVM5517_waitusec(50000);
    }

    for (i = 0; i < cnt; i++ )
    {
    	find = 0;
        for (j = 0; j < num; j++ )
        {
        	if(found[i] == check[j])
        		find = 1;
        }
        if(find == 0)
        	printf("Found additional address 0x%x\n",found[i]);
    }

    return error;
}


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


#include "usb.h"
#include "sar.h"

Uint16 preKey =NoKey;
Uint16 keyCnt1 =0;
Uint16 keyCnt2 =0;

void Init_SAR(void)
{
    *SARCTRL = 0x3C00;                      // select AIN3, which is GPAIN1
    //*SARDATA; 
    *SARCLKCTRL = 0x0031;                   // 100/50 = 2MHz 
    *SARPINCTRL = 0x7104;
    *SARGPOCTRL = 0; 
}

void Read_GPAIN1(void)
{
    Uint16 val, i;

    for(i=0;i<30; i++)
        asm("	nop");     

    while(1)
    {
        
        for(i=0;i<100; i++)
            asm("	nop");     

		*SARCTRL = 0xB400;     

        while(1)
        {
            for(i=0;i<50; i++)
                asm("	nop");     
            val = *SARDATA;
            if((val&0x8000) == 0)
                break;
        }
    }
}

Uint16 Get_Sar_Key(void)
{
    Uint16 val, i;

    //keyCnt1++;
    //if(keyCnt1 < 0x7FFF)
    //    return(NoKey);
    
    //keyCnt1=0;
    keyCnt2++;
    if(keyCnt2 > 90)   
    {
        keyCnt2=0;
        preKey = NoKey;
    }
    
    
	*SARCTRL = 0xB800;     
    while(1)
    {
        for(i=0;i<500; i++)
            asm("	nop");     
        val = *SARDATA;
        if((val&0x8000) == 0)
            break;
    }
    
    if(val == NoKey)
    {
        return val;
    }
    else if((val==SW10)||(val==SW11)||(val==SW12)||(val==SW14)||(val==SW7)||(val==SW6)||(val==SW8)||(val==SW13))
    {
        if(val != preKey)
        {
            preKey = val;
            return val;
        }
		else
		{
			return val;
		}

    }
    else
    {
        return val;
    }
    
    
}


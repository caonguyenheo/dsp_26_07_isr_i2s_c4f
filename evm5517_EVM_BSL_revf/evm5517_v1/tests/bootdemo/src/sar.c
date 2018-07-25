/**********************************************************************
**+-----------------------------------------------------------------+**
**|                            ****                                 |**
**|                            ****                                 |**
**|                            ******o***                           |**
**|                      ********_///_****                          |**
**|                      ***** /_//_/ ****                          |**
**|                       ** ** (__/ ****                           |**
**|                           *********                             |**
**|                            ****                                 |**
**|                            ***                                  |**
**|                                                                 |**
**|   Copyright (c) 2006 - 2010    Texas Instruments Incorporated   |**
**|                        ALL RIGHTS RESERVED                      |**
**|                                                                 |**
**| Permission is hereby granted to licensees of Texas Instruments  |**
**| Incorporated (TI) products to use this computer program for     |**
**| the sole purpose of implementing a licensee product based       |**
**| on TI products.No other rights to reproduce, use, or            |**
**| disseminate this computer program, whether in part or in whole, |**
**| are granted.TI makes no representation or warranties with       |**
**| respect to the performance of this computer program, and        |**
**| specifically disclaims any responsibility for any damages,      |**
**| special or consequential,connected with the use of this program.|**
**|                                                                 |**
**+-----------------------------------------------------------------+**
**********************************************************************/

#include "data_types.h"
#include "sar.h"

static int keylookup[11] = {
    1018,  // Index 0  = NoKey
     882,  // Index 1  = SW8
     599,  // Index 2  = SW9
     789,  // Index 3  = SW10
     565,  // Index 4  = SW13
     534,  // Index 5  = SW14
     472,  // Index 6  = SW15
     359,  // Index 7  = SW16
     0,    // Index 8  = SW17
     710,  // Index 9  = SW18
     216,  // Index 10 = SW19
};



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
    Uint16 val, i, keymatch, retval, delay;

	*SARCTRL = 0xB800;     
    while(1)
    {
        for(i=0;i<500; i++)
            asm("	nop");     
        val = *SARDATA;
        if((val&0x8000) == 0)
            break;
    }
    
    retval = NoKey;
    keymatch = NoKey;
    for (i = 0; i <= 10; i++)
    {
        if (((int)val < keylookup[i] + 4) && ((int)val > keylookup[i] - 4))
        {
            if ((i == preKey) && (preKey != NoKey))
            {
                retval = i;
                break;
            } else
            {
                retval = NoKey;   // Simple debounce, reject single anomalous values
                preKey = i;
                for (delay = 0; delay < 1000; delay++)
                    delay++;
                break;
            }
        }
    }

    return retval;
}


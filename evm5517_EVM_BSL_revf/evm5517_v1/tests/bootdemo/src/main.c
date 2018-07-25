/******************************************************************************
**+-------------------------------------------------------------------------+**
**|                            ****                                         |**
**|                            ****                                         |**
**|                            ******o***                                   |**
**|                      ********_///_****                                  |**
**|                      ***** /_//_/ ****                                  |**
**|                       ** ** (__/ ****                                   |**
**|                           *********                                     |**
**|                            ****                                         |**
**|                            ***                                          |**
**|                                                                         |**
**|         Copyright (c) 2006 - 2010    Texas Instruments Incorporated     |**
**|                        ALL RIGHTS RESERVED                              |**
**|                                                                         |**
**| Permission is hereby granted to licensees of Texas Instruments          |**
**| Incorporated (TI) products to use this computer program for the sole    |**
**| purpose of implementing a licensee product based on TI products.        |**
**| No other rights to reproduce, use, or disseminate this computer         |**
**| program, whether in part or in whole, are granted.                      |**
**|                                                                         |**
**| TI makes no representation or warranties with respect to the            |**
**| performance of this computer program, and specifically disclaims        |**
**| any responsibility for any damages, special or consequential,           |**
**| connected with the use of this program.                                 |**
**|                                                                         |**
**+-------------------------------------------------------------------------+**
******************************************************************************/

#include "data_types.h"
#include "register_system.h"
#include "register_cpu.h"
#include "lcd.h"
#include "sar.h"
#include "rtc.h"
#include "control.h"
#include "i2s.h"
#include "dma.h"
#include "timer.h"
#include "evm5517.h"
#include "evm5517_i2c.h"
#include "evm5517_i2cgpio.h"
#include <stdio.h>

void InitSystem(void);
void ConfigPort(void);
void SYS_GlobalIntEnable(void);
void SYS_GlobalIntDisable(void);
void BlinkLED(void);
void play_codec1();
void play_codec2();

Uint16 key;
Uint16 fLedBlinkOn =0;
Uint16 stDMA =0;
Uint16 fSineWave = 0;
Uint16 fMenu = 1;
extern Uint16 Count_RTC;
//extern void AIC3254_init(void);

#define I2CGPIO_I2C_ADDR 0x21

void i2ctest()
{
    Uint8 cmd[2];
    Uint16 i;

    printf("1\n");
#if(0)
    for (i = 0; i < 8; i++)
    {
        cmd[0] = i;     // 7-bit Device Register
        EVM5517_I2C_write( I2CGPIO_I2C_ADDR, cmd, 1 );

        EVM5517_I2C_read( I2CGPIO_I2C_ADDR, cmd, 1 );
        printf("reg[%d] = %02x\n", i, cmd[0]);
    }
    printf("\n");
#endif

//    while(1)
//    {
        EVM5517_I2CGPIO_configLine( 2, 0 );
        EVM5517_waitusec(1000);
//    }

    printf("2\n");
    for (i = 0; i < 8; i++)
    {
        cmd[0] = i;     // 7-bit Device Register
        EVM5517_I2C_write( I2CGPIO_I2C_ADDR, cmd, 1 );

        EVM5517_I2C_read( I2CGPIO_I2C_ADDR, cmd, 1 );
        printf("reg[%d] = %02x\n", i, cmd[0]);
    }
    printf("\n");

    EVM5517_I2CGPIO_configLine( 7, 0 );

    printf("3\n");
    for (i = 0; i < 8; i++)
    {
        cmd[0] = i;     // 7-bit Device Register
        EVM5517_I2C_write( I2CGPIO_I2C_ADDR, cmd, 1 );

        EVM5517_I2C_read( I2CGPIO_I2C_ADDR, cmd, 1 );
        printf("reg[%d] = %02x\n", i, cmd[0]);
    }
    printf("\n");
}

void main(void)
{
    InitSystem();
    ConfigPort();
    EVM5517_init();

    SYS_GlobalIntEnable();
    
    IER0 = 0x0010;      // enable timer int      
    IER1 = 0x0004;      // enable RTC int

    init_LCD(0);
	menu1_on_LCD();

//    i2ctest();

    Init_SAR();
    Timer0Init();
	reset_RTC();
	enable_rtc_second_int();

//	AIC3254_init();
//	set_i2s2_master();
//    enable_i2s2();

    while(1)
    {
		StartTimer0();
//		*(ioport volatile unsigned *)0x0001 = 0x0001;
//		asm("	idle");

        key = Get_Sar_Key();
        
        if(fMenu ==1)
        {
            switch(key)
            {
                case SW9:  // Switch to tone menu
                    if(fMenu ==1)
                    {
                        fMenu =2;
                        fLedBlinkOn=0;
                        draw_line();
                    }                
                break;
                case SW14:
                    // enable LED blinking
                        fLedBlinkOn =1;                
                break;
                case SW15:
                    // disable LED blinking
                        fLedBlinkOn =0;            
                break;
                case SW16:  // Reset RTC
		    		reset_RTC();
                break;
                default:
                    wait(100);
                break;
                
            }

            BlinkLED();
            display_RTC();
        }
        if (fMenu == 2)  {
            switch(key)
            {
                case SW18:
                    if(fMenu ==2)
                    {
                        fMenu =1;
                        menu1_on_LCD();
                    }
                break;
                case SW14:
                    draw_sine_1k();
                    play_codec1();
                    draw_line();
                break;
                case SW15:
                    draw_sine_1k();
                    play_codec2();
                    draw_line();
                break;
                default:
		    		wait(100);
                break;
            }
        }
	}
}

void InitSystem(void)
{
    volatile int i;

    CONFIG_MSW = 0;       // Put PLL in bypass
    PLL_CNTL1 = 0x6300;   // Pll mult = (0x6300 / 256) + 1 = 100
    PLL_CNTL2 = 0x0005;   // PLL reference divider = 5 + 1 = 6, 12MHz / 6 = 2Mhz ref
    PLL_CNTL4 = 0x0000;   // Output divider = 0
    PLL_CNTL3 = 0x0010;   // Normal operating mode

    for (i=0;i<0x7fff;i++);  // Wait for PLL lock (at least  4ms)

    CONFIG_MSW = 1;       // Switch to PLL clock
    
// reset peripherals
    PER_RSTCOUNT = 0x02;
    PER_RESET = 0x00fb;    
    for (i=0; i< 200; i++);
    
}

void ConfigPort(void)
{
    //  configure ports
    PERIPHSEL0 = 0x4A00;        // parallel port: mode 4, serial port: mode 2 
    
}


void SYS_GlobalIntEnable(void)
{
    asm(" BIT (ST1, #ST1_INTM) = #0");
}

void SYS_GlobalIntDisable(void)
{
    asm(" BIT (ST1, #ST1_INTM) = #1");
}

void BlinkLED(void)
{
    Uint16 temp;

    if(fLedBlinkOn ==0)
        return;
            
    if(Count_RTC > 0)
    {
        Count_RTC =0;
        
        temp = ST1_55;
        if((temp&0x2000) == 0)
        {
            // turn on LED
            temp |= 0x2000;
        }
        else
        {
            // turn off LED
            temp &=0xDFFF;
        }
        ST1_55 = temp; 
    }
    
}

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
#ifndef _LCD_H_
#define _LCD_H_

void wait(Uint32 count);
void  cmdWrite(Uint16 cmd, Uint16 cs_flag);
void  dataWrite(Uint16 data, Uint16 cs_flag);
void Delay(int val);
void Delay2(void);
void draw_font(Uint16 startc, Uint16 startl, Uint16 font,Uint16 Color);
void draw_string (Uint16 startc, Uint16 startl, char *pData,Uint16 Color);
void init_LCD(Uint16 cs_flag);      
void menu1_on_LCD(void);
void menu2_on_LCD(void);
void lcd_clear(void);
void draw_sine_1k(void);
void draw_sine_2k(void);
void draw_line(void);

#endif

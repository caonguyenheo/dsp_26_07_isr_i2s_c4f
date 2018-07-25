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
#ifndef _SAR_H_
#define _SAR_H_

void Init_SAR(void);
void Read_GPAIN1(void);
void sar_test(void);
Uint16 Get_Sar_Key(void);

#define SARCTRL   ((ioport volatile unsigned*)0x7012)
#define SARDATA   ((ioport volatile unsigned*)0x7014)
#define SARCLKCTRL   ((ioport volatile unsigned*)0x7016)
#define SARPINCTRL   ((ioport volatile unsigned*)0x7018)
#define SARGPOCTRL   ((ioport volatile unsigned*)0x701A)

#define NoKey 0
#define SW8   1
#define SW9   2
#define SW10  3
#define SW13  4
#define SW14  5
#define SW15  6
#define SW16  7
#define SW17  8
#define SW18  9
#define SW19  10

#endif

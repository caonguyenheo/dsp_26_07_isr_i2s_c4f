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


void Init_SAR(void);
void Read_GPAIN1(void);
void sar_test(void);
Uint16 Get_Sar_Key(void);

#define SARCTRL      ((ioport volatile unsigned*)0x7012)
#define SARDATA      ((ioport volatile unsigned*)0x7014)
#define SARCLKCTRL   ((ioport volatile unsigned*)0x7016)
#define SARPINCTRL   ((ioport volatile unsigned*)0x7018)
#define SARGPOCTRL   ((ioport volatile unsigned*)0x701A)

#define SW6  0x371
#define SW7  0x256
#define SW8  0x313
//#define SW9  0x166
#define SW10 0x215
#define SW11 0x1D6
#define SW12 0x166
#define SW13 0x000
#define SW14 0x2C6
//#define SW15 0x374
#define NoKey 0x3F9



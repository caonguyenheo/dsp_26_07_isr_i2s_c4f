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

#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "stdbool.h"
#include "evm5515.h"
#include <tms320.h>
#include <dsplib.h>



#include "csl_i2s.h"
#include "csl_intc.h"
#include <csl_general.h>
#include "csl_sysctrl.h"


#define ADJTXSYMBLEV        4400
#define OVERFLOW_PN9FSK     1
#define OVERFLOW_MAKEFSK     1

#pragma DATA_SECTION(SigI,".buffer3")
#pragma DATA_ALIGN (SigI, 4)
short SigI[480] = {0};

#pragma DATA_SECTION(SigQ,".buffer3")
#pragma DATA_ALIGN (SigQ, 4)
short SigQ[480] = {0};

#pragma DATA_SECTION(SigQ0,".buffer3")
#pragma DATA_ALIGN (SigQ0, 4)
short SigQ0[480] = {0};

//#pragma DATA_SECTION(SigQ0,".buffer5")
//#pragma DATA_ALIGN (SigQ0, 4)
#pragma DATA_SECTION(g_SigQ_Buff,".buffer3")
short g_SigQ_Buff[2][480];
short SigQ_Unit;
short SigQ_Pos;
short SigQ_Flg;
short SigQ_Valid_Flg;
int bit_pos;
int row_byte_pos;
int column_byte_pos;


short TrxSymbFilBuff[101+2] = {0};
short UpSampFilBuff[101+2]= {0};

#pragma DATA_SECTION(TxSymbFil,".buffer3")
short TxSymbFil[101]=
{
       -264,    -204,    -103,      31,     184,     336,     465,     551,
        574,     523,     394,     193,     -62,    -349,    -632,    -875,
      -1041,   -1097,   -1023,    -809,    -463,     -11,     505,    1031,
       1503,    1854,    2025,    1968,    1657,    1092,     303,    -648,
      -1673,   -2657,   -3471,   -3983,   -4064,   -3609,   -2541,    -825,
       1526,    4452,    7840,   11537,   15352,   19078,   22497,   25407,
      27626,   29017,   29490,   29017,   27626,   25407,   22497,   19078,
      15352,   11537,    7840,    4452,    1526,    -825,   -2541,   -3609,
      -4064,   -3983,   -3471,   -2657,   -1673,    -648,     303,    1092,
       1657,    1968,    2025,    1854,    1503,    1031,     505,     -11,
       -463,    -809,   -1023,   -1097,   -1041,    -875,    -632,    -349,
        -62,     193,     394,     523,     574,     551,     465,     336,
        184,      31,    -103,    -204,    -264
};

#pragma DATA_SECTION(UpSampFil,".buffer3")
short UpSampFil[101]=
{
         27,      30,       0,     -38,     -42,       0,      54,      59,
          0,     -70,     -77,       0,      93,     101,       0,    -118,
       -127,       0,     149,     161,       0,    -185,    -200,       0,
        232,     249,       0,    -286,    -308,       0,     357,     385,
          0,    -448,    -486,       0,     576,     631,       0,    -765,
       -852,       0,    1089,    1255,       0,   -1780,   -2237,       0,
       4506,    9028,   10923,    9028,    4506,       0,   -2237,   -1780,
          0,    1255,    1089,       0,    -852,    -765,       0,     631,
        576,       0,    -486,    -448,       0,     385,     357,       0,
       -308,    -286,       0,     249,     232,       0,    -200,    -185,
          0,     161,     149,       0,    -127,    -118,       0,     101,
         93,       0,     -77,     -70,       0,      59,      54,       0,
        -42,     -38,       0,      30,      27
};

short SymbolTable[4] = {+1, +3, -1, -3}; // mappings symbol
//short SymbolTable[4] = {+3, +1, -1, -3}; // mappings symbol

const unsigned char arPN9[4][128] = {
{0xF,0xF,0x8,0x7,0xB,0x8,0x5,0x9,0xB,0x7,0xA,0x1,0xC,0xC,0x2,0x4,0x5,0x7,0x5,0xE,0x4,0xB,0x9,0xC,0x0,0xE,0xE,0x9,0xE,0xA,0x5,0x0,0x2,0xA,0xB,0xE,0xB,0x4,0x1,0xB,0xB,0x6,0xB,0x0,0x5,0xD,0xF,0x1,0xE,0x6,0x9,0xA,0xE,0x3,0x4,0x5,0xF,0xD,0x2,0xC,0x5,0x3,0x1,0x8,0x0,0xC,0xC,0xA,0xC,0x9,0xF,0xB,0x4,0x9,0x3,0x7,0xE,0x5,0xA,0x8,0x5,0x1,0x3,0xB,0x2,0xF,0x6,0x1,0xA,0xA,0x7,0x2,0x1,0x8,0x8,0x4,0x0,0x2,0x2,0x3,0x2,0x3,0xA,0xB,0x6,0x3,0x8,0x9,0x5,0x1,0xB,0x3,0xE,0x7,0x8,0xB,0x7,0x2,0x9,0x0,0x4,0xC,0xE,0x8,0xF,0xB,0xC,0x0},
{0xF,0xF,0x0,0xF,0x7,0x0,0xB,0x3,0x6,0xF,0x4,0x3,0x9,0x8,0x4,0x8,0xA,0xE,0xB,0xC,0x9,0x7,0x3,0x8,0x1,0xD,0xD,0x3,0xD,0x4,0xA,0x0,0x5,0x5,0x7,0xD,0x6,0x8,0x3,0x7,0x6,0xD,0x6,0x0,0xB,0xB,0xE,0x3,0xC,0xD,0x3,0x5,0xC,0x6,0x8,0xB,0xF,0xA,0x5,0x8,0xA,0x6,0x3,0x0,0x1,0x9,0x9,0x5,0x9,0x3,0xF,0x6,0x9,0x2,0x6,0xF,0xC,0xB,0x5,0x0,0xA,0x2,0x7,0x6,0x5,0xE,0xC,0x3,0x5,0x4,0xE,0x4,0x3,0x1,0x0,0x8,0x0,0x4,0x4,0x6,0x4,0x7,0x5,0x6,0xC,0x7,0x1,0x2,0xA,0x3,0x6,0x7,0xC,0xF,0x1,0x6,0xE,0x5,0x2,0x0,0x9,0x9,0xD,0x1,0xF,0x7,0x8,0x2},
{0xF,0xE,0x1,0xE,0xE,0x1,0x6,0x6,0xD,0xE,0x8,0x7,0x3,0x0,0x9,0x1,0x5,0xD,0x7,0x9,0x2,0xE,0x7,0x0,0x3,0xB,0xA,0x7,0xA,0x9,0x4,0x0,0xA,0xA,0xF,0xA,0xD,0x0,0x6,0xE,0xD,0xA,0xC,0x1,0x7,0x7,0xC,0x7,0x9,0xA,0x6,0xB,0x8,0xD,0x1,0x7,0xF,0x4,0xB,0x1,0x4,0xC,0x6,0x0,0x3,0x3,0x2,0xB,0x2,0x7,0xE,0xD,0x2,0x4,0xD,0xF,0x9,0x6,0xA,0x1,0x4,0x4,0xE,0xC,0xB,0xD,0x8,0x6,0xA,0x9,0xC,0x8,0x6,0x2,0x1,0x0,0x0,0x8,0x8,0xC,0x8,0xE,0xA,0xD,0x8,0xE,0x2,0x5,0x4,0x6,0xC,0xF,0x9,0xE,0x2,0xD,0xC,0xA,0x4,0x1,0x3,0x3,0xA,0x3,0xE,0xF,0x0,0x6},
{0xF,0xC,0x3,0xD,0xC,0x2,0xC,0xD,0xB,0xD,0x0,0xE,0x6,0x1,0x2,0x2,0xB,0xA,0xF,0x2,0x5,0xC,0xE,0x0,0x7,0x7,0x4,0xF,0x5,0x2,0x8,0x1,0x5,0x5,0xF,0x5,0xA,0x0,0xD,0xD,0xB,0x5,0x8,0x2,0xE,0xF,0x8,0xF,0x3,0x4,0xD,0x7,0x1,0xA,0x2,0xF,0xE,0x9,0x6,0x2,0x9,0x8,0xC,0x0,0x6,0x6,0x5,0x6,0x4,0xF,0xD,0xA,0x4,0x9,0xB,0xF,0x2,0xD,0x4,0x2,0x8,0x9,0xD,0x9,0x7,0xB,0x0,0xD,0x5,0x3,0x9,0x0,0xC,0x4,0x2,0x0,0x1,0x1,0x1,0x9,0x1,0xD,0x5,0xB,0x1,0xC,0x4,0xA,0x8,0xD,0x9,0xF,0x3,0xC,0x5,0xB,0x9,0x4,0x8,0x2,0x6,0x7,0x4,0x7,0xD,0xE,0x0,0xE}};

int Pn9_Fsk()
{
    int  i = 0, j = 0, k = 0;
    unsigned short data = 0;
    short oflag = -1;

    //erase data before receiving data
    memset(SigQ0, 0x0, 480);
    memset(SigI, 0x0, 480);
    memset(SigQ, 0x0, 480);
    memset(g_SigQ_Buff, 0x0, 960);
    memset(TrxSymbFilBuff, 0x0, 103);
    memset(UpSampFilBuff, 0x0, 103);

    for(i = 0; i < 24; i++)
    {
        data = 0;
        for(j = 0; j < 2; j++)
        {
            data = data << 1;
            if((arPN9[column_byte_pos][row_byte_pos] & bit_pos))
            {
                data = data | 1;
            }
            bit_pos = bit_pos >> 1;
            if(bit_pos == 0)
            {
                row_byte_pos++;
                bit_pos = 0x08;
            }
            else if(row_byte_pos == 127)
            {
                if(bit_pos == 0x01)
                {
                    row_byte_pos = 0;
                    bit_pos = 0x08;

                }
            }
        }
        SigI[(i*10)] = SymbolTable[data] * ADJTXSYMBLEV;
    }

    oflag = fir2(SigI, TxSymbFil, SigI, TrxSymbFilBuff, 480>>1, 101);  //oflag = 0;
#if OVERFLOW_PN9FSK
    if(oflag == 1)
    {
        UART_PRINT("SigI(0) oflag OVERFLOW IN Pn9_Fsk():%d",oflag);
        return -1;
    }
    else
    {
        UART_PRINT("SigI(0) oflag IN Pn9_Fsk():%d",oflag);
    }
#endif

    //24k→48k up sampling
    for (i=0; i<(480 >>1); i++)
    {
        SigQ[(i*2)] = SigI[i];
        SigQ[(i*2)+1] = SigI[i];
    }

    oflag = fir2(SigQ, UpSampFil, SigQ, UpSampFilBuff, 480, 101);
#if OVERFLOW_PN9FSK
    if(oflag == 1)
    {
        UART_PRINT("SigI(1) oflag OVERFLOW IN Pn9_Fsk():%d",oflag);
        return -1;
    }
    else
    {
        UART_PRINT("SigI(1) oflag IN Pn9_Fsk():%d",oflag);
    }
#endif

/*    memcpy(&g_SigQ_Buff[0][0], SigQ, 480);*/
    for(k = 0; k<480; k++)
    {
        g_SigQ_Buff[0][k] = SigQ[k];
    }

    //Create one more buff
    //bit_pos = 0x08;
    memset(SigI, 0x0, 480);

    for(i = 0; i < 24; i++)
    {
        data = 0;
        for(j = 0; j < 2; j++)
        {
            data = data << 1;
            if((arPN9[column_byte_pos][row_byte_pos] & bit_pos))
            {
                data = data | 1;
            }
            bit_pos = bit_pos >> 1;
            if(bit_pos == 0)
            {
                row_byte_pos++;
                bit_pos = 0x08;
            }
            else if(row_byte_pos == 127)
            {
                if(bit_pos == 0x01)
                {
                    row_byte_pos = 0;
                    bit_pos = 0x08;

                }
                else;
            }
            else;
        }
        SigI[(i*10)] = SymbolTable[data] * ADJTXSYMBLEV;
    }

    oflag = fir2(SigI, TxSymbFil, SigI, TrxSymbFilBuff, 480>>1, 101);  //oflag = 0;
#if OVERFLOW_PN9FSK
    if(oflag == 1)
    {
        UART_PRINT("SigI(2) oflag OVERFLOW IN Pn9_Fsk():%d",oflag);
        return -1;
    }
    else
    {
        UART_PRINT("SigI(2) oflag IN Pn9_Fsk():%d",oflag);
    }
#endif

    //24k→48k up sampling
    for (i=0; i<(480 >>1); i++)
    {
        SigQ[(i*2)] = SigI[i];
        SigQ[(i*2)+1] = SigI[i];
    }

    oflag = fir2(SigQ, UpSampFil, SigQ, UpSampFilBuff, 480, 101);
#if OVERFLOW_PN9FSK
    if(oflag == 1)
    {
        UART_PRINT("SigI(3) oflag OVERFLOW IN Pn9_Fsk():%d", oflag);
        return -1;
    }
    else
    {
        UART_PRINT("SigI(3) oflag IN Pn9_Fsk():%d", oflag);
    }
#endif

/*    memcpy(&g_SigQ_Buff[1][0], SigQ, 480);*/
    for(k = 0; k<480; k++)
    {
        g_SigQ_Buff[1][k] = SigQ[k];
    }

    SigQ_Unit = 0;
    SigQ_Pos = 0;
    SigQ_Flg = 0;
    SigQ_Valid_Flg = 1;

    return  0;
}

int Make_Fsk()
{

    int  i = 0, j = 0, k = 0;
    unsigned short data = 0;
    short  oflag = -1;

    //erase data before receiving data
    memset(SigI, 0x0, 480);

    for(i = 0; i < 24; i++)
    {
        data = 0;
        for(j = 0; j < 2; j++)
        {
            data = data << 1;
            if((arPN9[column_byte_pos][row_byte_pos] & bit_pos))
            {
                data = data | 1;
            }
            bit_pos = bit_pos >> 1;
            if(bit_pos == 0)
            {
                row_byte_pos++;
                bit_pos = 0x08;
            }
            else if(row_byte_pos == 127)
            {
                if(bit_pos == 0x01)
                {
                    row_byte_pos = 0;
                    bit_pos = 0x08;

                }
                else;
            }
            else;
        }
        SigI[(i*10)] = SymbolTable[data] * ADJTXSYMBLEV;
    }

    //fir SigI and check overflow by oflag variable
    oflag = fir2(SigI, TxSymbFil, SigI, TrxSymbFilBuff, 480>>1, 101);  //oflag = 0;
#if OVERFLOW_MAKEFSK
    if(oflag == 1)
    {
        UART_PRINT("SigI(0) oflag OVERFLOW IN Make_Fsk():%d",oflag);
        return -1;
    }
#endif

    //24k→48k up sampling
    for (i=0; i<(480 >>1); i++)
    {
        SigQ[(i*2)] = SigI[i]; // i<<1
        SigQ[(i*2)+1] = SigI[i];
    }

    //fir SigQ and check overflow by oflag variable
    oflag = fir2(SigQ, UpSampFil, SigQ, UpSampFilBuff, 480, 101);
#if OVERFLOW_PN9FSK
    if(oflag == 1)
    {
        UART_PRINT("SigI(0) oflag OVERFLOW IN Make_Fsk():%d",oflag);
        return -1;
    }
#endif

    //copy data
/*    memcpy(&g_SigQ_Buff[(SigQ_Unit + 1) % 2][0], SigQ, 480);*/
    for(k = 0; k<480; k++)
    {
        g_SigQ_Buff[(SigQ_Unit + 1) % 2][k] = SigQ[k];
    }

    return 0;
}


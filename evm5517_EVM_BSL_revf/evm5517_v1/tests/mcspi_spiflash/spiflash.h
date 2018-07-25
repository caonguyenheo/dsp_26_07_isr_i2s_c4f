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

/* ------------------------------------------------------------------------ *
 *  SPI ROM Definitions                                                     *
 * ------------------------------------------------------------------------ */
#define SPIROM_SIZE             0x00008000
#define SPIROM_BASE             0x00000000
#define SPIROM_PAGESIZE         256
#define SPIROM_SECTORSIZE       4096
#define SPIROM_PAGEMASK         0xffffff00
#define SPIROM_SECTORMASK       0xfffff000
/* ------------------------------------------------------------------------ *
 *  SPI ROM Commands                                                        *
 * ------------------------------------------------------------------------ */
#define SPIROM_CMD_WRSR         0x01
#define SPIROM_CMD_WRITE        0x02
#define SPIROM_CMD_READ         0x03
#define SPIROM_CMD_WRDI         0x04
#define SPIROM_CMD_RDSR         0x05
#define SPIROM_CMD_WREN         0x06
#define SPIROM_CMD_ERASESEC     0x20
#define SPIROM_CMD_UNPROTECTSEC 0x39

/* ------------------------------------------------------------------------ *
 *  SPIOCP Module                                                           *
 * ------------------------------------------------------------------------ */
#define MCSPI_BASE                  0x3400
#define MCSPI_REVISION              *(volatile ioport Uint16*)( MCSPI_BASE + 0x100 )
#define MCSPI_SYSCONFIGL            *(volatile ioport Uint16*)( MCSPI_BASE + 0x110 )
#define MCSPI_SYSSTATUSL            *(volatile ioport Uint16*)( MCSPI_BASE + 0x114 )
#define MCSPI_IRQSTATUSL            *(volatile ioport Uint16*)( MCSPI_BASE + 0x118 )
#define MCSPI_IRQSTATUSU            *(volatile ioport Uint16*)( MCSPI_BASE + 0x119 )
#define MCSPI_IRQENABLEL            *(volatile ioport Uint16*)( MCSPI_BASE + 0x11C )
#define MCSPI_IRQENABLEU            *(volatile ioport Uint16*)( MCSPI_BASE + 0x11D )
#define MCSPI_WAKEUPENABLEL         *(volatile ioport Uint16*)( MCSPI_BASE + 0x120 )
//#define MCSPI_SYST                  *(volatile ioport Uint16*)( MCSPI_BASE + 0x20 )
#define MCSPI_MODULCTRLL            *(volatile ioport Uint16*)( MCSPI_BASE + 0x128 )
#define MCSPI_CH0CONFL              *(volatile ioport Uint16*)( MCSPI_BASE + 0x12C )
#define MCSPI_CH0CONFU              *(volatile ioport Uint16*)( MCSPI_BASE + 0x12D )
#define MCSPI_CH0STATL              *(volatile ioport Uint16*)( MCSPI_BASE + 0x130 )
#define MCSPI_CH0CTRLL              *(volatile ioport Uint16*)( MCSPI_BASE + 0x134 )
#define MCSPI_CH0TXL                *(volatile ioport Uint16*)( MCSPI_BASE + 0x138 )
#define MCSPI_CH0TXU                *(volatile ioport Uint16*)( MCSPI_BASE + 0x139 )
#define MCSPI_CH0RXL                *(volatile ioport Uint16*)( MCSPI_BASE + 0x13C )
#define MCSPI_CH0RXU                *(volatile ioport Uint16*)( MCSPI_BASE + 0x13D )
#define MCSPI_CH1CONFL              *(volatile ioport Uint16*)( MCSPI_BASE + 0x140 )
#define MCSPI_CH1CONFU              *(volatile ioport Uint16*)( MCSPI_BASE + 0x141 )
#define MCSPI_CH1STATL              *(volatile ioport Uint16*)( MCSPI_BASE + 0x144 )
#define MCSPI_CH1CTRLL              *(volatile ioport Uint16*)( MCSPI_BASE + 0x148 )
#define MCSPI_CH1TXL                *(volatile ioport Uint16*)( MCSPI_BASE + 0x14C )
#define MCSPI_CH1TXU                *(volatile ioport Uint16*)( MCSPI_BASE + 0x14D )
#define MCSPI_CH1RXL                *(volatile ioport Uint16*)( MCSPI_BASE + 0x150 )
#define MCSPI_CH1RXU                *(volatile ioport Uint16*)( MCSPI_BASE + 0x151 )


/* ------------------------------------------------------------------------ *
 *  Prototype                                                               *
 * ------------------------------------------------------------------------ */
void spirom_init( );
void spirom_erase( Uint32 base, Uint32 length );
void spirom_read( Uint32 src, Uint32 dst, Uint32 length );
void spirom_write( Uint32 src, Uint32 dst, Uint32 length );


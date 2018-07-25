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
 *  SPI Flash Definitions                                                   *
 * ------------------------------------------------------------------------ */
#define spiflash_SIZE               0x400000
#define spiflash_BASE               0x00000000
#define spiflash_PAGESIZE           256
#define spiflash_PAGEMASK           0xffffff00
#define spiflash_SECTORSIZE         4096
#define spiflash_SECTORMASK         0xfffff000

/* ------------------------------------------------------------------------ *
 *  SPI Flash Commands                                                      *
 * ------------------------------------------------------------------------ */
#define spiflash_CMD_WREN           0x06
#define spiflash_CMD_WRDI           0x04
#define spiflash_CMD_RDSR           0x05
#define spiflash_CMD_WRSR           0x01
#define spiflash_CMD_READ           0x03
#define spiflash_CMD_WRITE          0x02
#define spiflash_CMD_ERASEBLK       0xD8
#define spiflash_CMD_ERASESEC       0x20
#define spiflash_CMD_ERASECHIP      0xC7
#define spiflash_CMD_MFGID          0x90
#define spiflash_CMD_UNPROTECTSEC   0x39

/* ------------------------------------------------------------------------ *
 *  SPI Controller                                                          *
 * ------------------------------------------------------------------------ */

#define SPI_SPICC1         *(volatile ioport Uint16*)(0x3000)
#define SPI_SPICC2         *(volatile ioport Uint16*)(0x3001)
#define SPI_SPIDC1         *(volatile ioport Uint16*)(0x3002)
#define SPI_SPIDC2         *(volatile ioport Uint16*)(0x3003)
#define SPI_SPICR1         *(volatile ioport Uint16*)(0x3004)
#define SPI_SPICR2         *(volatile ioport Uint16*)(0x3005)
#define SPI_SPISR1         *(volatile ioport Uint16*)(0x3006)
#define SPI_SPISR2         *(volatile ioport Uint16*)(0x3007)
#define SPI_SPIDR1         *(volatile ioport Uint16*)(0x3008)
#define SPI_SPIDR2         *(volatile ioport Uint16*)(0x3009)

/* ------------------------------------------------------------------------ *
 *  Prototype                                                               *
 * ------------------------------------------------------------------------ */
void spirom_init( );
void spiflash_erase( Uint32 base, Uint32 length );
Uint16 spirom_status_set( Uint8 val);
void spirom_read( Uint32 src, Uint32 dst, Uint32 length );
void spirom_write( Uint32 src, Uint16 dst, Uint32 length );



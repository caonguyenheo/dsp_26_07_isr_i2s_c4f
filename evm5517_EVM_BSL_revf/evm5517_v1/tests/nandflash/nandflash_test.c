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
#include "evm5517.h"
#include "evm5517_emif.h"

#define NANDFLASH_BASE                  0x700000  // Low CS
#define NANDFLASH_BLOCKS                4096
#define NANDFLASH_PAGESPERBLOCK         32
#define NANDFLASH_PAGES                 ((Uint32)NANDFLASH_BLOCKS * (Uint32)NANDFLASH_PAGESPERBLOCK)
#define NANDFLASH_PAGESIZE              512
#define NANDFLASH_SPARESIZE             16

#define NANDFLASH_DATA  *( volatile Uint8* )( NANDFLASH_BASE + 0x00 )
#define NANDFLASH_CLE   *( volatile Uint8* )( NANDFLASH_BASE + 0x2000 )
#define NANDFLASH_ALE   *( volatile Uint8* )( NANDFLASH_BASE + 0x1000 )

#define CMD_READA                   0x00
#define CMD_READB                   0x01
#define CMD_READID                  0x90
#define CMD_PROGRAM                 0x80
#define CMD_PROGRAM_CONFIRM         0x10
#define CMD_ERASE                   0x60
#define CMD_ERASE_CONFIRM           0xd0
#define CMD_STATUS                  0x70
#define CMD_RESET                   0xff

static Uint8 src[NANDFLASH_PAGESIZE + NANDFLASH_SPARESIZE];
static Uint8 dst[NANDFLASH_PAGESIZE + NANDFLASH_SPARESIZE];

Int16 nand_init()
{
    Uint16 mfgid, devid, i;

    // Set EMIF timings
    EMIF_ACS4CR1 = 0x2115;  // 0xFFFD;
    EMIF_ACS4CR2 = 0x0422;  // 0x3FFF;

    NANDFLASH_CLE = CMD_RESET;
    EVM5517_waitusec(100000);

    // Read IDs
    NANDFLASH_CLE = CMD_READID;
    NANDFLASH_ALE = 0x00;

    // Wait for command completion
    EVM5517_wait(1);
    while((EMIF_NANDFSR1 & 0x04) == 0);

    // Get IDs
    mfgid = NANDFLASH_DATA;
    devid = NANDFLASH_DATA;

    printf("NAND MFGID = %02x\n", mfgid);
    printf("NAND DEVID = %02x\n", devid);

    if (devid != 0x36)
        return 1;
  
    return 0;
}

Int16 nand_eraseBlock(Uint32 blocknum)
{
    Uint32 status;

    // Start erase operation
    NANDFLASH_CLE = CMD_RESET;
    NANDFLASH_CLE = CMD_ERASE;
    NANDFLASH_ALE = (blocknum & 0x0007) << 5;
    NANDFLASH_ALE = (blocknum & 0x07f8) >> 3;
    NANDFLASH_ALE = (blocknum & 0x1800) >> 11;
    NANDFLASH_CLE = CMD_ERASE_CONFIRM;

    // Wait for erase completion
    EVM5517_wait(1);
    while((EMIF_NANDFSR1 & 0x04) == 0);

    // Check erase status
    NANDFLASH_CLE = CMD_STATUS;
    status = NANDFLASH_DATA;

    NANDFLASH_CLE = CMD_RESET;
    if (status & 0x01)
        return 1;  // Error
    else
        return 0;  // OK
}

Int16 nand_readPage(Uint32 pagenum, Uint8 *buf)
{
    Uint8 *dptr;
    Uint16 i;

    NANDFLASH_CLE = CMD_READA;
    NANDFLASH_ALE = 0x00;
    NANDFLASH_ALE =  pagenum & 0x000000ff;
    NANDFLASH_ALE = (pagenum & 0x0000ff00) >> 8;
    NANDFLASH_ALE = (pagenum & 0x00030000) >> 16;

    // Wait for read completion
    EVM5517_waitusec(1);
    while((EMIF_NANDFSR1 & 0x04) == 0);

    // Read data
    dptr = buf;
    for (i = 0; i < 256; i++)
        *dptr++ = NANDFLASH_DATA;

    NANDFLASH_CLE = CMD_READB;
    NANDFLASH_ALE = 0x00;
    NANDFLASH_ALE =  pagenum & 0x000000ff;
    NANDFLASH_ALE = (pagenum & 0x0000ff00) >> 8;
    NANDFLASH_ALE = (pagenum & 0x00030000) >> 16;

    // Wait for read completion
    EVM5517_waitusec(1);
    while((EMIF_NANDFSR1 & 0x04) == 0);

    // Read data
    for (i = 0; i < 256; i++)
        *dptr++ = NANDFLASH_DATA;

    return 0;
}

Int16 nand_writePage(Uint32 pagenum, Uint8 *buf)
{
    Uint8 *dptr;
    Uint16 i;
    Uint32 status;

    // Start program operation
    NANDFLASH_CLE = CMD_READA;
    NANDFLASH_CLE = CMD_PROGRAM;
    NANDFLASH_ALE = 0x00;
    NANDFLASH_ALE =  pagenum & 0x000000ff;
    NANDFLASH_ALE = (pagenum & 0x0000ff00) >> 8;
    NANDFLASH_ALE = (pagenum & 0x00030000) >> 16;

    dptr = buf;
    for (i = 0; i < NANDFLASH_PAGESIZE; i++)
        NANDFLASH_DATA = *dptr++;
    NANDFLASH_CLE = CMD_PROGRAM_CONFIRM;

    // Check program status
    NANDFLASH_CLE = CMD_STATUS;
    status = NANDFLASH_DATA;

    // Wait for program completion
    EVM5517_waitusec(1);
    while((EMIF_NANDFSR1 & 0x04) == 0);

    // Check program status
    NANDFLASH_CLE = CMD_STATUS;
    status = NANDFLASH_DATA;

    NANDFLASH_CLE = CMD_RESET;
    if (status & 0x01)
        return 1;  // Error
    else
        return 0;  // OK
}


/*
 *
 *  nandflash_test( )
 *
 *  Test the first 4MB of NAND, uncomment loop limits to test entire
 *  device.  A full device test will take a LONG time.
 */
Int16 nandflash_test( )
{
    Int16 status;
    Uint32 i, j, errors;
    Uint32 counter;

    /* Initialize NAND */
    status = nand_init();

    /* Erase all of NAND */
    printf("Erasing NAND blocks\n");
    errors = 0;
    for (i = 0; i < NANDFLASH_BLOCKS; i++)
        errors += nand_eraseBlock(i);
    printf("--> %d block erase errors\n", errors);
    if (errors > 80)
        return 1;

    /* Clear buffer */
    for (i = 0; i < NANDFLASH_PAGESIZE; i++)
        src[i] = 0xff;

    /* Program all pages */
    printf("Programming NAND pages\n");
    for (j = 0; j < NANDFLASH_PAGES; j++)
    {
        counter = j;
        for (i = 0; i < NANDFLASH_PAGESIZE; i+=4)
        {
            src[i + 0] = counter  & 0x000000ff;
            src[i + 1] = (counter & 0x0000ff00) >> 8;
            src[i + 2] = (counter & 0x00ff0000) >> 16;
            src[i + 3] = (counter & 0xff000000) >> 24;
            counter++;
        }

        nand_writePage(j, src);
    }

    /* Read and compare all pages */
    printf("Comparing data\n");
    errors = 0;
    for (j = 0; j < NANDFLASH_PAGES; j++)
    {
        nand_readPage(j, dst);
        status = 0;
        counter = j;
        for (i = 0; i < NANDFLASH_PAGESIZE; i+=4)
        {
            if (dst[i + 0] != (counter & 0x000000ff))
                status = 1;
            if (dst[i + 1] != ((counter & 0x0000ff00) >> 8))
                status = 1;
            if (dst[i + 2] != ((counter & 0x00ff0000) >> 16))
                status = 1;
            if (dst[i + 3] != ((counter & 0xff000000) >> 24))
                status = 1;
            counter++;
        }
        if (status)
        {
            printf("Error on page %ld\n", j);
            errors++;
        }
    }

    printf("--> %d page verify errors\n", errors);
    if (errors > 8)  // Not all NAND Flash pages may be good, allow for a small number of errors
        return 1;

    return 0;
}

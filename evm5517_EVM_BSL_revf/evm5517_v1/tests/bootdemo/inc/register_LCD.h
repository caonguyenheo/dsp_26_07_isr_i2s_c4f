#ifndef _REG_LCD_H_
#define _REG_LCD_H_
/*********************************************************************
 * Copyright (C) 2003-2004 Texas Instruments Incorporated. 
 * All Rights Reserved 
 *********************************************************************/

//**************************************************************************\
//* Register Overlay Structure
//**************************************************************************/

#define LCD_REVMIN              *(ioport volatile unsigned *)0x2E00
#define LCD_REVMAJ              *(ioport volatile unsigned *)0x2E02
#define LCD_CTRL                *(ioport volatile unsigned *)0x2E04
#define LCD_SATA                *(ioport volatile unsigned *)0x2E08
#define LIDD_CTRL               *(ioport volatile unsigned *)0x2E0C
#define LIDD_CS0_CONF0          *(ioport volatile unsigned *)0x2E10
#define LIDD_CS0_CONF1          *(ioport volatile unsigned *)0x2E11
#define LIDD_CS0_ADDR           *(ioport volatile unsigned *)0x2E14
#define LIDD_CS0_DATA           *(ioport volatile unsigned *)0x2E18
#define LIDD_CS1_CONF0          *(ioport volatile unsigned *)0x2E1C
#define LIDD_CS1_CONF1          *(ioport volatile unsigned *)0x2E1D
#define LIDD_CS1_ADDR           *(ioport volatile unsigned *)0x2E20
#define LIDD_CS1_DATA           *(ioport volatile unsigned *)0x2E24
#define RASTER_CTRL0            *(ioport volatile unsigned *)0x2E28
#define RASTER_CTRL1            *(ioport volatile unsigned *)0x2E29
#define RASTER_TIMING_0L        *(ioport volatile unsigned *)0x2E2C
#define RASTER_TIMING_0M        *(ioport volatile unsigned *)0x2E2D
#define RASTER_TIMING_1L        *(ioport volatile unsigned *)0x2E30
#define RASTER_TIMING_1M        *(ioport volatile unsigned *)0x2E31
#define RASTER_TIMING_2L        *(ioport volatile unsigned *)0x2E34
#define RASTER_TIMING_2M        *(ioport volatile unsigned *)0x2E35
#define RASTER_SUBPANEL0        *(ioport volatile unsigned *)0x2E38
#define RASTER_SUBPANEL1        *(ioport volatile unsigned *)0x2E39
#define LCDDMA_CTRL             *(ioport volatile unsigned *)0x2E40
#define LCDDMA_FB0_BASE0        *(ioport volatile unsigned *)0x2E44
#define LCDDMA_FB0_BASE1        *(ioport volatile unsigned *)0x2E45
#define LCDDMA_FB0_CEILING0     *(ioport volatile unsigned *)0x2E48
#define LCDDMA_FB0_CEILING1     *(ioport volatile unsigned *)0x2E49
#define LCDDMA_FB1_BASE0        *(ioport volatile unsigned *)0x2E4C
#define LCDDMA_FB1_BASE1        *(ioport volatile unsigned *)0x2E4D
#define LCDDMA_FB1_CEILING0     *(ioport volatile unsigned *)0x2E50
#define LCDDMA_FB1_CEILING1     *(ioport volatile unsigned *)0x2E51

#endif

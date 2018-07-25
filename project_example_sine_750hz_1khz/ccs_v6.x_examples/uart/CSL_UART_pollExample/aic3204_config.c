#include "stdio.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"
#include "stdbool.h"
#include "evm5515.h"
#include <tms320.h>
#include <dsplib.h>

#include "evm5515_gpio.h"
#include "evm5515_i2c.h"
#include "evm5515_i2cgpio.h"
#include "stdio.h"

#define AIC3204_I2C_ADDR 0x18
extern Int16 AIC3204_rset( Uint16 regnum, Uint16 regval);

#define Rcv 0x08
#define Xmit 0x20

Int16 AIC3204_rget(  Uint16 regnum, Uint16* regval )
{
    Int16 retcode = 0;
    Uint8 cmd[2];

    cmd[0] = regnum & 0x007F;       // 7-bit Device Address
    cmd[1] = 0;

    retcode |= EVM5515_I2C_write( AIC3204_I2C_ADDR, cmd, 1 );
    retcode |= EVM5515_I2C_read( AIC3204_I2C_ADDR, cmd, 1 );

    *regval = cmd[0];
    EVM5515_wait( 10 );
    return retcode;
}

/*
 *
 *   AIC3204_rset( regnum, regval )
 *
 *      Set codec register regnum to value regval
 *
 */
Int16 AIC3204_rset( Uint16 regnum, Uint16 regval )
{
    Uint8 cmd[2];
    cmd[0] = regnum & 0x007F;       // 7-bit Register Address
    cmd[1] = regval;                // 8-bit Register Data

    return EVM5515_I2C_write( AIC3204_I2C_ADDR, cmd, 2 );
}
int CodecInit()
{

#if 0
    SYS_EXBUSSEL &= ~0x0300;   //
    SYS_EXBUSSEL |=  0x0100;   // Serial Port mode 1 (I2S1 and GP[11:10]).
    /* Configure I2C mux for AIC3204-1 */
    EVM5515_I2CGPIO_configLine(  2, 0 );
    EVM5515_I2CGPIO_writeLine(  2, 0 );  // SEL_I2C_S0 = 0

    EVM5515_I2CGPIO_configLine(  3, 0 );
    EVM5515_I2CGPIO_writeLine(  3, 0 );  // SEL_I2C_S1 = 0

    /* Set AIC_MCBSP_MODE to I2S (disable McBSP) */
    EVM5515_I2CGPIO_configLine(  1, 0 );
    EVM5515_I2CGPIO_writeLine(  1, 1 );  // AIC_MCBSP_MODE = 1

    /* Set SEL_MMC0_I2S to I2S */
    EVM5515_I2CGPIO_configLine(  8, 0 );
    EVM5515_I2CGPIO_writeLine(  8, 1 );  // SEL_MMC0_I2S = 1

    /* Release AIC3204 reset */
    EVM5515_I2CGPIO_configLine(  0, 0 );
    EVM5515_I2CGPIO_writeLine(  0, 0 );  // AIC_RST = 0
#endif

#if 1
    SYS_EXBUSSEL &= ~0x7300;   //
    SYS_EXBUSSEL |=  0x4100;   // Enable I2S2 pins
    EVM5515_I2CGPIO_configLine(  2, 0 );
    EVM5515_I2CGPIO_writeLine(  2, 1 );  // SEL_I2C_S0 = 1

    EVM5515_I2CGPIO_configLine(  3, 0 );
    EVM5515_I2CGPIO_writeLine(  3, 0 );  // SEL_I2C_S1 = 0

    /* Configure SPI2 mux for AIC3204-2 */
    EVM5515_I2CGPIO_configLine(  5, 0 );
    EVM5515_I2CGPIO_writeLine(  5, 1 );  // SPI_I2S2_S0 = 1

    EVM5515_I2CGPIO_configLine(  6, 0 );
    EVM5515_I2CGPIO_writeLine(  6, 1 );  // SPI_I2S2_S1 = 1

    /* Release AIC3204 reset */
    EVM5515_I2CGPIO_configLine(  0, 0 );
    EVM5515_I2CGPIO_writeLine(  0, 0 );  // AIC_RST = 0
#endif

    // Configure AIC3204
    AIC3204_rset(  0, 0x00 );      // Select page 0
    AIC3204_rset(  1, 0x01 );      // Reset codec
    AIC3204_rset(  0, 0x01 );      // Point to page 1
    AIC3204_rset(  1, 0x08 );      // Disable crude AVDD generation from DVDD
    AIC3204_rset(  2, 0x00 );      // Enable Analog Blocks
    //  PLL and Clocks config and Power Up
    AIC3204_rset(  0, 0x00 );      // Select page 0
    AIC3204_rset( 27, 0x00 );      // BCLK and WCLK is set as i/p to AIC3204(Slave)
    AIC3204_rset(  4, 0x07 );      // PLL setting: PLLCLK <- BCLK and CODEC_CLKIN <-PLL CLK
    AIC3204_rset(  6, 0x20 );      // PLL setting: J=32
    AIC3204_rset(  7, 0 );         // PLL setting: HI_BYTE(D = 0)
    AIC3204_rset(  8, 0 );         // PLL setting: LO_BYTE(D) = 0
    // For 48 KHz sampling
    AIC3204_rset(  5, 0x92 );      // PLL setting: Power up PLL, P=1 and R=2
    AIC3204_rset( 13, 0x00 );      // Hi_Byte(DOSR) for DOSR = 128 decimal or 0x0080 DAC oversamppling
    AIC3204_rset( 14, 0x80 );      // Lo_Byte(DOSR) for DOSR = 128 decimal or 0x0080
    AIC3204_rset( 20, 0x80 );      // AOSR for AOSR = 128 decimal or 0x0080 for decimation filters 1 to 6
    AIC3204_rset( 11, 0x88 );      // Power up NDAC and set NDAC value to 8
    AIC3204_rset( 12, 0x82 );      // Power up MDAC and set MDAC value to 2
    AIC3204_rset( 18, 0x88 );      // Power up NADC and set NADC value to 8
    AIC3204_rset( 19, 0x82 );      // Power up MADC and set MADC value to 2
    // DAC ROUTING and Power Up
    AIC3204_rset(  0, 0x01 );      // Select page 1
    AIC3204_rset( 12, 0x08 );      // LDAC AFIR routed to HPL
    AIC3204_rset( 13, 0x08 );      // RDAC AFIR routed to HPR
    AIC3204_rset(  0, 0x00 );      // Select page 0
    AIC3204_rset( 64, 0x02 );      // Left vol=right vol
    AIC3204_rset( 65, 0x00 );      // Left DAC gain to 0dB VOL; Right tracks Left
    AIC3204_rset( 63, 0xd4 );      // Power up left,right data paths and set channel
    AIC3204_rset(  0, 0x01 );      // Select page 1
    AIC3204_rset( 16, 0x00);      // Unmute HPL , 6dB gain
    AIC3204_rset( 17, 0x00);      // Unmute HPR , 6dB gain
    AIC3204_rset(  9, 0x30 );      // Power up HPL,HPR
    AIC3204_rset(  0, 0x00 );      // Select page 0
    EVM5515_wait( 500 );           // Wait
    // ADC ROUTING and Power Up
    AIC3204_rset(  0, 0x01 );      // Select page 1
    AIC3204_rset( 51, 0x40 );      // SetMICBIAS
    AIC3204_rset( 52, 0xc0 );      // STEREO 1 Jack
                                   // IN2_L to LADC_P through 40 kohm
    AIC3204_rset( 55, 0xc0 );      // IN2_R to RADC_P through 40 kohmm
    AIC3204_rset( 54, 0x03 );      // CM_1 (common mode) to LADC_M through 40 kohm
    AIC3204_rset( 57, 0xc0 );      // CM_1 (common mode) to RADC_M through 40 kohm
    AIC3204_rset( 59, 0x00);       // MIC_PGA_L unmute 5f
    AIC3204_rset( 60, 0x5f);      // MIC_PGA_R unmute 5f
    AIC3204_rset(  0, 0x5f );      // Select page 0
    AIC3204_rset( 81, 0xc0 );      // Powerup Left and Right ADC
    AIC3204_rset( 82, 0x00 );      // Unmute Left and Right ADC

    AIC3204_rset( 0,  0x00 );
    EVM5515_wait( 200 );           // Wait

// I2S settings
//    I2S0_SRGR = 0x0015;
//    I2S0_ICMR = 0x0028;    // Enable interrupts
//    I2S0_CR   = 0x8012;    // 16-bit word, Master, enable I2S
//
    I2S2_SRGR = 0x0015;
//    I2S2_ICMR = 0x0028;    // Enable interrupts
    I2S2_CR   = 0x8012;    // 16-bit word, Master, enable I2S
    return 0;
}

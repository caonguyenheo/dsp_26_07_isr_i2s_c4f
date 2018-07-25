################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Add inputs and outputs from these tool invocations to the build variables 
ASM_SRCS += \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_irqplug.asm \
D:/dsp_filter/project_example_sine_750hz_1khz/src/vectors.asm 

C_SRCS += \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_audioClass.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_cdc.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_dat.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_dma.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_emif.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_gpio.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_gpt.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_hid.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_i2c.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_i2s.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_intc.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_lcdc.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_mcbsp.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_mcspi.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_mem.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_mmcsd.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_mmcsd_ataIf.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_msc.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_pll.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_rtc.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_sar.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_sdio.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_spi.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_sysctrl.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_uart.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_uhpi.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_usb.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_wdt.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/evm5515.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/evm5515_gpio.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/evm5515_i2c.c \
D:/dsp_filter/project_example_sine_750hz_1khz/src/evm5517_i2cgpio.c 

C_DEPS += \
./csl_audioClass.d \
./csl_cdc.d \
./csl_dat.d \
./csl_dma.d \
./csl_emif.d \
./csl_gpio.d \
./csl_gpt.d \
./csl_hid.d \
./csl_i2c.d \
./csl_i2s.d \
./csl_intc.d \
./csl_lcdc.d \
./csl_mcbsp.d \
./csl_mcspi.d \
./csl_mem.d \
./csl_mmcsd.d \
./csl_mmcsd_ataIf.d \
./csl_msc.d \
./csl_pll.d \
./csl_rtc.d \
./csl_sar.d \
./csl_sdio.d \
./csl_spi.d \
./csl_sysctrl.d \
./csl_uart.d \
./csl_uhpi.d \
./csl_usb.d \
./csl_wdt.d \
./evm5515.d \
./evm5515_gpio.d \
./evm5515_i2c.d \
./evm5517_i2cgpio.d 

OBJS += \
./csl_audioClass.obj \
./csl_cdc.obj \
./csl_dat.obj \
./csl_dma.obj \
./csl_emif.obj \
./csl_gpio.obj \
./csl_gpt.obj \
./csl_hid.obj \
./csl_i2c.obj \
./csl_i2s.obj \
./csl_intc.obj \
./csl_irqplug.obj \
./csl_lcdc.obj \
./csl_mcbsp.obj \
./csl_mcspi.obj \
./csl_mem.obj \
./csl_mmcsd.obj \
./csl_mmcsd_ataIf.obj \
./csl_msc.obj \
./csl_pll.obj \
./csl_rtc.obj \
./csl_sar.obj \
./csl_sdio.obj \
./csl_spi.obj \
./csl_sysctrl.obj \
./csl_uart.obj \
./csl_uhpi.obj \
./csl_usb.obj \
./csl_wdt.obj \
./evm5515.obj \
./evm5515_gpio.obj \
./evm5515_i2c.obj \
./evm5517_i2cgpio.obj \
./vectors.obj 

ASM_DEPS += \
./csl_irqplug.d \
./vectors.d 

OBJS__QUOTED += \
"csl_audioClass.obj" \
"csl_cdc.obj" \
"csl_dat.obj" \
"csl_dma.obj" \
"csl_emif.obj" \
"csl_gpio.obj" \
"csl_gpt.obj" \
"csl_hid.obj" \
"csl_i2c.obj" \
"csl_i2s.obj" \
"csl_intc.obj" \
"csl_irqplug.obj" \
"csl_lcdc.obj" \
"csl_mcbsp.obj" \
"csl_mcspi.obj" \
"csl_mem.obj" \
"csl_mmcsd.obj" \
"csl_mmcsd_ataIf.obj" \
"csl_msc.obj" \
"csl_pll.obj" \
"csl_rtc.obj" \
"csl_sar.obj" \
"csl_sdio.obj" \
"csl_spi.obj" \
"csl_sysctrl.obj" \
"csl_uart.obj" \
"csl_uhpi.obj" \
"csl_usb.obj" \
"csl_wdt.obj" \
"evm5515.obj" \
"evm5515_gpio.obj" \
"evm5515_i2c.obj" \
"evm5517_i2cgpio.obj" \
"vectors.obj" 

C_DEPS__QUOTED += \
"csl_audioClass.d" \
"csl_cdc.d" \
"csl_dat.d" \
"csl_dma.d" \
"csl_emif.d" \
"csl_gpio.d" \
"csl_gpt.d" \
"csl_hid.d" \
"csl_i2c.d" \
"csl_i2s.d" \
"csl_intc.d" \
"csl_lcdc.d" \
"csl_mcbsp.d" \
"csl_mcspi.d" \
"csl_mem.d" \
"csl_mmcsd.d" \
"csl_mmcsd_ataIf.d" \
"csl_msc.d" \
"csl_pll.d" \
"csl_rtc.d" \
"csl_sar.d" \
"csl_sdio.d" \
"csl_spi.d" \
"csl_sysctrl.d" \
"csl_uart.d" \
"csl_uhpi.d" \
"csl_usb.d" \
"csl_wdt.d" \
"evm5515.d" \
"evm5515_gpio.d" \
"evm5515_i2c.d" \
"evm5517_i2cgpio.d" 

ASM_DEPS__QUOTED += \
"csl_irqplug.d" \
"vectors.d" 

C_SRCS__QUOTED += \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_audioClass.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_cdc.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_dat.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_dma.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_emif.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_gpio.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_gpt.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_hid.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_i2c.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_i2s.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_intc.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_lcdc.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_mcbsp.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_mcspi.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_mem.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_mmcsd.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_mmcsd_ataIf.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_msc.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_pll.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_rtc.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_sar.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_sdio.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_spi.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_sysctrl.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_uart.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_uhpi.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_usb.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_wdt.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/evm5515.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/evm5515_gpio.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/evm5515_i2c.c" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/evm5517_i2cgpio.c" 

ASM_SRCS__QUOTED += \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/csl_irqplug.asm" \
"D:/dsp_filter/project_example_sine_750hz_1khz/src/vectors.asm" 



################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccsv8/tools/compiler/c5500_4.4.1

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./aic3204_config.obj" \
"./i2s_Intr.obj" \
"./main.obj" \
"./modulation_4fsk.obj" \
"../VC5505_UART.cmd" \
$(GEN_CMDS__FLAG) \
-l"Debug/C55XXCSL_LP.lib" \
-l"Debug/dsp.lib" \
-lrts55x.lib \
-llibc.a \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
DSP.out \

EXE_OUTPUTS__QUOTED += \
"DSP.out" \

BIN_OUTPUTS += \
DSP.hex \

BIN_OUTPUTS__QUOTED += \
"DSP.hex" \


# All Target
all: DSP.out

dependents:
	-cd D:/dsp_filter/project_example_sine_750hz_1khz/ccs_v6.x_examples/C55XXCSL_LP/Debug && $(MAKE) clean all
	-cd D:/dsp_filter/project_example_sine_750hz_1khz/ccs_v6.x_examples/LIB_DSP/Debug && $(MAKE) clean all

# Tool invocations
DSP.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS) D:/dsp_filter/project_example_sine_750hz_1khz/ccs_v6.x_examples/C55XXCSL_LP/Debug/C55XXCSL_LP.lib D:/dsp_filter/project_example_sine_750hz_1khz/ccs_v6.x_examples/LIB_DSP/Debug/dsp.lib
	@echo 'Building target: "$@"'
	@echo 'Invoking: C5500 Linker'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=large -g --define="_DEBUG" --define=c5505 --diag_warning=225 --ptrdiff_size=16 --algebraic --asm_source=algebraic -z -m"DSP.map" --stack_size=0x200 --heap_size=0x400 -i"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/lib" -i"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" -i"C:/ti/bios_5_42_02_10/packages/ti/rtdx/lib/c5500" -i"C:/ti/bios_5_42_02_10/packages/ti/bios/lib" -i"D:/dsp_filter/project_example_sine_750hz_1khz/ccs_v6.x_examples/C55XXCSL_LP" -i"D:/dsp_filter/project_example_sine_750hz_1khz/ccs_v6.x_examples/LIB_DSP" -i"D:/dsp_filter/project_example_sine_750hz_1khz/ccs_v6.x_examples/uart/CSL_UART_pollExample" --reread_libs --warn_sections --xml_link_info="CSL_UART_pollExample_linkInfo.xml" --rom_model --sys_stacksize=0x200 -o "DSP.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

DSP.hex: $(EXE_OUTPUTS)
	@echo 'Building files: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo 'Invoking: C5500 Hex Utility'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/hex55"  -o "DSP.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $(strip $(EXE_OUTPUTS__QUOTED))'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(GEN_CMDS__QUOTED)$(GEN_MISC_FILES__QUOTED)$(BIN_OUTPUTS__QUOTED)$(GEN_FILES__QUOTED)$(EXE_OUTPUTS__QUOTED)$(GEN_HDRS__QUOTED)
	-$(RM) "aic3204_config.obj" "i2s_Intr.obj" "main.obj" "modulation_4fsk.obj" 
	-$(RM) "aic3204_config.d" "i2s_Intr.d" "main.d" "modulation_4fsk.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
D:/dsp_filter/project_example_sine_750hz_1khz/ccs_v6.x_examples/C55XXCSL_LP/Debug/C55XXCSL_LP.lib:
D:/dsp_filter/project_example_sine_750hz_1khz/ccs_v6.x_examples/LIB_DSP/Debug/dsp.lib:

-include ../makefile.targets


################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
aic3204_config.obj: ../aic3204_config.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=large -g --include_path="D:/dsp_filter/project_example_sine_750hz_1khz/55x_inc" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --include_path="D:/dsp_filter/project_example_sine_750hz_1khz/inc" --include_path="D:/dsp_filter/project_example_sine_750hz_1khz/ccs_v6.x_examples/uart/CSL_UART_pollExample/Debug" --define="_DEBUG" --define=c5505 --diag_warning=225 --ptrdiff_size=16 --algebraic --asm_source=algebraic --preproc_with_compile --preproc_dependency="aic3204_config.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

i2s_Intr.obj: ../i2s_Intr.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=large -g --include_path="D:/dsp_filter/project_example_sine_750hz_1khz/55x_inc" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --include_path="D:/dsp_filter/project_example_sine_750hz_1khz/inc" --include_path="D:/dsp_filter/project_example_sine_750hz_1khz/ccs_v6.x_examples/uart/CSL_UART_pollExample/Debug" --define="_DEBUG" --define=c5505 --diag_warning=225 --ptrdiff_size=16 --algebraic --asm_source=algebraic --preproc_with_compile --preproc_dependency="i2s_Intr.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

main.obj: ../main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=large -g --include_path="D:/dsp_filter/project_example_sine_750hz_1khz/55x_inc" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --include_path="D:/dsp_filter/project_example_sine_750hz_1khz/inc" --include_path="D:/dsp_filter/project_example_sine_750hz_1khz/ccs_v6.x_examples/uart/CSL_UART_pollExample/Debug" --define="_DEBUG" --define=c5505 --diag_warning=225 --ptrdiff_size=16 --algebraic --asm_source=algebraic --preproc_with_compile --preproc_dependency="main.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

modulation_4fsk.obj: ../modulation_4fsk.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C5500 Compiler'
	"C:/ti/ccsv8/tools/compiler/c5500_4.4.1/bin/cl55" -v5505 --memory_model=large -g --include_path="D:/dsp_filter/project_example_sine_750hz_1khz/55x_inc" --include_path="C:/ti/ccsv8/tools/compiler/c5500_4.4.1/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/bios/include" --include_path="C:/ti/bios_5_42_02_10/packages/ti/rtdx/include/c5500" --include_path="D:/dsp_filter/project_example_sine_750hz_1khz/inc" --include_path="D:/dsp_filter/project_example_sine_750hz_1khz/ccs_v6.x_examples/uart/CSL_UART_pollExample/Debug" --define="_DEBUG" --define=c5505 --diag_warning=225 --ptrdiff_size=16 --algebraic --asm_source=algebraic --preproc_with_compile --preproc_dependency="modulation_4fsk.d_raw" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '



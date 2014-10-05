################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
driver\ development/eeprom.obj: ../driver\ development/eeprom.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"c:/ti/ccsv6/tools/compiler/msp430_4.3.3/bin/cl430" -vmspx --abi=eabi --data_model=restricted --preinclude="C:/ti/ccsv6/ccs_base/msp430/include/msp430f5xx_6xxgeneric.h" --include_path="c:/ti/ccsv6/ccs_base/msp430/include" --include_path="D:/work projects/Seebright/Firmware and Tools/Demo_KEY_LED_BLE/Common" --include_path="D:/work projects/Seebright/Firmware and Tools/Demo_KEY_LED_BLE/SYS/MSP430Ware" --include_path="c:/ti/ccsv6/tools/compiler/msp430_4.3.3/include" --advice:power=all -g --relaxed_ansi --define=__MSP430F5328__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="driver development/eeprom.pp" --obj_directory="driver development" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '



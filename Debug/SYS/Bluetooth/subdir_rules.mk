################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
SYS/Bluetooth/le_gatt_command.obj: ../SYS/Bluetooth/le_gatt_command.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/ti/ccsv5/tools/compiler/msp430_4.2.1/bin/cl430" -vmspx --abi=eabi --include_path="C:/ti/ccsv5/ccs_base/msp430/include" --include_path="C:/Users/Taylor/Documents/Remote Firmware/Demo_KEY_LED_BLE/Common" --include_path="C:/ti/ccsv5/tools/compiler/msp430_4.2.1/include" --advice:power=all -g --relaxed_ansi --define=__MSP430F5328__ --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU23 --silicon_errata=CPU40 --printf_support=minimal --preproc_with_compile --preproc_dependency="SYS/Bluetooth/le_gatt_command.pp" --obj_directory="SYS/Bluetooth" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '



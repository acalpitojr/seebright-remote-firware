/*
@************************ CYC_SYS_TargetConfig.h ******************************************

$MODULE IDENT		:  	SYS	$
$DESCRIPTION		: 	This file contains the port definitions pertaining to the particular target

<BEGIN REVISION>

    $Copyright: CRATUS TECHNOLOGY INC, 2013-14 $
    $Project: CYCLOPS Remote $
    $Revision: 0.1 $
    $Author: Sudhi $
    $Log:  $
    
	Revision 0.1  2014/3/6 
    Creation of the template
    
@**********************************************************************************
*/

 /*
NOTES:

*/



/* INCLUDE FILES: */
#include "MSP430Ware\gpio.h"


#define	TARGET_CYCLOPS_GAME
//#define	TARGET_MSP430F5438A_EXPERIMENTER_BOARD

/* EXPORTED CONSTANT DEFINITIONS            *ccccccccc*/

/* EXPORTED MACRO DEFINITIONS               *mmmmmmmmm*/
#ifdef	TARGET_CYCLOPS_GAME

//	PORT and PIN definitions for XT1 PORT
#define	XT1_PORT						GPIO_PORT_P5
#define	XT1_IN_PIN						GPIO_PIN4
#define	XT1_OUT_PIN						GPIO_PIN5

//	PORT and PIN definitions for User Buttons
#define	USER_BUTTONS_PORT				GPIO_PORT_P2
#define	USER_BUTTON_1_PIN				GPIO_PIN3
#define	USER_BUTTON_2_PIN				GPIO_PIN4
#define	USER_BUTTON_3_PIN				GPIO_PIN6

// PORT and PIN definitions for NAV button
#define NAV_BUTTON_PORT					GPIO_PORT_P2
#define NAV_BUTTON_PIN					GPIO_PIN5

//	PORT and PIN definitions for Trigger Button
#define	TRIGGER_BUTTON_PORT				GPIO_PORT_P2
#define	TRIGGER_BUTTON_PIN				GPIO_PIN2

//	PORT and PIN definitions for RGB LEDs
//	RED LED
#define	RGB_RED_LED_PORT				GPIO_PORT_P1
#define	RGB_RED_LED_PIN					GPIO_PIN2
//	GREEN LED
#define	RGB_GREEN_LED_PORT				GPIO_PORT_P1
#define	RGB_GREEN_LED_PIN				GPIO_PIN3
//	BLUE LED
#define	RGB_BLUE_LED_PORT				GPIO_PORT_P1
#define	RGB_BLUE_LED_PIN				GPIO_PIN4

// PORT and PIN definintions for Haptic Motors
//Haptic motor 1
#define HAPTIC_MOTOR_1_PORT				GPIO_PORT_P2
#define HAPTIC_MOTOR_1_PIN				GPIO_PIN0

//Haptic motor 2
#define HAPTIC_MOTOR_2_PORT				GPIO_PORT_P2
#define HAPTIC_MOTOR_2_PIN				GPIO_PIN1

//	PORT and PIN definitions for Battery Monitoring signals
#define	BATTERY_LOW_SIGNAL_PORT			GPIO_PORT_P1		//	BATTERY LOW SIGNAL
#define	BATTERY_LOW_SIGNAL_PIN			GPIO_PIN6

#define	BATTERY_MONITOR_SIGNAL_PORT		GPIO_PORT_P6		//	BATTERY MONITOR SIGNAL
#define	BATTERY_MONITOR_SIGNAL_PIN		GPIO_PIN0

//	PORT and PIN definitions for PAN MODULE RESET SIGNAL
#define	PAN_MODULE_RESET_SIGNAL_PORT	GPIO_PORT_P1
#define	PAN_MODULE_RESET_SIGNAL_PIN		GPIO_PIN5

//	The I2C Port used for I2C communication
#define	I2C_B0

//	PORT and PIN definitions for Interrupt from MPU 9250
#define	MPU_9250_INT_PORT				GPIO_PORT_P1
#define	MPU_9250_INT_PIN				GPIO_PIN7

//	PORT and PIN definitions for ACLK and SMCLK
#define	ACLK_OUT_PORT					GPIO_PORT_P1
#define	ACLK_OUT_PIN					GPIO_PIN0

#define	SMCLK_OUT_PORT					GPIO_PORT_P2
#define	SMCLK_OUT_PIN					GPIO_PIN2

//	PORT and PIN definitions for Joystick
#define	JOYSTICK_PORT					GPIO_PORT_P6
#define	VERT_AXIS_PIN					GPIO_PIN1
#define	HORIZ_AXIS_PIN					GPIO_PIN2

#define USB_PWR_DETECT_PORT 			GPIO_PORT_P6
#define USB_PWR_DETECT_PIN 				GPIO_PIN6

#define BAT_PWR_DETECT_PORT				GPIO_PORT_P6
#define BAT_PWR_DETECT_PIN				GPIO_PIN7

#define BT_PWR_DETECT_PORT				GPIO_PORT_P6
#define BT_PWR_DETECT_PIN				GPIO_PIN4

//PIN and PORT Defintions for UART0 PORT, used for communication with BLE Module
#define	UART_PORT_0_
#endif


#ifdef	TARGET_MSP430F5438A_EXPERIMENTER_BOARD
//	PORT and PIN definitions for XT1 PORT
#define	XT1_PORT						GPIO_PORT_P7
#define	XT1_IN_PIN						GPIO_PIN0
#define	XT1_OUT_PIN						GPIO_PIN1



//	PORT and PIN definitions for Trigger Button
#define	TRIGGER_BUTTON_PORT				GPIO_PORT_P2
#define	TRIGGER_BUTTON_PIN				GPIO_PIN0

//	PORT and PIN definitions for UP and DOWN Button
#define	UP_DOWN_BUTTON_PORT				GPIO_PORT_P2
#define	UP_BUTTON_PIN					GPIO_PIN4
#define	DOWN_BUTTON_PIN					GPIO_PIN5

//	PORT and PIN definitions for DOCKING STATUS Signal
#define	DOCKING_STATUS_SIGNAL_PORT		GPIO_PORT_P2
#define	DOCKING_STATUS_SIGNAL_PIN		GPIO_PIN6

//	PORT and PIN definitions for RGB LEDs
//	RED LED
#define	RGB_RED_LED_PORT				GPIO_PORT_P1
#define	RGB_RED_LED_PIN					GPIO_PIN0
//	GREEN LED
#define	RGB_GREEN_LED_PORT				GPIO_PORT_P1
#define	RGB_GREEN_LED_PIN					GPIO_PIN1
//	BLUE LED
#define	RGB_BLUE_LED_PORT				GPIO_PORT_P1
#define	RGB_BLUE_LED_PIN				GPIO_PIN2

//	PORT and PIN definitions for Battery Monitoring signals
#define	BATTERY_LOW_SIGNAL_PORT			GPIO_PORT_P1		//	BATTERY LOW SIGNAL
#define	BATTERY_LOW_SIGNAL_PIN			GPIO_PIN6

#define	BATTERY_MONITOR_SIGNAL_PORT		GPIO_PORT_P6		//	BATTERY MONITOR SIGNAL
#define	BATTERY_MONITOR_SIGNAL_PIN		GPIO_PIN0

//	PORT and PIN definitions for PAN MODULE RESET SIGNAL
#define	PAN_MODULE_RESET_SIGNAL_PORT	GPIO_PORT_P1
#define	PAN_MODULE_RESET_SIGNAL_PIN		GPIO_PIN7

//	The I2C Port used for I2C communication
#define	I2C_B1

//	PORT and PIN definitions for Interrupt from MPU 9250
#define	MPU_9250_INT_PORT				GPIO_PORT_P2
#define	MPU_9250_INT_PIN				GPIO_PIN7

//	PORT and PIN definitions for ACLK and SMCLK
#define	ACLK_OUT_PORT					GPIO_PORT_P1
#define	ACLK_OUT_PIN					GPIO_PIN0

#define	SMCLK_OUT_PORT					GPIO_PORT_P1
#define	SMCLK_OUT_PIN					GPIO_PIN6

//PIN and PORT Defintions for UART0 PORT, used for communication with BLE Module
#define	UART_PORT_0_

#endif

#ifdef	REMOTE_V1_2


#endif

/* EXPORTED TYPE DEFINITIONS                *ttttttttt*/

/* EXPORTED FUNCTIONS                       *ggggggggg*/


/* EXPORTED DATA DEFINITIONS/DECLARATIONS   ddddddd*/

/*-----------------------------EOF-------------------------------------------*/

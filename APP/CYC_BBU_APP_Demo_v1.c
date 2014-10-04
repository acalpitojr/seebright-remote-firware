/*
@************************ CYC_BBU_APP_Demo.c ******************************************

$MODULE IDENT		:  	APP	$
$DESCRIPTION		:  	This file contains the functionality to demonstrate:
						1. Periodic update of the User 1, 2 and 3 buttons



<BEGIN REVISION>

    $Copyright: CRATUS TECHNOLOGY INC, 2013-14 $
    $Project: CYCLOPS Remote $
    $Revision: 0.1 $
    $Author: Sudhi $
    $Log:  $
    
	Revision 0.1  2014/3/6 
    Creation of the template
    
@*******************************************************************************
*/

 /*
NOTES:

*/

/* INCLUDE FILES */
#include "CYC_Config.h"
#include "..\SYS\CYC_SYS_Common.h"
#include "..\SYS\CYC_SYS_Init.h"
#include "..\IO\CYC_IO_KEYS.h"
#include "..\IO\CYC_IO_LEDS.h"
#include "..\IO\CYC_IO_JSTK.h"
#include "..\IO\CYC_IO_MOTS.h"
#include "..\SYS\CYC_SYS_UART.h"
#include "..\SYS\CYC_SYS_Timer.h"
#include "..\SYS\CYC_SYS_ADC.h"
#include "..\SYS\CYC_SYS_PWM.h"

/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/



/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/
#define			MAX_AXIS_VALUE				4095

#define			SCAN_INTERVAL				10				//	IN MilliSeconds
#define			INPUT_REPORT_SIZE			20

//	Define the offset positions in input report
/*
Byte 0	JoyStick - X- Axis-LSB
Byte 1	JoyStick - X- Axis-MSB
Byte 2	JoyStick - Y- Axis-LSB
Byte 3	JoyStick - Y- Axis-MSB
Byte 4	Quaternion - X-LSB
Byte 5	Quaternion - X-MSB
Byte 6	Quaternion - Y-LSB
Byte 7	Quaternion - Y-MSB
Byte 8	Quaternion - Z-LSB
Byte 9	Quaternion - Z-MSB
Byte 10	Quaternion - W-LSB
Byte 11	Quaternion - W-MSB
Byte 12	Select Button		1-Pressed 0-Released
Byte 13	Back Button			1-Pressed 0-Released
Byte 14	Option Button		1-Pressed 0-Released
Byte 15	UP Button			1-Pressed 0-Released
Byte 16	DOWN Button			1-Pressed 0-Released
Byte 17	TRIGGER Button		1-Pressed 0-Released
Byte 18	NAVIGATOR Button	1-Pressed 0-Released
Byte 19	UNUSED
*/
#define			JOYSTICK_X_AXIS_INDEX		1
#define			JOYSTICK_Y_AXIS_INDEX		3
#define			QUAT_X_AXIS_INDEX			5
#define			QUAT_Y_AXIS_INDEX			7
#define			QUAT_Z_AXIS_INDEX			9
#define			QUAT_W_AXIS_INDEX			11
#define			SELECT_BUTTON_INDEX			13
#define			BACK_BUTTON_INDEX			14
#define			OPTION_BUTTON_INDEX			15
#define			UP_BUTTON_INDEX				16
#define			DOWN_BUTTON_INDEX			17
#define			TRIGGER_BUTTON_INDEX		18
#define			NAVIGATOR_BUTTON_INDEX		19

/*
SW2 - OPTION BUTTON - USER 1
SW3 - SELECT BUTTON - USER 2
SW4 - BACK BUTTON	- UER 3

 */

/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/

/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/



__IO UINT8 gau8UserInputReport[INPUT_REPORT_SIZE+1]=
{
INPUT_REPORT_SIZE,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};



/*
@@********************* main ***************************************
 *  Function	     :main
 *  Description 	 :This is the entry point for the Firmware
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */

main()
{
	__IO UINT8 lu8UserButtonStatus = 0;
	__IO UINT8 lu8UpDownButtonStatus = 0;
	__IO UINT8 lu8TriggerButtonStatus=0;
	__IO UINT8 lu8DockingButtonStatus=0;
	__IO INT16 ls16XAxis,ls16YAxis=0;
	__IO UINT16 lu16SkipCount=0;
	__IO UINT16 lu16TestCount=0;
	__IO INT16	ls16XYAxisData[2];
	__IO UINT32 lu32QuatData[4];


	//	Initialize the target
	CYC_SYS_InitializeTarget();

	//	Turn on the LEDs to work with duty cycle
	CYC_SYS_PWM_SetDutyCycle(0);

	while(1)
	{
		//	Read the status of buttons every 10 ms
		CYC_SYS_TMR_DelayInMilliSeconds(SCAN_INTERVAL);
		//__bis_SR_register(LPM0_bits + GIE);

		//	Read the status of
		//		1. User button 1, 2, 3
		//		2. Trigger button
		//		3. Up and Down button
		CYC_IO_KEYS_ReadUserButtonsStatus((UINT8*)&lu8UserButtonStatus);

		//	Update the array to indicate the same
		/*
		SW2 - BACK BUTTON- USER 1
		SW3 - SELECT BUTTON - USER 2
		SW4 - OPTION BUTTON - USER 3
		 */
		gau8UserInputReport[BACK_BUTTON_INDEX] = !(lu8UserButtonStatus & 0x01);
		gau8UserInputReport[SELECT_BUTTON_INDEX] = !((lu8UserButtonStatus & 0x02)>>1);
		gau8UserInputReport[OPTION_BUTTON_INDEX] = !((lu8UserButtonStatus & 0x04)>>2);

		//	Read UP / DOWN button status
		CYC_IO_KEYS_ReadUpDownButtonsStatus((UINT8*)&lu8UpDownButtonStatus);
		gau8UserInputReport[DOWN_BUTTON_INDEX] = !(lu8UpDownButtonStatus & 0x01);
		gau8UserInputReport[UP_BUTTON_INDEX] = !((lu8UpDownButtonStatus & 0x02)>>1);

		//	Read Trigger button status
		CYC_IO_KEYS_ReadTriggerButtonStatus((UINT8*)&lu8TriggerButtonStatus);
		gau8UserInputReport[TRIGGER_BUTTON_INDEX] = !(lu8TriggerButtonStatus & 0x01);

		//	Docking button status
		CYC_IO_KEYS_ReadDockingButtonStatus((UINT8*)&lu8DockingButtonStatus);
		gau8UserInputReport[NAVIGATOR_BUTTON_INDEX] = (lu8DockingButtonStatus & 0x01);

		//	Read the Joystick values
		CYC_IO_JSTK_ReadJoystickData((INT16*)ls16XYAxisData);
		ls16XAxis = ls16XYAxisData[0];
		ls16YAxis = ls16XYAxisData[1];
		//	Copy values to the input report
		//	X-AXIS
		gau8UserInputReport[JOYSTICK_X_AXIS_INDEX] = (ls16XAxis & 0xFF);
		gau8UserInputReport[JOYSTICK_X_AXIS_INDEX+1] = (ls16XAxis >> 8)& 0xFF;
		//	Y-AXIS
		gau8UserInputReport[JOYSTICK_Y_AXIS_INDEX] = (ls16YAxis & 0xFF);
		gau8UserInputReport[JOYSTICK_Y_AXIS_INDEX+1] = (ls16YAxis >> 8) & 0xFF;


		//	Read QUAT data from MPU9250
		CYC_IO_MOTS_GetQuaternionData((UINT32*)lu32QuatData);
		//	X-AXIS
		gau8UserInputReport[QUAT_X_AXIS_INDEX+1] = ((lu32QuatData[0]>>16) & 0xFF);
		gau8UserInputReport[QUAT_X_AXIS_INDEX] = ((lu32QuatData[0]>>16) >> 8);
		//	Y-AXIS
		gau8UserInputReport[QUAT_Y_AXIS_INDEX+1] = ((lu32QuatData[1]>>16) & 0xFF);
		gau8UserInputReport[QUAT_Y_AXIS_INDEX] = ((lu32QuatData[1]>>16) >> 8);
		//	Z-AXIS
		gau8UserInputReport[QUAT_Z_AXIS_INDEX+1] = ((lu32QuatData[2]>>16) & 0xFF);
		gau8UserInputReport[QUAT_Z_AXIS_INDEX] = ((lu32QuatData[2]>>16) >> 8);
		//	W-AXIS
		gau8UserInputReport[QUAT_W_AXIS_INDEX+1] = ((lu32QuatData[3]>>16) & 0xFF);
		gau8UserInputReport[QUAT_W_AXIS_INDEX] = ((lu32QuatData[3]>>16) >> 8);

		//	Transmit the information over UART
		CYC_SYS_UART_TransmitData((UINT8 *)gau8UserInputReport,(INPUT_REPORT_SIZE+1));
	}

}


/* MODULE INTERNAL FUNCTIONS               *fffffff*/

/*-----------------------------EOF-------------------------------------------*/





    
    

/*
@************************ CYC_BBU_APP_Demo_v2.c ******************************************

$MODULE IDENT		:  	APP	$
$DESCRIPTION		:  	This file contains the functionality to demonstrate:
						1. Periodic update of the User 1, 2 and 3 buttons
						2. Trigger button, Up and Down Button
						3. Joystick information
						4. Quaternion data

					All of these packed into 20 byte structure


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
#include "stdio.h"

/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/
extern __IO UINT8 gu8PowerOffMode;


/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/
#define			MAX_AXIS_VALUE				4095

#define			SCAN_INTERVAL				1				//	IN MilliSeconds
#define			INPUT_REPORT_SIZE			20

#define 		CONDENSED_JOYSTICK
//	Define the offset positions in input report
/*
Byte 1	JoyStick - X- Axis-LSB
Byte 2	JoyStick - (4 MSB of X Axis << 4) | 4 MSB OF Y AXIS
Byte 3	JoyStick - Y- Axis-LSB
Byte 4	QUAT - X- Axis-Byte0 (LSB)
Byte 5	QUAT - X- Axis-Byte1
Byte 6	QUAT - X- Axis-Byte2
Byte 7	QUAT - X- Axis-Byte3 (MSB)
Byte 8	QUAT - Y- Axis-Byte0 (LSB)
Byte 9	QUAT - Y- Axis-Byte1
Byte 10	QUAT - Y- Axis-Byte2
Byte 11	QUAT - Y- Axis-Byte3 (MSB)
Byte 12	QUAT - Z- Axis-Byte0 (LSB)
Byte 13	QUAT - Z- Axis-Byte1
Byte 14	QUAT - Z- Axis-Byte2
Byte 15	QUAT - Z- Axis-Byte3 (MSB)
Byte 16	QUAT - W- Axis-Byte0 (LSB)
Byte 17	QUAT - W- Axis-Byte1
Byte 18	QUAT - W- Axis-Byte2
Byte 19	QUAT - W- Axis-Byte3 (MSB)
Byte 20 BUTTONS
				bit7	bit6	bit5	bit4	bit3	bit2	bit1	bit0
				UP	 	DOWN	NAV		TRIG	OPT		BACK	X		SELECT
							VALUE		= 0		->	Button is NOT pressed
										= 1		->  Button is PRESSED
*/
#define			JOYSTICK_DATA_INDEX			1
#define			BUTTON_STATUS_INDEX			3
#define			QUAT_X_AXIS_INDEX			4
#define			QUAT_Y_AXIS_INDEX			8
#define			QUAT_Z_AXIS_INDEX			12
#define			QUAT_W_AXIS_INDEX			16


/*
SW2 - OPTION BUTTON - USER 1
SW3 - SELECT BUTTON - USER 2
SW4 - BACK BUTTON	- UER 3

 */

/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/
STATUS CYC_APP_ParseReceivedCommand(UINT8 *rau8ReceivedCommand, UINT8 ru8ReceivedCommandLen);
STATUS CYC_APP_GenerateLEDCommand(UINT8* rpu8CommandBuffer, UINT8* rpu8CommandLen);

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
	__IO UINT8 ButtonStatus = 0;
	__IO UINT8 lu8UserButtonStatus = 0;
	__IO UINT8 lu8ConsolidatedButtonStatus = 0;
	__IO UINT8 lu8SelectButtonStatus = 0;
	__IO UINT8 lu8OptionButtonStatus = 0;
	__IO UINT8 lu8BackButtonStatus = 0;
	__IO UINT8 lu8TriggerButtonStatus=0;
	__IO UINT8 lu8NavButtonStatus=0;
	__IO UINT16 ls16XAxis, ls16YAxis = 0;
	__IO INT8 ls8XAxis,ls8YAxis=0;
	__IO INT8 lu8XAxisSign, lu8YAxisSign;
	__IO UINT16 lu16SkipCount=0;
	__IO UINT16 lu16TestCount=0;
	__IO INT16	ls16XYAxisData[2];
	__IO INT32 lu32QuatData[4];
	__IO float lfQuatData[4];
	__IO UINT8 lau8ReceivedCommand[5];
	__IO UINT8 lu8ReceivedCommandLen;
	__IO UINT16 lu16TempCount=0;
	__IO UINT8  lu8BlueLEDDutyCycle = 0;
	//double ldFactor = 0.000000000931322574615478515625;

	//	Initialize the target
	CYC_SYS_InitializeTarget();  /*clocks and timers should be init here.  Our debug port uart is init here as well.*/

	/*-------------------------------------DEBUG UART TESTING-------------------------------------------*/
//	while(1)
	//    {
	//      CYC_SYS_UART_TransmitData(SERIAL_UART_PORT, "Seebright\r\n", sizeof("Seebright\r\n"));
	//__delay_cycles(0xfffff);
	//    }


	/*------------------------------GPIO OUTPUT TEST------------------------------------*/
	//GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN2);
//	GPIO_setOutputLowOnPin(GPIO_PORT_P5,GPIO_PIN2 );
//	GPIO_setOutputHighOnPin(GPIO_PORT_P5,GPIO_PIN2 );
/*---------------------------------------------------------------------------------------------------*/


/*------------------------------MOTION SENSOR TEST------------------------------------*/
	//	CYC_IO_MOTS_Init();
    //mpu_test();
	 //mpu_data_STRUCT mpu;
//	while(1)
//	{
  //      mpu = get_mpu_data();
   //     __delay_cycles(0xfffff);
	//}
	/*---------------------------------------------------------------------------------------------------*/



	/*----------------------------------------------BLUETOOTH TESTING--------------------------------------------------------*/
	//init_bluetooth();
//	__delay_cycles(0xfffff);
////
	//app_BT_SPP_Acceptor_DEMO();
	//app_BT_SPP_Initiator_DEMO();

	//app_BT_BLE_peripherial_DEMO();
	my_profile_DEMO();

	/*-----------------------------------------------------------------------------------------------------------------------------------------*/



	/*------------------------------------------------------EEPROM TESTING-----------------------------------------------------------*/
	//eeprom_test();
	/*-------------------------------------------------------------------------------------------------------------------------------------------*/




	/*------------------------------------------------------FUEL GAUGE TESTING-----------------------------------------------------------*/
    //fuel_gauge_test();
	/*-------------------------------------------------------------------------------------------------------------------------------------------*/



	/*-----------------------------------------------------------ADC_TESTING--------------------------------------------------------------*/
	//CYC_SYS_ADC_Init();
    //volatile uint16_t adc_reading = 0x00;

	//while(1)
//	{
//	    adc_reading=Read_ADC_Voltage(1);
	//adc_reading=Read_ADC_Voltage(2);
	//adc_reading=Read_ADC_Voltage(6);
	//adc_reading=Read_ADC_Voltage(7);
//	}
	/*-------------------------------------------------------------------------------------------------------------------------------------------*/














   while(1);



    for(lu16TempCount=0;lu16TempCount<10;lu16TempCount++)
	{
		CYC_SYS_PWM_SetDutyCycle(RGB_GREEN_LED_CHANNEL, lu8BlueLEDDutyCycle);
		CYC_SYS_TMR_DelayInMilliSeconds(200);
		lu8BlueLEDDutyCycle += 10;
	}
	CYC_SYS_PWM_SetDutyCycle(RGB_GREEN_LED_CHANNEL, 0);
	CYC_SYS_PWM_SetDutyCycle(RGB_BLUE_LED_CHANNEL, 0);

#define BOARD_TEST
#ifdef BOARD_TEST

#define LED_PWM	50

	CYC_SYS_GPIO_SetAsOutputPin(GPIO_PORT_P5, GPIO_PIN5);
	CYC_SYS_GPIO_SetAsOutputPin(GPIO_PORT_P5, GPIO_PIN2);

	int i = 0, j = 0;

	while(1) {
		//Serial Test
		CYC_SYS_UART_TransmitData(SERIAL_UART_PORT, "Seebright\r\n", sizeof("Seebright\r\n"));

		//Debug LED Test
		if (i == 1) {
			CYC_SYS_GPIO_SetOutputPinToLow(GPIO_PORT_P5, GPIO_PIN3);
			CYC_SYS_GPIO_SetOutputPinToHigh(GPIO_PORT_P5, GPIO_PIN2);
		} else {
			CYC_SYS_GPIO_SetOutputPinToLow(GPIO_PORT_P5, GPIO_PIN2);
			CYC_SYS_GPIO_SetOutputPinToHigh(GPIO_PORT_P5, GPIO_PIN3);
		}
		i ^= 1;

		//Button Test
		CYC_IO_KEYS_ReadUserButtonsStatus((UINT8*)&lu8UserButtonStatus);
		lu8BackButtonStatus = !(lu8UserButtonStatus & 0x01);
		lu8SelectButtonStatus = !((lu8UserButtonStatus & 0x02)>>1);
		lu8OptionButtonStatus = !((lu8UserButtonStatus & 0x04)>>2);

		CYC_IO_KEYS_ReadTriggerButtonStatus((UINT8*)&lu8TriggerButtonStatus);
		lu8TriggerButtonStatus = (!(lu8TriggerButtonStatus & 0x01));

		CYC_IO_KEYS_ReadNavButtonStatus((UINT8*) &lu8NavButtonStatus);
		lu8NavButtonStatus = (!(lu8NavButtonStatus & 0x01));

		if (lu8BackButtonStatus == 1)
			CYC_SYS_UART_TransmitData(SERIAL_UART_PORT, "Back\r\n", sizeof("Back\r\n"));
		if(lu8SelectButtonStatus == 1)
			CYC_SYS_UART_TransmitData(SERIAL_UART_PORT, "Select\r\n", sizeof("Select\r\n"));
		if (lu8OptionButtonStatus == 1)
			CYC_SYS_UART_TransmitData(SERIAL_UART_PORT, "Option\r\n", sizeof("Option\r\n"));
		if (lu8TriggerButtonStatus == 1)
			CYC_SYS_UART_TransmitData(SERIAL_UART_PORT, "Trigger\r\n", sizeof("Trigger\r\n"));
		if (lu8NavButtonStatus == 1)
			CYC_SYS_UART_TransmitData(SERIAL_UART_PORT, "Nav\r\n", sizeof("Nav\r\n"));

		//RGB LED
		switch (j++) {
		case 0:
			//CYC_SYS_GPIO_SetOutputPinToHigh(RGB_RED_LED_PORT, RGB_RED_LED_PIN);
			CYC_SYS_PWM_SetDutyCycle(RGB_RED_LED_CHANNEL, LED_PWM);
			break;
		case 1:
			CYC_SYS_PWM_SetDutyCycle(RGB_GREEN_LED_CHANNEL, LED_PWM);
			break;
		case 2:
			CYC_SYS_PWM_SetDutyCycle(RGB_BLUE_LED_CHANNEL, LED_PWM);
			break;
		case 3:
			CYC_SYS_PWM_SetDutyCycle(RGB_RED_LED_CHANNEL, LED_PWM);
			CYC_SYS_PWM_SetDutyCycle(RGB_GREEN_LED_CHANNEL, LED_PWM);
			break;
		case 4:
			CYC_SYS_PWM_SetDutyCycle(RGB_GREEN_LED_CHANNEL, LED_PWM);
			CYC_SYS_PWM_SetDutyCycle(RGB_BLUE_LED_CHANNEL, LED_PWM);
			break;
		case 5:
			CYC_SYS_PWM_SetDutyCycle(RGB_RED_LED_CHANNEL, LED_PWM);
			CYC_SYS_PWM_SetDutyCycle(RGB_BLUE_LED_CHANNEL, LED_PWM);
			break;
		case 6:
			CYC_SYS_PWM_SetDutyCycle(RGB_RED_LED_CHANNEL, LED_PWM);
			CYC_SYS_PWM_SetDutyCycle(RGB_GREEN_LED_CHANNEL, LED_PWM);
			CYC_SYS_PWM_SetDutyCycle(RGB_BLUE_LED_CHANNEL, LED_PWM);
			break;
		case 7 :
			j = 0;
		}

		//Haptic Motor Test


		//Joystick Test
/*
 *
*/
		//MPU9250 Test
/*
		CYC_IO_MOTS_GetQuaternionData((INT32*)lu32QuatData);

		gau8UserInputReport[QUAT_X_AXIS_INDEX+0] = (UINT8)((lu32QuatData[0] & 0xFF));
		gau8UserInputReport[QUAT_X_AXIS_INDEX+1] = (UINT8)((lu32QuatData[0] >> 8 & 0xFF));
		gau8UserInputReport[QUAT_X_AXIS_INDEX+2] = (UINT8)((lu32QuatData[0] >> 16 & 0xFF));
		gau8UserInputReport[QUAT_X_AXIS_INDEX+3] = (UINT8)((lu32QuatData[0] >> 24 & 0xFF));

		CYC_SYS_UART_TransmitData(SERIAL_UART_PORT, (UINT8*)gau8UserInputReport[QUAT_X_AXIS_INDEX], sizeof(lu32QuatData[0]));
*/
		//Bluetooth Code
/*

*/


		CYC_SYS_TMR_DelayInMilliSeconds(1000);

		CYC_SYS_PWM_SetDutyCycle(RGB_RED_LED_CHANNEL, 0);
		CYC_SYS_PWM_SetDutyCycle(RGB_GREEN_LED_CHANNEL, 0);
		CYC_SYS_PWM_SetDutyCycle(RGB_BLUE_LED_CHANNEL, 0);
		CYC_SYS_PWM_SetDutyCycle(HAPTIC_MOTOR_1_CHANNEL, 0);
		CYC_SYS_PWM_SetDutyCycle(HAPTIC_MOTOR_2_CHANNEL, 0);

	}
#endif



	while(1)
	{
		//	Check if any command has been received from the host
		CYC_SYS_UART_ReadCommandData(BT_UART_PORT, (UINT8*)lau8ReceivedCommand, (UINT8*)&lu8ReceivedCommandLen);
		//CYC_APP_GenerateLEDCommand((UINT8*)lau8ReceivedCommand, (UINT8*)&lu8ReceivedCommandLen);
		if(lu8ReceivedCommandLen != 0)
		{
			//	Parse the received command and act on the command received
			CYC_APP_ParseReceivedCommand((UINT8*)lau8ReceivedCommand, (UINT8)lu8ReceivedCommandLen);
		}

		//	Read the status of buttons every 1 ms
		CYC_SYS_TMR_DelayInMilliSeconds(SCAN_INTERVAL);


		/*
			BUTTONS
						bit7	bit6	bit5	bit4	bit3	bit2	bit1	bit0
						0	 	0		NAV		TRIG	OPT		BACK	X		SELECT

						VALUE		= 0		->	Button is NOT pressed
									= 1		->  Button is PRESSED
		SW2 - BACK BUTTON- 	USER 1
		SW3 - SELECT BUTTON - USER 2
		SW4 - OPTION BUTTON - USER 3
		*/
		//	Read the status of Buttons
		CYC_IO_KEYS_ReadUserButtonsStatus((UINT8*)&lu8UserButtonStatus);
		lu8BackButtonStatus = !(lu8UserButtonStatus & 0x01);
		lu8SelectButtonStatus = !((lu8UserButtonStatus & 0x02)>>1);
		lu8OptionButtonStatus = !((lu8UserButtonStatus & 0x04)>>2);

		//	Read Trigger button status
		CYC_IO_KEYS_ReadTriggerButtonStatus((UINT8*)&lu8TriggerButtonStatus);
		lu8TriggerButtonStatus = (!(lu8TriggerButtonStatus & 0x01));


		/*---------------------TO SAVE POWER OFF THE DEVICE IF OPTION and SELECT buttons are pressed and held */
#if 1
		if((lu8BackButtonStatus == 1) && (lu8OptionButtonStatus == 1))
		{

			for(lu16TempCount=0;lu16TempCount<10;lu16TempCount++)
			{
				//	Flash the RED LED to signify a powerup
				CYC_IO_LEDS_TurnOnAnLED(RED_LED);
				CYC_SYS_TMR_DelayInMilliSeconds(100);
				CYC_IO_LEDS_TurnOffAnLED(RED_LED);
				CYC_SYS_TMR_DelayInMilliSeconds(100);
			}

			//	Power down MPU
			mpu_reset();

			CYC_SYS_TMR_DisableTimer1();

			//	Hold the BLUETOOTH module in RESET mode and go to sleep
			CYC_SYS_RST_HoldPAN1721InReset();

			//	Clear the interrupts and enter into sleep mode
			gu8PowerOffMode = TRUE;


			__bis_SR_register(LPM0_bits+GIE);
			__no_operation();

			while(1);
			//	Re-initialize the target board
			//CYC_SYS_InitializeTarget();
			//CYC_SYS_RST_DeAssertPAN1721ResetSignal();
			//	Set it for GREEN LED
			//CYC_SYS_PWM_SetDutyCycle(RGB_GREEN_LED_CHANNEL, 80);
		}
#endif
#ifdef CONDENSED_JOYSTICK
		//	Read the Joystick values
		CYC_IO_JSTK_ReadJoystickData((INT16*)ls16XYAxisData);
		lu8XAxisSign = ((ls16XYAxisData[0] & 0x0200) >> 9);
		lu8YAxisSign = ((ls16XYAxisData[1] & 0x0200) >> 9);

		ls8XAxis = ((ls16XYAxisData[0] >> 1) & 0xFF);
		ls8YAxis = ((ls16XYAxisData[1] >> 1) & 0xFF);


		//	X-AXIS
		gau8UserInputReport[JOYSTICK_DATA_INDEX] = ls8XAxis;
		//	Y-AXIS
		gau8UserInputReport[JOYSTICK_DATA_INDEX+1] = ls8YAxis;
		//Buttons and Joystick Sign
		lu8ConsolidatedButtonStatus = 	lu8SelectButtonStatus |
										(lu8BackButtonStatus<<2) |
										(lu8OptionButtonStatus<<3) |
										(lu8TriggerButtonStatus<<4) |
										(0<<5) |
										(lu8XAxisSign<<6) |
										(lu8YAxisSign<<7);
#endif
#ifndef CONDENSED_JOYSTICK
		//	Read the Joystick values
		CYC_IO_JSTK_ReadJoystickData((INT16*)ls16XYAxisData);

		ls16XAxis = ls16XYAXisData[0];
		ls16YAxis = ls16XYAXisData[1];
		//	X-AXIS LSB
		gau8UserInputReport[JOYSTICK_DATA_INDEX] = (ls16XAxis & 0xFF);
		//	MSB of X AXIS and MSB of Y AXIS
		gau8UserInputReport[JOYSTICK_DATA_INDEX+1] = ((ls16XAxis >> 4) & 0xF0) | ((ls16YAxis >> 8) & 0x0F);
		//	Y-AXIS LSB
		gau8UserInputReport[JOYSTICK_DATA_INDEX+2] = (ls16YAxis & 0xFF);
		//Buttons and Joystick Sign
		lu8ConsolidatedButtonStatus = 	lu8SelectButtonStatus |
										(lu8BackButtonStatus<<2) |
										(lu8OptionButtonStatus<<3) |
										(lu8TriggerButtonStatus<<4) |
										(lu8DockingButtonStatus<<5);
#endif

		//	Copy the consolidated button status into input report
		gau8UserInputReport[BUTTON_STATUS_INDEX] = lu8ConsolidatedButtonStatus;

		/*-----------------------------------FOR TESTING ONLY---------------------------------------- */
		{
			static UINT8 lu8Count;
			//gau8UserInputReport[JOYSTICK_DATA_INDEX] = lu8Count++;
		}
		/*------------------------------------------------------------------------------------------- */

		//	Read QUAT data from MPU9250
		CYC_IO_MOTS_GetQuaternionData((INT32*)lu32QuatData);

		//	To test floating point, override the values
#if 0
		*((float*)&lu32QuatData[0]) = (float)((double)lu32QuatData[0]* ldFactor);
		*((float*)&lu32QuatData[1]) = (float)((double)lu32QuatData[1]* ldFactor);
		*((float*)&lu32QuatData[2]) = (float)((double)lu32QuatData[2]* ldFactor);
		*((float*)&lu32QuatData[3]) = (float)((double)lu32QuatData[3]* ldFactor);
#endif

		//	X-AXIS
		gau8UserInputReport[QUAT_X_AXIS_INDEX+0] = (UINT8)((lu32QuatData[0] & 0xFF));
		gau8UserInputReport[QUAT_X_AXIS_INDEX+1] = (UINT8)((lu32QuatData[0] >> 8 & 0xFF));
		gau8UserInputReport[QUAT_X_AXIS_INDEX+2] = (UINT8)((lu32QuatData[0] >> 16 & 0xFF));
		gau8UserInputReport[QUAT_X_AXIS_INDEX+3] = (UINT8)((lu32QuatData[0] >> 24 & 0xFF));

		//	Y-AXIS
		gau8UserInputReport[QUAT_Y_AXIS_INDEX+0] = (UINT8)((lu32QuatData[1] & 0xFF));
		gau8UserInputReport[QUAT_Y_AXIS_INDEX+1] = (UINT8)((lu32QuatData[1] >> 8 & 0xFF));
		gau8UserInputReport[QUAT_Y_AXIS_INDEX+2] = (UINT8)((lu32QuatData[1] >> 16 & 0xFF));
		gau8UserInputReport[QUAT_Y_AXIS_INDEX+3] = (UINT8)((lu32QuatData[1] >> 24 & 0xFF));

		//	Z-AXIS
		gau8UserInputReport[QUAT_Z_AXIS_INDEX+0] = (UINT8)((lu32QuatData[2] & 0xFF));
		gau8UserInputReport[QUAT_Z_AXIS_INDEX+1] = (UINT8)((lu32QuatData[2] >> 8 & 0xFF));
		gau8UserInputReport[QUAT_Z_AXIS_INDEX+2] = (UINT8)((lu32QuatData[2] >> 16 & 0xFF));
		gau8UserInputReport[QUAT_Z_AXIS_INDEX+3] = (UINT8)((lu32QuatData[2] >> 24 & 0xFF));

		//	W-AXIS
		gau8UserInputReport[QUAT_W_AXIS_INDEX+0] = (UINT8)((lu32QuatData[3] & 0xFF));
		gau8UserInputReport[QUAT_W_AXIS_INDEX+1] = (UINT8)((lu32QuatData[3] >> 8 & 0xFF));
		gau8UserInputReport[QUAT_W_AXIS_INDEX+2] = (UINT8)((lu32QuatData[3] >> 16 & 0xFF));
		gau8UserInputReport[QUAT_W_AXIS_INDEX+3] = (UINT8)((lu32QuatData[3] >> 24 & 0xFF));

		//	Transmit the information over BT_UART
		CYC_SYS_UART_TransmitData(BT_UART_PORT, (UINT8 *)gau8UserInputReport,(INPUT_REPORT_SIZE+1));
		CYC_SYS_UART_TransmitData(SERIAL_UART_PORT, (UINT8 *)gau8UserInputReport,(INPUT_REPORT_SIZE+1));

	}

}


/* MODULE INTERNAL FUNCTIONS               *fffffff*/
STATUS CYC_APP_ParseReceivedCommand(UINT8 *rpu8ReceivedCommand, UINT8 ru8ReceivedCommandLen)
{
	__IO UINT8 lu8RedLEDDutyCycle = 0;
	__IO UINT8 lu8GreenLEDDutyCycle = 0;
	__IO UINT8 lu8BlueLEDDutyCycle = 0;

	//	Check if the first two bytes are AB and BA
	if	((rpu8ReceivedCommand[0] == 0xAB) &&
		(rpu8ReceivedCommand[1] == 0xAD)
		)
	{
		//	Command contains duty cycle for RED, GREEN and BLUE LEDs
		lu8RedLEDDutyCycle = rpu8ReceivedCommand[2];
		//	Set it for RED LED
		CYC_SYS_PWM_SetDutyCycle(RGB_RED_LED_CHANNEL, lu8RedLEDDutyCycle);

		lu8GreenLEDDutyCycle = rpu8ReceivedCommand[3];
		//	Set it for GREEN LED
		CYC_SYS_PWM_SetDutyCycle(RGB_GREEN_LED_CHANNEL, lu8GreenLEDDutyCycle);

		lu8BlueLEDDutyCycle = rpu8ReceivedCommand[4];
		//	Set it for BLUE LED
		CYC_SYS_PWM_SetDutyCycle(RGB_BLUE_LED_CHANNEL, lu8BlueLEDDutyCycle);

	}

	return SUCCESS;
}

static UINT8 su8RedLedDutyCycle=30;
static UINT8 su8BlueLedDutyCycle=20;
static UINT8 su8GreenLedDutyCycle=60;

STATUS CYC_APP_GenerateLEDCommand(UINT8* rpu8CommandBuffer, UINT8* rpu8CommandLen)
{

	//	This function fills the passed buffer with the simulated command
	su8RedLedDutyCycle++;
	if(su8RedLedDutyCycle>=100)
		su8RedLedDutyCycle = 0;

	su8BlueLedDutyCycle++;
	if(su8BlueLedDutyCycle>=100)
		su8BlueLedDutyCycle = 0;

	su8GreenLedDutyCycle++;
	if(su8GreenLedDutyCycle>=100)
		su8GreenLedDutyCycle = 0;

	rpu8CommandBuffer[0] = 0xAB;
	rpu8CommandBuffer[1] = 0xAD;

	//	RED LED Duty cycle
	rpu8CommandBuffer[2] = su8RedLedDutyCycle;
	//	GREEN LED Duty Cycle
	rpu8CommandBuffer[3] = su8GreenLedDutyCycle;
	//	BLUE LED Duty Cycle
	rpu8CommandBuffer[4] = su8BlueLedDutyCycle;

	*rpu8CommandLen = 5;

	return SUCCESS;
}


/*-----------------------------EOF-------------------------------------------*/





    
    

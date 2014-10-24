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
					 		NAV		TRIG	OPT		BACK	X		SELECT
							VALUE		= 0		->	Button is NOT pressed
										= 1		->  Button is PRESSED

SW2 - OPTION BUTTON - USER 1
SW3 - SELECT BUTTON - USER 2
SW4 - BACK BUTTON	- UER 3
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
#include "..\driver development\Event_Handler.h"
#include "stdio.h"

/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/

/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

typedef enum {
	INIT,
	SAMPLE,
	SEND,
} state_t;
static state_t FSM_State;

typedef enum {
	NO_ERROR,
	FSM_INIT_ERROR,
	FSM_SAMPLE_ERROR,
	FSM_SEND_ERROR,
	FSM_DEFAULT_ERROR,
	QUEUE_ERROR,
} error_t;
static error_t mainError;

static MainEvent_t mainEvent;

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/

/* PRIVATE FUNCTION PROTOTYPES*/
void InitSeebrightController(void);
error_t RunControllerFSM(MainEvent_t FSM_Event);
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
	InitSeebrightController();

	while(1) {
		//Main Loop
		while (mainError == NO_ERROR) {
			mainEvent = RunEventHandler();
			mainError = RunControllerFSM(mainEvent);
		}
		//Error Handler
		switch (mainError) {
		case FSM_INIT_ERROR:
			break;
		case FSM_SAMPLE_ERROR:
			break;
		case FSM_SEND_ERROR:
			break;
		case QUEUE_ERROR:
			break;
		}

	}
}

void InitSeebrightController(void)
{

	CYC_SYS_InitializeTarget();	//Initialize the target
	CYC_IO_MOTS_Init();			//Initialize MPU-9250

	InitEventHandler();

	FSM_State = INIT;
	mainError = NO_ERROR;
	mainEvent = NO_EVENT;

	RunControllerFSM(NO_EVENT);	//Run FSM with no event, runs through init state
}

error_t RunControllerFSM(MainEvent_t FSM_Event)
{
	error_t FSM_returnError = NO_ERROR;

	if (FSM_Event == QUEUE_FULL)
		return QUEUE_ERROR;

	switch (FSM_State) {
	case INIT:
		if (FSM_Event != NO_EVENT)
			FSM_returnError = FSM_INIT_ERROR;

		InitTimer(JOYSTICK_SAMPLE_TIMER, TIME_JOYSTICK_SAMPLE);
		InitTimer(SEND_BT_TIMER, TIME_BT_SEND);

		FSM_State = SAMPLE;
		break; //END INIT

	case SAMPLE:
		switch (FSM_Event) {
		case NO_EVENT:
			break; //END NO-EVENT
		case MPU_9250_DATA_READY:
			break; //END MPU_9250_DATA_READY
		case BUTTON_PRESSED:
			break; //END BUTTON_PRESSED
		case SAMPLE_TIMER:
			break; //END SAMPLE_TIMER
		case SEND_TIMER:
			//Get Final Data
			//Compile Send Report
			FSM_State = SEND;
			break; //END SEND_TIMER
		}
		break; //END SAMPLE

	case SEND:
		switch (FSM_Event) {
		case NO_EVENT:
			break; //END NO-EVENT
		case MPU_9250_DATA_READY:
			break; //END MPU_9250_DATA_READY
		case BUTTON_PRESSED:
			break; //END BUTTON_PRESSED
		case SAMPLE_TIMER:
			break; //END SAMPLE_TIMER
		case SEND_TIMER:
			break; //END SEND_TIMER
		}
		break; //END SEND


	default:
		FSM_returnError = FSM_DEFAULT_ERROR;
		break; //END DEFAULT

	}

	return FSM_returnError;
}
    

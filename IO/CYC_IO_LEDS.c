/*
@************************ CYC_IO_LEDS.c ******************************************

$MODULE IDENT		:  	LED	$
$DESCRIPTION		: 	This file contains the functions to test the LEDs

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
#include "CYC_IO_LEDS.h"
#include "..\SYS\CYC_SYS_GPIO.h"

/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/

/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/

/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/

/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/

/*
@@********************* CYC_IO_LEDS_IntializeLEDs ***************************************
 *  Function	     :	VOID CYC_IO_LEDS_IntializeLEDs()
 *
 *  Description 	 : 	This function initializes the pins connected to RGB LEDs as output pins
 *
 *  Input parameters :	none
 *
 *  Output parameters:	none
 *
 *  Return      	 :
 *
 *  Note         	 :  The LEDs are PWM controlled
 *
 ******************************************************************************
 */
VOID CYC_IO_LEDS_IntializeLEDs()
{
	//	Set the Pins connected to RGB LEDs to be Digital Output pins
	//	RED LED
	CYC_SYS_GPIO_SetPeripheralPinAsOutput(RGB_RED_LED_PORT, RGB_RED_LED_PIN);

	//	GREEN LED
	CYC_SYS_GPIO_SetPeripheralPinAsOutput(RGB_GREEN_LED_PORT, RGB_GREEN_LED_PIN);

	//	BLUE LED
	CYC_SYS_GPIO_SetPeripheralPinAsOutput(RGB_BLUE_LED_PORT, RGB_BLUE_LED_PIN);

}

/*
@@********************* CYC_IO_LEDS_TurnOnAnLED ***************************************
 *  Function	     :	VOID CYC_IO_LEDS_TurnOnAnLED(UINT8 ru8LEDToBeTurnedOn)
 *
 *  Description 	 : 	This function turns the needed LED ON
 *
 *  Input parameters :	none
 *
 *  Output parameters:	none
 *
 *  Return      	 :
 *
 *  Note         	 :  The LEDs are PWM controlled. During testing, they are kept to be simple GPIOs
 *
 ******************************************************************************
 */
VOID CYC_IO_LEDS_TurnOnAnLED(UINT8 ru8LEDToBeTurnedOn)
{

	UINT8 lu8LEDPort = 0;
	UINT16 lu16LEDPin = 0;

	//	Based on the LED to be operated on, get to know the LEDs PORT and PIN number
	switch(ru8LEDToBeTurnedOn)
	{
		case RED_LED:
		{
			lu8LEDPort = RGB_RED_LED_PORT;
			lu16LEDPin = RGB_RED_LED_PIN;
			break;
		}

		case GREEN_LED:
		{
			lu8LEDPort = RGB_GREEN_LED_PORT;
			lu16LEDPin = RGB_GREEN_LED_PIN;
			break;
		}

		case BLUE_LED:
		{
			lu8LEDPort = RGB_BLUE_LED_PORT;
			lu16LEDPin = RGB_BLUE_LED_PIN;
			break;
		}
	}//	end of switch(ru8LEDToBeTurnedOn)

	//	Assert a high on the port to drive the LED on
	CYC_SYS_GPIO_SetOutputPinToHigh(lu8LEDPort, lu16LEDPin);

}

/*
@@********************* CYC_IO_LEDS_TurnOffAnLED ***************************************
 *  Function	     :	VOID CYC_IO_LEDS_TurnOffAnLED(UINT8 ru8LEDToBeTurnedOff)
 *
 *  Description 	 : 	This function initializes the pins connected to RGB LEDs as output pins
 *
 *  Input parameters :	none
 *
 *  Output parameters:	none
 *
 *  Return      	 :
 *
 *  Note         	 :  The LEDs are PWM controlled. During testing, they are kept to be simple GPIOs
 *
 ******************************************************************************
 */
VOID CYC_IO_LEDS_TurnOffAnLED(UINT8 ru8LEDToBeTurnedOff)
{
	UINT8 lu8LEDPort = 0;
	UINT16 lu16LEDPin = 0;

	//	Based on the LED to be operated on, get to know the LEDs PORT and PIN number
	switch(ru8LEDToBeTurnedOff)
	{
		case RED_LED:
		{
			lu8LEDPort = RGB_RED_LED_PORT;
			lu16LEDPin = RGB_RED_LED_PIN;
			break;
		}

		case GREEN_LED:
		{
			lu8LEDPort = RGB_GREEN_LED_PORT;
			lu16LEDPin = RGB_GREEN_LED_PIN;
			break;
		}

		case BLUE_LED:
		{
			lu8LEDPort = RGB_BLUE_LED_PORT;
			lu16LEDPin = RGB_BLUE_LED_PIN;
			break;
		}
	}//	end of switch(ru8LEDToBeTurnedOff)

	//	Assert a LOW on the port to drive the LED off
	CYC_SYS_GPIO_SetOutputPinToLow(lu8LEDPort, lu16LEDPin);

}


VOID CYC_IO_LEDS_TurnOffAllLED(void)
{
	CYC_SYS_GPIO_SetOutputPinToLow(RGB_RED_LED_PORT, RGB_RED_LED_PIN);
	CYC_SYS_GPIO_SetOutputPinToLow(RGB_GREEN_LED_PORT, RGB_GREEN_LED_PIN);
	CYC_SYS_GPIO_SetOutputPinToLow(RGB_BLUE_LED_PORT, RGB_BLUE_LED_PIN);

}
/* MODULE INTERNAL FUNCTIONS               *fffffff*/


/*-----------------------------EOF-------------------------------------------*/





    
    

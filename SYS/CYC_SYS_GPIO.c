/*
@************************ CYC_SYS_GPIO.c ******************************************

$MODULE IDENT		:  	GPIO	$
$DESCRIPTION		: 	This file contains the functions which are needed for the GPIO

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
#include "CYC_SYS_Common.h"
#include "CYC_SYS_GPIO.h"
#include "MSP430Ware\gpio.h"


/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/

/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/

/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/

/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/

/*
@@********************* CYC_SYS_GPIO_SetAsInputPin ***************************************
 *  Function	     :	STATUS CYC_SYS_GPIO_SetAsInputPin (UINT8 ru8Port, UINT16 ru16Pin  )
 *  Description 	 :	This initialises the given pin in the given port as input pin signal
 *  Input parameters :	None
 *  Output parameters:	None
 *  Return      	 :	SUCCESS / ERROR
 *  Note         	 :
 *
 ******************************************************************************
 */
STATUS CYC_SYS_GPIO_SetAsInputPin (UINT8 ru8Port, UINT16 ru16Pin  )
{
	STATUS lu32StatusInfo = SUCCESS;

	//	Call the GPIO function in MSP430Ware to initialise the port and pins as input
	GPIO_setAsInputPin (ru8Port,ru16Pin);

	return lu32StatusInfo;
}

/*
@@********************* CYC_SYS_GPIO_GetInputPinStatus ***************************************
 *  Function	     :	STATUS CYC_SYS_GPIO_GetInputPinStatus (UINT8 ru8Port, UINT16 ru16Pin, UINT16* rpu16ReadValue)
 *
 *  Description 	 :	This reads the status of a pin in a given port
 *
 *  Input parameters :	ru8Port - The port to which the pin belongs
 *  					ru16Pin - Pin number in the port whose status is needed
 *
 *  Output parameters:	rpu16ReadValue - Read value is updated into the address pointed by this parameter
 *
 *  Return      	 :	SUCCESS / ERROR
 *
 *  Note         	 :
 *
 ******************************************************************************
 */
STATUS CYC_SYS_GPIO_GetInputPinStatus (UINT8 ru8Port, UINT16 ru16Pin, UINT8* rpu8ReadValue)
{
	STATUS lu32StatusInfo = SUCCESS;
	__IO UINT16	lu16ReadValue=0;

	//	Call the GPIO function in MSP430Ware to read the status of the given pin, in given port
	lu16ReadValue = GPIO_getInputPinValue (ru8Port,ru16Pin);

	//	Return the value read. If the input was high, it will be 1 else it will be 0
	*rpu8ReadValue = (UINT8)lu16ReadValue;

	return lu32StatusInfo;
}


/*
@@********************* CYC_SYS_GPIO_SetAsOutputPin ***************************************
 *  Function	     :	STATUS CYC_SYS_GPIO_SetAsOutputPin  (UINT8 ru8Port, UINT16 ru16Pin  )
 *  Description 	 :	This initialises the given pin in the given port as Digital Output signal
 *  Input parameters :	None
 *  Output parameters:	None
 *  Return      	 :	SUCCESS / ERROR
 *  Note         	 :
 *
 ******************************************************************************
 */
STATUS CYC_SYS_GPIO_SetAsOutputPin (UINT8 ru8Port, UINT16 ru16Pin  )
{
	STATUS lu32StatusInfo = SUCCESS;

	//	Call the GPIO function in MSP430Ware to initialise the given port and given pin as output
	GPIO_setAsOutputPin (ru8Port,ru16Pin);

	return lu32StatusInfo;
}

/*
@@********************* CYC_SYS_GPIO_SetOutputPinToHigh ***************************************
 *  Function	     :	STATUS CYC_SYS_GPIO_SetOutputPinToHigh  (UINT8 ru8Port, UINT16 ru16Pin  )
 *  Description 	 :	This sets the given pin in the given port as Digital HIGH signal
 *  Input parameters :	None
 *  Output parameters:	None
 *  Return      	 :	SUCCESS / ERROR
 *  Note         	 :
 *
 ******************************************************************************
 */
STATUS CYC_SYS_GPIO_SetOutputPinToHigh (UINT8 ru8Port, UINT16 ru16Pin  )
{
	STATUS lu32StatusInfo = SUCCESS;

	//	Call the GPIO function in MSP430Ware to set the pin to HIGH
	GPIO_setOutputHighOnPin (ru8Port, ru16Pin);

	return lu32StatusInfo;
}

/*
@@********************* CYC_SYS_GPIO_SetOutputPinToLow ***************************************
 *  Function	     :	STATUS CYC_SYS_GPIO_SetOutputPinToLow  (UINT8 ru8Port, UINT16 ru16Pin  )
 *  Description 	 :	This sets the given pin in the given port as Digital LOW signal
 *  Input parameters :	None
 *  Output parameters:	None
 *  Return      	 :	SUCCESS / ERROR
 *  Note         	 :
 *
 ******************************************************************************
 */
STATUS CYC_SYS_GPIO_SetOutputPinToLow (UINT8 ru8Port, UINT16 ru16Pin  )
{
	STATUS lu32StatusInfo = SUCCESS;

	//	Call the GPIO function in MSP430Ware to set the pin to HIGH
	GPIO_setOutputLowOnPin (ru8Port, ru16Pin);

	return lu32StatusInfo;
}

/*
@@********************* CYC_SYS_GPIO_SetPeripheralPinAsInput  ***************************************
 *  Function	     :	STATUS CYC_SYS_GPIO_SetPeripheralAsInputPin (UINT8 ru8Port, UINT16 ru16Pin  )
 *  Description 	 :	This initialises the given pin in the given port as input pin for use by a peripheral
 *
 *  Input parameters :	None
 *
 *  Output parameters:	None
 *
 *  Return      	 :	SUCCESS / ERROR
 *
 *  Note         	 :
 *
 ***************************************************************************************************
 */
STATUS CYC_SYS_GPIO_SetPeripheralPinAsInput (UINT8 ru8Port, UINT16 ru16Pin  )
{
	STATUS lu32StatusInfo = SUCCESS;

	//	Call the GPIO function in MSP430Ware to initialise the port and pins as input
	GPIO_setAsPeripheralModuleFunctionInputPin (ru8Port,ru16Pin);

	return lu32StatusInfo;
}

/*
@@********************* CYC_SYS_GPIO_SetPeripheralPinAsOutput  ***************************************
 *  Function	     :	STATUS CYC_SYS_GPIO_SetPeripheralPinAsOutput (UINT8 ru8Port, UINT16 ru16Pin  )
 *
 *  Description 	 :	This initialises the given pin in the given port as Output pin for use by a peripheral
 *
 *  Input parameters :	None
 *
 *  Output parameters:	None
 *
 *  Return      	 :	SUCCESS / ERROR
 *
 *  Note         	 :
 *
 ***************************************************************************************************
 */
STATUS CYC_SYS_GPIO_SetPeripheralPinAsOutput (UINT8 ru8Port, UINT16 ru16Pin  )
{
	STATUS lu32StatusInfo = SUCCESS;

	//	Call the GPIO function in MSP430Ware to initialise the port and pins as input
	GPIO_setAsPeripheralModuleFunctionOutputPin (ru8Port,ru16Pin);

	return lu32StatusInfo;
}


/*
@@********************* CYC_SYS_GPIO_InterruptEdgeSelect  ***************************************
 *  Function	     :	STATUS CYC_SYS_GPIO_InterruptEdgeSelect
 *
 *  Description 	 :
 *
 *  Input parameters :	None
 *
 *  Output parameters:	None
 *
 *  Return      	 :	SUCCESS / ERROR
 *
 *  Note         	 :
 *
 ***************************************************************************************************
 */
STATUS CYC_SYS_GPIO_InterruptEdgeSelect (UINT8 ru8SelectedPort, UINT16 ru16SelectedPins,UINT8 ru8EdgeSelect)
{
	//	Make use of the MSP430Ware program to enable edge detect interrupt
	GPIO_interruptEdgeSelect (ru8SelectedPort,ru16SelectedPins, ru8EdgeSelect);

	return SUCCESS;
}

/*
@@********************* CYC_SYS_GPIO_EnableInterrupts  ***************************************
 *  Function	     :	STATUS CYC_SYS_GPIO_EnableInterrupts
 *
 *  Description 	 :
 *
 *  Input parameters :	None
 *
 *  Output parameters:	None
 *
 *  Return      	 :	SUCCESS / ERROR
 *
 *  Note         	 :
 *
 ***************************************************************************************************
 */
STATUS CYC_SYS_GPIO_EnableInterrupts (UINT8 ru8SelectedPort, UINT16 ru16SelectedPins)
{
	//	Make use of the MSP430Ware program to enable the interrupt for the given port and pin
	GPIO_enableInterrupt (ru8SelectedPort,ru16SelectedPins);

	return SUCCESS;
}

/*
SW2 - BACK BUTTON- 	USER 1		-	P2.1
SW3 - SELECT BUTTON - USER 2	-	P2.2
SW4 - OPTION BUTTON - USER 3	-	P2.3
*/
__IO UINT8	gu8BackButtonPressedAndReleased = FALSE;
__IO UINT8	gu8SelectButtonPressedAndReleased = FALSE;
__IO UINT8	gu8OptionButtonPressedAndReleased = FALSE;

#if 0
//	This ISR is invoked whenever the user keys are being pressed
#pragma vector=PORT2_VECTOR
__interrupt void CYC_SYS_GPIO_ISR_UserKeys (void)
{
	__IO	UINT8 lu8Port2PinStatus=0;
	//	Read the status of the pins on GPIO port
	lu8Port2PinStatus = P2IFG;

	//	Check if it was USER 1 button
	if(lu8Port2PinStatus & 0x02)
	{
		//	If so, set the flag
		gu8BackButtonPressedAndReleased = TRUE;
		//	Clear the interrupt
		P2IFG = P2IFG & (~(0x02));
	}

	//	Check if it was USER 2 button
	if(lu8Port2PinStatus & 0x04)
	{
		//	If so, set the flag
		gu8SelectButtonPressedAndReleased = TRUE;
		//	Clear the interrupt
		P2IFG = P2IFG & (~(0x04));
	}

	//	Check if it was USER 3 button
	if(lu8Port2PinStatus & 0x08)
	{
		//	If so, set the flag
		gu8OptionButtonPressedAndReleased = TRUE;
		//	Clear the interrupt
		P2IFG = P2IFG & (~(0x08));
	}

	//	clear all the flags
	P2IFG = 0;

	 _BIC_SR_IRQ(LPM0_bits);
}
#endif

/* MODULE INTERNAL FUNCTIONS               *fffffff*/


/*-----------------------------EOF-------------------------------------------*/





    
    

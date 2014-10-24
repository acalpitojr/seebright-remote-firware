/*
@************************ CYC_IO_KEYS.c ******************************************

$MODULE IDENT		:  	KEY	$
$DESCRIPTION		: 	This file contains the functions relevant to User Buttons 1, 2 and 3

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
	TO DO:
		1> The read input pins might need to flipped based on default values


*/

/* INCLUDE FILES */
#include "CYC_Config.h"
#include "CYC_ERROR_CODES.h"
#include "CYC_IO_Common.h"
#include "..\SYS\CYC_SYS_GPIO.h"
#include "..\SYS\MSP430Ware\gpio.h"
#include "CYC_IO_KEYS.h"

/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/

/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/

/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/

/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/



/*
@@********************* CYC_IO_KEYS_InitializeUserButtons ***************************************
 *  Function	     :	STATUS CYC_IO_KEYS_InitializeUserButtons()
 *  Description 	 :	This function initalizes the user buttons 1, 2 and 3
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :	SUCCESS / ERROR
 *  Note         	 :	Following are the port assignments
 *						1. USER BUTTON 1 	- 	P2.1 (PORT 2 PIN 1)
 *						2. USER BUTTON 2 	- 	P2.2 (PORT 2 PIN 2)
 *						3. USER BUTTON 3 	- 	P2.3 (PORT 2 PIN 3)
 ******************************************************************************
 */
STATUS CYC_IO_KEYS_InitializeUserButtons()
{
	STATUS lu32StatusInfo = SUCCESS;

	//	Initialize User Buttons 1, 2 and 3 as input ports
	//	USER BUTTON 1
	lu32StatusInfo = CYC_SYS_GPIO_SetAsInputPin (USER_BUTTONS_PORT,
												USER_BUTTON_1_PIN );
	//	USER BUTTON 2
	lu32StatusInfo = CYC_SYS_GPIO_SetAsInputPin (USER_BUTTONS_PORT,
												USER_BUTTON_2_PIN );
	//	USER BUTTON 3
	lu32StatusInfo = CYC_SYS_GPIO_SetAsInputPin (USER_BUTTONS_PORT,
												USER_BUTTON_3_PIN );


#if 1
	//	Configure to receive an interrupt for all the user buttons. Generate interrupt on High to Low Transition
	CYC_SYS_GPIO_InterruptEdgeSelect(USER_BUTTONS_PORT,
									USER_BUTTON_1_PIN |USER_BUTTON_2_PIN |USER_BUTTON_3_PIN,
									GPIO_LOW_TO_HIGH_TRANSITION
									);
#endif
	//	Clear interrupts
	GPIO_clearInterruptFlag (USER_BUTTONS_PORT,
							USER_BUTTON_1_PIN |USER_BUTTON_2_PIN |USER_BUTTON_3_PIN
	    					);
	GPIO_enableInterrupt(USER_BUTTONS_PORT,
			USER_BUTTON_1_PIN |USER_BUTTON_2_PIN |USER_BUTTON_3_PIN
			);

	return lu32StatusInfo;
}


/*
@@********************* CYC_IO_KEYS_ReadUserButtonsStatus ************************************
 *  Function	     :	STATUS CYC_IO_KEYS_ReadUserButtonsStatus(UINT8 *rpu8UserButtonStatus)
 *
 *  Description 	 :	This function reads the status of user buttons 1, 2 and 3
 *
 *  Input parameters :	ru8UserButtonStatus - Pointer to the character in which
 *  					the status information will be returned by the function
 *
 *  Output parameters:
 *
 *  Return      	 :	SUCCESS
 *  					ERRORS are not checked for in this implementation
 *
 *  Note         	 :	Following will be the bits corresponding to the status
 *
 *						bit7	bit6	bit5	bit4	bit3	bit2	bit1	bit0
 *						0	 	0		0		0		0		UB3		UB2		UB1
 *
 *						UB1/UB2/UB3	 = 0		->	Button is NOT pressed
 *									 = 1		->  Button is PRESSED
 *
 ******************************************************************************
 */
STATUS CYC_IO_KEYS_ReadUserButtonsStatus(UINT8 *rpu8UserButtonStatus)
{
	STATUS lu32StatusInfo = SUCCESS;
	UINT8 lu8ConsolidatedStatus = 0;
	UINT8 lu8ReadValue = 0;


	//	Read the status of USER BUTTON 1
	lu32StatusInfo = CYC_SYS_GPIO_GetInputPinStatus (USER_BUTTONS_PORT,
													 USER_BUTTON_1_PIN,
													 &lu8ReadValue);
	lu8ConsolidatedStatus =  lu8ReadValue;

	//	Read the status of USER BUTTON 2
	lu32StatusInfo = CYC_SYS_GPIO_GetInputPinStatus (USER_BUTTONS_PORT,
													 USER_BUTTON_2_PIN,
													 &lu8ReadValue);
	//	Append the status of USER BUTTON 2 with that of USER BUTTON 1
	lu8ConsolidatedStatus =  lu8ConsolidatedStatus | (lu8ReadValue << 1);

	//	Read the status of USER BUTTON 3
	lu32StatusInfo = CYC_SYS_GPIO_GetInputPinStatus (USER_BUTTONS_PORT,
													 USER_BUTTON_3_PIN,
													 &lu8ReadValue);

	//	Append the status of USER BUTTON 3 with that of USER BUTTON 1 and 2
	lu8ConsolidatedStatus =  lu8ConsolidatedStatus | (lu8ReadValue << 2);

	//	Return the status of User Buttons 1, 2 and 3 fused into one byte
	*(rpu8UserButtonStatus) = lu8ConsolidatedStatus;

	return lu32StatusInfo;

}




/*
@@********************* CYC_IO_KEYS_InitializeTriggerButton ***************************************
 *  Function	     :	STATUS CYC_IO_KEYS_InitializeTriggerButton()
 *  Description 	 :	This function initalizes the Trigger Button
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :	SUCCESS / ERROR
 *  Note         	 :	Following are the port assignments
 *						1. Trigger Button  	- 	P2.0 (PORT 2 PIN 0)
 ***************************************************************************************************
 */
STATUS CYC_IO_KEYS_InitializeTriggerButton()
{
	STATUS lu32StatusInfo = SUCCESS;

	//	Initialize Trigger button
	lu32StatusInfo = CYC_SYS_GPIO_SetAsInputPin (TRIGGER_BUTTON_PORT,
												TRIGGER_BUTTON_PIN
												);
	return lu32StatusInfo;
}

/*
 @@********************* CYC_IO_KEYS_ReadTriggerButtonsStatus ***************************************
 *  Function	     :	STATUS CYC_IO_KEYS_ReadTriggerButtonsStatus(UINT8 *rpu8TriggerButtonStatus)
 *
 *  Description 	 :	This function reads the status of Trigger button
 *
 *  Input parameters :	rpu8TriggerButtonStatus - Pointer to the character in which
 *  					the status information will be returned by the function
 *
 *  Output parameters:
 *
 *  Return      	 :	SUCCESS
 *  					ERRORS are not checked for in this implementation
 *
 *  Note         	 :	Following will be the bits corresponding to the status
 *
 *						bit7	bit6	bit5	bit4	bit3	bit2	bit1	bit0
 *						0	 	0		0		0		0		0		0		TRG_S
 *
 *							TRG_S	 = 0		->	Trigger Button is NOT pressed
 *									 = 1		->  Trigger Button is PRESSED
 *
 ******************************************************************************
 */
STATUS CYC_IO_KEYS_ReadTriggerButtonStatus(UINT8 *rpu8TriggerButtonStatus)
{
	STATUS lu32StatusInfo = SUCCESS;
	UINT8 lu8ReadValue = 0;

	//	Read the status of TRIGGER BUTTON
	lu32StatusInfo = CYC_SYS_GPIO_GetInputPinStatus (TRIGGER_BUTTON_PORT,
													 TRIGGER_BUTTON_PIN,
													 &lu8ReadValue);

	//	Return the status of TRIGGER button
	*(rpu8TriggerButtonStatus) = lu8ReadValue;

	return lu32StatusInfo;
}

/*
@@********************* CYC_IO_KEYS_InitializeNavButton ***************************************
 *  Function	     :	STATUS CYC_IO_KEYS_InitializeNavButton()
 *  Description 	 :	This function initalizes the Nav Button
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :	SUCCESS / ERROR
 *  Note         	 :	Following are the port assignments
 *						1. Trigger Button  	- 	P2.0 (PORT 2 PIN 0)
 ***************************************************************************************************
 */
STATUS CYC_IO_KEYS_InitializeNavButton()
{
	STATUS lu32StatusInfo = SUCCESS;

	//	Initialize Trigger button
	lu32StatusInfo = CYC_SYS_GPIO_SetAsInputPin (NAV_BUTTON_PORT,
												NAV_BUTTON_PIN
												);
	return lu32StatusInfo;
}

/*
 @@********************* CYC_IO_KEYS_ReadNavButtonsStatus ***************************************
 *  Function	     :	STATUS CYC_IO_KEYS_ReadNavButtonsStatus(UINT8 *rpu8NavButtonStatus)
 *
 *  Description 	 :	This function reads the status of Nav button
 *
 *  Input parameters :	rpu8TriggerButtonStatus - Pointer to the character in which
 *  					the status information will be returned by the function
 *
 *  Output parameters:
 *
 *  Return      	 :	SUCCESS
 *  					ERRORS are not checked for in this implementation
 *
 *  Note         	 :	Following will be the bits corresponding to the status
 *
 *						bit7	bit6	bit5	bit4	bit3	bit2	bit1	bit0
 *						0	 	0		0		0		0		0		0		Nav
 *
 *							TRG_S	 = 0		->	Nav Button is NOT pressed
 *									 = 1		->  Nav Button is PRESSED
 *
 ******************************************************************************
 */
STATUS CYC_IO_KEYS_ReadNavButtonStatus(UINT8 *rpu8NavButtonStatus)
{
	STATUS lu32StatusInfo = SUCCESS;
	UINT8 lu8ReadValue = 0;

	//	Read the status of NAV BUTTON
	lu32StatusInfo = CYC_SYS_GPIO_GetInputPinStatus (NAV_BUTTON_PORT,
													 NAV_BUTTON_PIN,
													 &lu8ReadValue);

	//	Return the status of NAV button
	*(rpu8NavButtonStatus) = lu8ReadValue;

	return lu32StatusInfo;
}


/* MODULE INTERNAL FUNCTIONS               *fffffff*/


/*-----------------------------EOF-------------------------------------------*/





    
    

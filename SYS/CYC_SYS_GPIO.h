/*
@************************ CYC_SYS_GPIO.h ******************************************

$MODULE IDENT		:  	GPIO	$
$DESCRIPTION		: 	This file contains the functions relating to GPIO

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
#include "CYC_SYS_TargetConfig.h"

/* EXPORTED CONSTANT DEFINITIONS            *ccccccccc*/

/* EXPORTED MACRO DEFINITIONS               *mmmmmmmmm*/
#define GPIO_HIGH_TO_LOW_TRANSITION 		0x01
#define GPIO_LOW_TO_HIGH_TRANSITION 		0x00

/* EXPORTED TYPE DEFINITIONS                *ttttttttt*/

/* EXPORTED FUNCTIONS                       *ggggggggg*/
STATUS CYC_SYS_GPIO_SetAsInputPin (UINT8 ru8Port, UINT16 ru16Pin  );

STATUS CYC_SYS_GPIO_GetInputPinStatus (UINT8 ru8Port, UINT16 ru16Pin, UINT8* rpu8ReadValue);

STATUS CYC_SYS_GPIO_SetAsOutputPin (UINT8 ru8Port, UINT16 ru16Pin  );

STATUS CYC_SYS_GPIO_SetOutputPinToHigh (UINT8 ru8Port, UINT16 ru16Pin  );

STATUS CYC_SYS_GPIO_SetOutputPinToLow (UINT8 ru8Port, UINT16 ru16Pin  );

STATUS CYC_SYS_GPIO_SetPeripheralPinAsInput (UINT8 ru8Port, UINT16 ru16Pin  );

STATUS CYC_SYS_GPIO_SetPeripheralPinAsOutput (UINT8 ru8Port, UINT16 ru16Pin  );

/* EXPORTED DATA DEFINITIONS/DECLARATIONS   ddddddd*/

/*-----------------------------EOF-------------------------------------------*/

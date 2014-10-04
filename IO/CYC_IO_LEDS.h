/*
@************************ CYC_IO_KEYS.h ******************************************

$MODULE IDENT		:  	KEYS	$
$DESCRIPTION		: 	This file contains the functions relating to the user keys

<BEGIN REVISION>

    $Copyright: CRATUS TECHNOLOGY INC, 2013-14 $
    $Project: CYCLOPS Remote $
    $Revision: 0.1 $
    $Author: Sudhi $
    $Log:  $
    
	Revision 0.1  2014/3/6 
    Creation of the template
    
@***********************************************************************************
*/

 /*
NOTES:

*/



/* INCLUDE FILES: */


/* EXPORTED CONSTANT DEFINITIONS            *ccccccccc*/

/* EXPORTED MACRO DEFINITIONS               *mmmmmmmmm*/
#define			RED_LED							1
#define			GREEN_LED						2
#define			BLUE_LED						3


/* EXPORTED TYPE DEFINITIONS                *ttttttttt*/

/* EXPORTED FUNCTIONS                       *ggggggggg*/
VOID CYC_IO_LEDS_IntializeLEDs();

VOID CYC_IO_LEDS_TurnOnAnLED(UINT8 ru8LEDToBeTurnedOn);

VOID CYC_IO_LEDS_TurnOffAnLED(UINT8 ru8LEDToBeTurnedOff);

VOID CYC_IO_LEDS_TurnOffAllLED(void);

/* EXPORTED DATA DEFINITIONS/DECLARATIONS   ddddddd*/

/*-----------------------------EOF-------------------------------------------*/

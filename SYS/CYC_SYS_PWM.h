/*
@************************ <File Name> ******************************************

$MODULE IDENT		:  $
$DESCRIPTION		: 

<BEGIN REVISION>

    $Copyright: CRATUS TECHNOLOGY INC, 2013-14 $
    $Project: CYCLOPS Remote $
    $Revision: 0.1 $
    $Author: Sudhi $
    $Log:  $
    
	Revision 0.1  2014/3/6 
    Creation of the template
    
@********************** <File Name>*****************************************
*/

 /*
NOTES:

*/



/* INCLUDE FILES: */


/* EXPORTED CONSTANT DEFINITIONS            *ccccccccc*/

/* EXPORTED MACRO DEFINITIONS               *mmmmmmmmm*/
#define		RGB_RED_LED_CHANNEL				1
#define		RGB_GREEN_LED_CHANNEL			2
#define		RGB_BLUE_LED_CHANNEL			3
#define 	HAPTIC_MOTOR_1_CHANNEL			4
#define		HAPTIC_MOTOR_2_CHANNEL			5


/* EXPORTED TYPE DEFINITIONS                *ttttttttt*/

/* EXPORTED FUNCTIONS                       *ggggggggg*/


/* EXPORTED DATA DEFINITIONS/DECLARATIONS   ddddddd*/
STATUS CYC_SYS_PWM_InitPWMTimer();
STATUS CYC_SYS_PWM_SetDutyCycle(UINT16 ru16ChannelNumber, UINT16 ru16DutyCycle);

/*-----------------------------EOF-------------------------------------------*/

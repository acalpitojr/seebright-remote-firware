/*
@************************ CYC_SYS_ADC.h ******************************************

$MODULE IDENT		:  	ADC	$
$DESCRIPTION		: 	Header file relating to ADC functionality

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



#define JOYSTICK_X		0
#define JOYSTICK_Y		1
#define	USB_PWR			2
#define BATT_PWR		3
#define	BT_PWR			4

/* EXPORTED MACRO DEFINITIONS               *mmmmmmmmm*/

/* EXPORTED TYPE DEFINITIONS                *ttttttttt*/

/* EXPORTED FUNCTIONS                       *ggggggggg*/
STATUS CYC_SYS_ADC_Init();

STATUS CYC_SYS_ADC_ReadInputVoltage(UINT16 *rpu16JoystickData, UINT16 *rpu16PWRData);

UINT16 Read_ADC_Voltage(UINT8 port);




/* EXPORTED DATA DEFINITIONS/DECLARATIONS   ddddddd*/



/*-----------------------------EOF-------------------------------------------*/

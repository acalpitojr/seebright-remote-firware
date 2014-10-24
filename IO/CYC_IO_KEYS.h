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

#define USER2_BUTTON	<<0
#define	USER1_BUTTON	<<2
#define	USER3_BUTTON	<<4
#define	TRIG_BUTTON		<<5
#define	DOCKING_BUTTON	<<6
#define	DOWN_BUTTON		<<7
#define	UP_BUTTON		<<8

/* EXPORTED MACRO DEFINITIONS               *mmmmmmmmm*/


/* EXPORTED TYPE DEFINITIONS                *ttttttttt*/

/* EXPORTED FUNCTIONS                       *ggggggggg*/
STATUS CYC_IO_KEYS_InitializeUserButtons();
STATUS CYC_IO_KEYS_ReadUserButtonsStatus(UINT8 *rpu8UserButtonStatus);

STATUS CYC_IO_KEYS_InitializeTriggerButton();
STATUS CYC_IO_KEYS_ReadTriggerButtonStatus(UINT8 *rpu8TriggerButtonStatus);

STATUS CYC_IO_KEYS_InitializeNavButton();
STATUS CYC_IO_KEYS_ReadNavButtonStatus(UINT8 *rpu8NavButtonStatus);

UINT8 ReadAllButtons(void);




/* EXPORTED DATA DEFINITIONS/DECLARATIONS   ddddddd*/

/*-----------------------------EOF-------------------------------------------*/

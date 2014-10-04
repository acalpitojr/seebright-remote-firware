/*
@************************ CYC_ERROR_CODES.h ******************************************

$MODULE IDENT		:  	COMMON	$
$DESCRIPTION		: 	This file contains the definition of error codes

<BEGIN REVISION>

    $Copyright: CRATUS TECHNOLOGY INC, 2013-14 $
    $Project: CYCLOPS Remote $
    $Revision: 0.1 $
    $Author: Sudhi $
    $Log:  $
    
	Revision 0.1  2014/3/6 
    Creation of the template
    
@**************************************************************************************
*/

 /*
NOTES:

*/



/* INCLUDE FILES: */

/* EXPORTED CONSTANT DEFINITIONS            *ccccccccc*/

/* EXPORTED MACRO DEFINITIONS               *mmmmmmmmm*/
//-------------HIGH LEVEL ERROR CODE RANGE FOR IO MODULES---------------------------
#define	CYC_IO_KEY_ERRORS					0x00010000
#define	CYC_IO_JSTK_ERRORS					0x00020000
#define	CYC_IO_BLE_ERRORS					0x00030000
#define	CYC_IO_MOTS_ERRORS					0x00040000
#define	CYC_IO_LED_ERRORS					0x00050000
#define	CYC_IO_BAT_ERRORS					0x00060000
#define	CYC_IO_SIGNAL_ERRORS				0x00070000

//-------------HIGH LEVEL ERROR CODE RANGE FOR SYS MODULES---------------------------
#define	CYC_SYS_CLK_ERRORS					0x00001000
#define	CYC_SYS_RST_ERRORS					0x00002000
#define	CYC_SYS_ADC_ERRORS					0x00003000
#define	CYC_SYS_DMA_ERRORS					0x00004000
#define	CYC_SYS_GPIO_ERRORS					0x00005000
#define	CYC_SYS_I2C_ERRORS					0x00006000
#define	CYC_SYS_TIMER_ERRORS				0x00007000
#define	CYC_SYS_UART_ERRORS					0x00008000
#define	CYC_SYS_PWM_ERRORS					0x00009000



/* EXPORTED TYPE DEFINITIONS                *ttttttttt*/

/* EXPORTED FUNCTIONS                       *ggggggggg*/

/* EXPORTED DATA DEFINITIONS/DECLARATIONS   ddddddd*/

/*-----------------------------EOF-------------------------------------------*/

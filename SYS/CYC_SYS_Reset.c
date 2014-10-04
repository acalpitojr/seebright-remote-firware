/*
@************************ CYC_SYS_Reset.c ******************************************

$MODULE IDENT		:  RESET $
$DESCRIPTION		:  This file contains the functions relating to hardware / software reset of
						the microcontroller and PAN1721 module

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
#include "msp430.h"
#include "MSP430Ware\gpio.h"


/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/

/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/

/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/
VOID	DelayForPANReset();

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/

/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/

/*
@@********************* CYC_SYS_RST_StopWatchdog ***************************************
 *  Function	     :	CYC_SYS_RST_StopWatchdog
 *
 *  Description 	 :	Stops the watchdog timer
 *  					Called immediately after entering main
 *
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :	TO DO: Watchdog timer might need to be disabled even before main
 *  					if there are many constants to be initialized
 *
 ******************************************************************************
 */
VOID CYC_SYS_RST_StopWatchdog()
{
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
}

/*
@@********************* CYC_SYS_RST_DeAssertPAN1721ResetSignal() ***************************************
 *  Function	     :	VOID CYC_SYS_RST_DeAssertPAN1721ResetSignal()
 *
 *  Description 	 :	PAN7121 module can be RESET from the microcontroller.
 *  					Since this pin is floating at the time of start up,
 *  					PAN1721 module can't be programmed.
 *  					So, this signal needs to be set to high
 *
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 *
 ******************************************************************************
 */
VOID CYC_SYS_RST_DeAssertPAN1721ResetSignal()
{


	//	Set the PAN1721_RESET SIGNAL as Digital Output Pin
	CYC_SYS_GPIO_SetAsOutputPin (PAN_MODULE_RESET_SIGNAL_PORT,
								 PAN_MODULE_RESET_SIGNAL_PIN  );

	//	Set the signal on PAN1721_RESET SIGNAL to HIGH
	CYC_SYS_GPIO_SetOutputPinToLow(PAN_MODULE_RESET_SIGNAL_PORT,
			 PAN_MODULE_RESET_SIGNAL_PIN  );

	DelayForPANReset();

	//	Set the signal on PAN1721_RESET SIGNAL to HIGH
	CYC_SYS_GPIO_SetOutputPinToHigh(PAN_MODULE_RESET_SIGNAL_PORT,
			 PAN_MODULE_RESET_SIGNAL_PIN  );

	DelayForPANReset();


}

/*
@@********************* CYC_SYS_RST_HoldPAN1721InReset() ***************************************
 *  Function	     :	VOID CYC_SYS_RST_HoldPAN1721InReset()
 *
 *  Description 	 :	PAN7121 module can be RESET from the microcontroller.
 *  					Since this pin is floating at the time of start up,
 *  					PAN1721 module can't be programmed.
 *  					So, this signal needs to be set to high
 *
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 *
 ******************************************************************************
 */
VOID CYC_SYS_RST_HoldPAN1721InReset()
{
	//	Set the PAN1721_RESET SIGNAL as Digital Output Pin
	CYC_SYS_GPIO_SetAsOutputPin (PAN_MODULE_RESET_SIGNAL_PORT,
								 PAN_MODULE_RESET_SIGNAL_PIN  );

	//	Set the signal on PAN1721_RESET SIGNAL to HIGH
	CYC_SYS_GPIO_SetOutputPinToLow(PAN_MODULE_RESET_SIGNAL_PORT,
			 PAN_MODULE_RESET_SIGNAL_PIN  );



}

/* MODULE INTERNAL FUNCTIONS               *fffffff*/
VOID	DelayForPANReset()
{
	__IO UINT32 lu32DelayCount=0xFFFF;

	while(lu32DelayCount--);
}

/*-----------------------------EOF-------------------------------------------*/





    
    

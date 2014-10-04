/*
@************************ CYC_SYS_Clock.c ******************************************

$MODULE IDENT		:  CLK$
$DESCRIPTION		: This file contains the functions needed to set the System Clock

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
#include "CYC_SYS_Clock.h"

#include "MSP430Ware\ucs.h"
#include "MSP430Ware\gpio.h"
#include "MSP430Ware\sfr.h"


/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/

/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/
#define		MASTER_CLOCK_FRQUENCY			12000			//	Frequency in KHz

#define		XT1_XTAL_FREQUENCY				32768				//	Frequency of XT1 Crystal in Hz

#define		FLL_TO_FLLREF_RATIO				368					//	Desired frequency / XTAL Frequency

#define		XT2_XTAL_FREQUENCY				0					//	Frequency of XT1 Crystal in Hz


/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/
uint32_t clockValue = 0;

/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/

/*
@@********************* STATUS CYC_SYS_CLK_SetSystemClock ***************************************
 *  Function	     :	STATUS CYC_SYS_CLK_SetSystemClock()
 *  Description 	 :	Initializes the System Clock
 *  					Clock is set to 12 MHz
 *  Input parameters :	None
 *  Output parameters:	None
 *  Return      	 :	SUCCESS /
 *  					ERROR CODE
 *  Note         	 :	This function sets the clock to 12 MHz
 *
 ******************************************************************************
 */
STATUS CYC_SYS_CLK_SetSystemClock()
{
	STATUS	lsReturnValue = SUCCESS;

	__IO UINT32 lu32CurrentMCLKValue, lu32CurrentSMCLKValue, lu32CurrentACLKValue = 0;

	/*-------------------------------------------------------------------------
	 * Clock initialization consists of the following steps
	 * 	1. Set the External XTAL value
	 * 	2. Start the External XTAL in low frequency mode
	 * 	3.
	 * ------------------------------------------------------------------------
	 */

	//	Set XT1 IN and XT1_OUT as INPUT PERIPHERAL pin
	CYC_SYS_GPIO_SetPeripheralPinAsOutput (	XT1_PORT,
											(XT1_IN_PIN + XT1_OUT_PIN) );


	//	Select the external crystal to XT1 and set its frequency
	UCS_setExternalClockSource(UCS_BASE, XT1_XTAL_FREQUENCY, XT2_XTAL_FREQUENCY);

	/*
	-Initialize XT1 Oscillator in low frequency mode.
	-Right now it uses the highest drive current for a quick boot up
	-The capacitance value of XCAP_3 needs to be verified.
	-There is no timeout for this function. It will loop until the XTAL fault
	 flags are cleared
	*/
	UCS_LFXT1Start ( UCS_BASE, XCAP_3, XT1DRIVE_3);

	//	Set XT1CLK as FLLREF
	UCS_clockSignalInit(UCS_BASE,
						UCS_FLLREF, 		//	Signal
						UCS_XT1CLK_SELECT, 	//	Source for the signal
						UCS_CLOCK_DIVIDER_1);//	Divider value

	//	Set the DCO to produce 12 MHz
	UCS_initFLLSettle ( UCS_BASE,
						MASTER_CLOCK_FRQUENCY,	//	Desired Master clock frequency
						FLL_TO_FLLREF_RATIO //	Ratio of Master clock frequency to FLLREF
	    				);

    // Enable global oscillator fault flag
	SFR_clearInterrupt(SFR_BASE,
		SFR_OSCILLATOR_FAULT_INTERRUPT
		);
    SFR_enableInterrupt(SFR_BASE,
		SFR_OSCILLATOR_FAULT_INTERRUPT
		);

    // Enable global interrupt
    __bis_SR_register(GIE);


	//	Set OUTPUT from DCO as the clock source for Auxiliary CLOCK
	UCS_clockSignalInit(UCS_BASE,
						UCS_ACLK, 			//	Signal
						UCS_REFOCLK_SELECT, 	//	Source for the signal
						UCS_CLOCK_DIVIDER_1);//	Divider value

	//	Set OUTPUT from DCO as the clock source for Subsystem Master CLOCK
	UCS_clockSignalInit(UCS_BASE,
						UCS_SMCLK, 			//	Signal
						UCS_DCOCLKDIV_SELECT, 	//	Source for the signal
						UCS_CLOCK_DIVIDER_1);//	Divider value

	//	This is for testing ONLY
	//	Set ACLK and SMCLK on the peripheral
	CYC_SYS_GPIO_SetPeripheralPinAsOutput (	ACLK_OUT_PORT,
											ACLK_OUT_PIN );

	CYC_SYS_GPIO_SetPeripheralPinAsOutput (	SMCLK_OUT_PORT,
											SMCLK_OUT_PIN );


	lu32CurrentMCLKValue = UCS_getMCLK(UCS_BASE);

	lu32CurrentSMCLKValue = UCS_getSMCLK(UCS_BASE);

	lu32CurrentACLKValue = UCS_getACLK(UCS_BASE);

	return lsReturnValue;

}


/*
@@********************* STATUS CYC_SYS_CLK_SetSystemClock ***************************************
 *  Function	     :	STATUS CYC_SYS_CLK_SetSystemClock()
 *  Description 	 :	Initializes the System Clock
 *  					Clock is set to 12 MHz
 *  Input parameters :	None
 *  Output parameters:	None
 *  Return      	 :	SUCCESS /
 *  					ERROR CODE
 *  Note         	 :	This function sets the clock to 12 MHz
 *
 ******************************************************************************
 */


/* MODULE INTERNAL FUNCTIONS               *fffffff*/
#if 0
volatile unsigned int i;
#pragma vector=UNMI_VECTOR
__interrupt void UNMI_ISR(void)
{
  do
  {
    UCSCTL7 &= ~(XT1LFOFFG + DCOFFG);       // Clear XT1 & DCO fault flags
    SFRIFG1 &= ~OFIFG;                      // Clear OSC Fault flag
    for (i = 0x0FFF; i > 0; i--);           // Time for flag to set????
    P1OUT ^= 0x02;                          // Toggle P1.1
  }while ( (SFRIFG1 & OFIFG) );

  //	Finally, turn off
  P1OUT = 0x00;
}
#endif

STATUS status=0;

#pragma vector=UNMI_VECTOR
__interrupt void NMI_ISR(void)
{
  do {
    // If it still can't clear the oscillator fault flags after the timeout,
    // trap and wait here.
    status = UCS_clearAllOscFlagsWithTimeout(UCS_BASE,
                                             1000
                                             );
  } while(status != 0);
}

/*-----------------------------EOF-------------------------------------------*/





    
    

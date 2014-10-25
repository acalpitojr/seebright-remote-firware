/*
@************************ CYC_SYS_Init.c ******************************************

$MODULE IDENT		:  SYS	$
$DESCRIPTION		: This file contains the functions needed to initialize the system

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
#include "CYC_SYS_Reset.h"
#include "CYC_SYS_GPIO.h"
#include "CYC_SYS_Clock.h"
#include "CYC_SYS_Timer.h"
#include "CYC_SYS_PWM.h"
#include "CYC_SYS_I2C.h"
#include "CYC_SYS_UART.h"

#include "..\IO\CYC_IO_LEDS.h"
#include "..\IO\CYC_IO_JSTK.h"
#include "..\IO\CYC_IO_KEYS.h"
#include "..\IO\CYC_IO_MOTS.h"

#include "MSP430Ware\ucs.h"
#include "MSP430Ware\gpio.h"
#include "MSP430Ware\pmm.h"


/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/

/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/

/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/
STATUS CYC_SYS_ResetTargetGPIOPorts();

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/

/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/

/*
@@********************* STATUS CYC_SYS_InitializeTarget ***************************************
 *  Function	     :	STATUS CYC_SYS_InitializeTarget()
 *  Description 	 :	Initializes the System
 *  						1. Setting all the ports to be input.
 *  						2. Setting the clock to 12 MHz *
 *  Input parameters :	None
 *  Output parameters:	None
 *  Return      	 :	SUCCESS /
 *  					ERROR CODE
 *  Note         	 :	This function sets the clock to 12 MHz
 *
 ******************************************************************************
 */
STATUS CYC_SYS_InitializeTarget()
{
	STATUS	lsReturnValue = SUCCESS;

	//	Stop the watchdog timer
	CYC_SYS_RST_StopWatchdog();

	//	Reset all GPIO Ports to be output and with 0 as output
	//CYC_SYS_ResetTargetGPIOPorts();

	//Set VCore = 3 for 12MHz clock
	PMM_setVCore(PMM_BASE,PMM_CORE_LEVEL_3);

	//	Initialize the system clock to 12 MHz
	CYC_SYS_CLK_SetSystemClock();

	//	Initialize and enable TIMER 1
	CYC_SYS_TMR_InitTimer1();
	CYC_SYS_TMR_EnableTimer1();

	//	Take the PAN1721 module out of reset
	//CYC_SYS_RST_DeAssertPAN1721ResetSignal();
	//CYC_SYS_RST_HoldPAN1721InReset();

	//	Initialize the UART @57600 baudrate
	CYC_SYS_UART0_Initialize();
	//CYC_SYS_UART1_Initialize();

	//	Initialize LEDs
	CYC_IO_LEDS_IntializeLEDs();
	CYC_SYS_PWM_InitPWMTimer();

	//	Initialize user keys
	CYC_IO_KEYS_InitializeUserButtons();
	CYC_IO_KEYS_InitializeTriggerButton();
	CYC_IO_KEYS_InitializeNavButton();
	//	Initialize Joystick
	//CYC_IO_JSTK_Init();
	CYC_SYS_ADC_Init();
	//	Initialize and enable I2C port
	//CYC_SYS_I2CB0_Enable();
	//CYC_SYS_I2CB1_Enable();


	//	Initialize the Motion Sensor
	//CYC_IO_MOTS_Init();

	//	Re-initialize this as interrupts were disabled
	//CYC_IO_KEYS_InitializeUserButtons();

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
/*
@@********************* STATUS CYC_SYS_ResetTargetGPIOPorts ***************************************
 *  Function	     :	STATUS CYC_SYS_ResetTargetGPIOPorts()
 *
 *  Description 	 :	Makes all the GPIO Ports to output ports and drives '0' on it
 *
 *  Input parameters :	None
 *  Output parameters:	None
 *  Return      	 :	SUCCESS /
 *  					ERROR CODE
 *  Note         	 :	This function sets the clock to 12 MHz
 *
 ******************************************************************************
 */
STATUS CYC_SYS_ResetTargetGPIOPorts()
{

	STATUS	lsReturnValue = SUCCESS;

#ifdef __MSP430F5328__
	P1DIR = 0xFF; 					// All P1.x outputs
	P1OUT = 0; 						// All P1.x reset
	P2DIR = 0xFF; 					// All P2.x outputs
	P2OUT = 0; 						// All P2.x reset
	P3DIR = 0xFF; 					// All P3.x outputs
	P3OUT = 0; 						// All P3.x reset
	P4DIR = 0xFF; 					// All P4.x outputs
	P4OUT = 0; 						// All P4.x reset
	P5DIR = 0xFF; 					// All P5.x outputs
	P5OUT = 0; 						// All P5.x reset
	P6DIR = 0xFF; 					// All P6.x outputs
	P6OUT = 0; 						// All P6.x reset
#endif

#ifdef __MSP430F5438A__
	P1DIR = 0xFF; 					// All P1.x outputs
	P1OUT = 0; 						// All P1.x reset

	P2DIR = 0xFF; 					// All P2.x outputs
	P2OUT = 0; 						// All P2.x reset

	P3DIR = 0xFF; 					// All P3.x outputs
	P3OUT = 0; 						// All P3.x reset

	P4DIR = 0xFF; 					// All P4.x outputs
	P4OUT = 0; 						// All P4.x reset

	P5DIR = 0xFF; 					// All P5.x outputs
	P5OUT = 0; 						// All P5.x reset

	P6DIR = 0xFF; 					// All P6.x outputs
	P6OUT = 0; 						// All P6.x reset

	P7DIR = 0xFF; 					// All P7.x outputs
	P7OUT = 0; 						// All P7.x reset

	P8DIR = 0xFF; 					// All P8.x outputs
	P8OUT = 0; 						// All P8.x reset

	P9DIR = 0xFF; 					// All P9.x outputs
	P9OUT = 0; 						// All P9.x reset

	P10DIR = 0xFF; 					// All P10.x outputs
	P10OUT = 0; 						// All P10.x reset

	P11DIR = 0xFF; 					// All P11.x outputs
	P11OUT = 0; 						// All P11.x reset
#endif

	return lsReturnValue;
}

/*
@@********************* STATUS CYC_SYS_TestSystemClock ***************************************
 *  Function	     :	STATUS CYC_SYS_TestSystemClock()
 *
 *  Description 	 :
 *
 *  Input parameters :	None
 *  Output parameters:	None
 *  Return      	 :	SUCCESS /
 *  					ERROR CODE
 *  Note         	 :
 *
 ******************************************************************************
 */
STATUS CYC_SYS_TestSystemClock()
{

	P4DIR = 0xFF; 					// All P4.x outputs
	P4OUT = 0; 						// All P4.x reset

	while(1)
	{
		P4OUT = 0x01;
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");
		asm(" NOP ");

		P4OUT = 0x00;
	}
}

/*-----------------------------EOF-------------------------------------------*/





    
    

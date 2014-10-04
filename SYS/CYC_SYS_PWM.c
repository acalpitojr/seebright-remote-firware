/*
@************************ CYC_SYS_PWM.c ******************************************

$MODULE IDENT		:  	PWM	$
$DESCRIPTION		: 	This file contains the functionality of PWM

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
#include "CYC_SYS_PWM.h"
#include "CYC_SYS_TargetConfig.h"
#include "MSP430Ware\timer_a.h"

/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/

/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/
#define			RED_LED_DUTY_CYCLE			128

/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/

/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/

/*
@@********************* CYC_SYS_PWM_SetDutyCycle ***************************************
 *  Function	     :
 *  Description 	 :
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_SYS_PWM_SetDutyCycle(UINT16 ru16ChannelNumber, UINT16 ru16DutyCycle)
{
	UINT8 lu8DutyCycle=0;

	if(ru16DutyCycle >= 100)
		ru16DutyCycle = 100;

	//lu8DutyCycle = (UINT8)(((float)ru16DutyCycle*(0.01f))*511);
	lu8DutyCycle = (UINT8)(ru16DutyCycle * 5);

	//	Set the duty cycle for respective channels
	switch(ru16ChannelNumber)
	{
#ifdef TARGET_CYCLOPS_GAME
		case RGB_RED_LED_CHANNEL:
		{
			TA0CCR1 = lu8DutyCycle;                            // CCR1 PWM duty cycle
			break;
		}

		case RGB_GREEN_LED_CHANNEL:
		{
			  TA0CCR2 = lu8DutyCycle;                            // CCR1 PWM duty cycle
			  break;
		}

		case RGB_BLUE_LED_CHANNEL:
		{
			  TA0CCR3 = lu8DutyCycle;                            // CCR2 PWM duty cycle
			  break;
		}
		case HAPTIC_MOTOR_1_CHANNEL:
		{
			TA1CCR1 = lu8DutyCycle;
			break;
		}
		case HAPTIC_MOTOR_2_CHANNEL:
		{
			TA1CCR2 = lu8DutyCycle;
			break;
		}

#endif

	}

	//	Set the corresponding pins of PWM module to output mode

	return SUCCESS;
}

/*
@@********************* CYC_SYS_PWM_InitPWMTimer ***************************************
 *  Function	     :
 *  Description 	 :
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_SYS_PWM_InitPWMTimer()
{
	CYC_SYS_GPIO_SetPeripheralPinAsOutput(HAPTIC_MOTOR_1_PORT, HAPTIC_MOTOR_1_PIN);
	CYC_SYS_GPIO_SetPeripheralPinAsOutput(HAPTIC_MOTOR_2_PORT, HAPTIC_MOTOR_2_PIN);


	// PWM Period
	TA0CCR0 = 512-1;

	//RED LED
	TA0CCTL1 = OUTMOD_7;
	TA0CCR1 = 0;

	//	GREEN LED
	TA0CCTL2 = OUTMOD_7;                      // CCR1 reset/set
	TA0CCR2 = 0;                            // CCR1 PWM duty cycle

	//	BLUE LED
	TA0CCTL3 = OUTMOD_7;                      // CCR2 reset/set
	TA0CCR3 = 0;                            // CCR2 PWM duty cycle

	// PWM Period
	TA1CCR0 = 512-1;

	//Haptic Motor1
	TA1CCTL1 = OUTMOD_7;
	TA1CCR1 = 0;

	//Haptic Motor2
	TA1CCTL2 = OUTMOD_7;                      // CCR1 reset/set
	TA1CCR2 = 0;

	//Enable Counting
	TA1CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, up mode, clear TAR

	//	Enable Counting
	TA0CTL = TASSEL_1 + MC_1 + TACLR;         // ACLK, up mode, clear TAR


	//	Set the corresponding pins of PWM module to output mode

	return SUCCESS;
}


/* MODULE INTERNAL FUNCTIONS               *fffffff*/
__IO UINT16 su16FlipStatus = 0;
#pragma vector=TIMER0_A1_VECTOR
__interrupt void CYC_SYS_PWM_PWMTimer (void)
{
#if 0
	if(su16FlipStatus == 0)
	{
		//	Reload the Capture Compare Register 3
		TA1CCR0 = TA1R + RED_LED_DUTY_CYCLE;

		CYC_SYS_GPIO_SetOutputPinToHigh(RGB_RED_LED_PORT, RGB_RED_LED_PIN);

		su16FlipStatus = 1;
	}
	else
	{
		//	Reload the Capture Compare Register 3
		TA1CCR0 = TA1R + (512-RED_LED_DUTY_CYCLE);

		CYC_SYS_GPIO_SetOutputPinToLow(RGB_RED_LED_PORT, RGB_RED_LED_PIN);

		su16FlipStatus = 0;
	}
#endif
}

/*-----------------------------EOF-------------------------------------------*/





    
    

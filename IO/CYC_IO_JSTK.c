/*
@************************ CYC_IO_JSTK.c ******************************************

$MODULE IDENT		:  	Joystick	$
$DESCRIPTION		: 	This file contains the functionality for Joystick

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
#include "CYC_ERROR_CODES.h"
#include "CYC_IO_Common.h"
#include "..\SYS\CYC_SYS_ADC.h"
#include "CYC_IO_JSTK.h"

/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/

/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/

/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/

/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/

/*
@@********************* CYC_IO_JSTK_Init ***************************************
 *  Function	     :
 *  Description 	 :
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS	CYC_IO_JSTK_Init()
{
	//	Initialize ADC for Joystick
	CYC_SYS_ADC_Init();

	return SUCCESS;
}

/*
@@********************* CYC_IO_JSTK_ReadJoystickData ***************************************
 *  Function	     :
 *  Description 	 :
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS	CYC_IO_JSTK_ReadJoystickData(INT16 *rps16XYAxisValues)
{
	__IO UINT16 lu16RawXYAxisValues[2];
	__IO UINT16 lu16RawPWRValues[3];
	__IO INT16	ls16AmplifactionFactor;
	__IO UINT16 ls16XAxisOffset, ls16YAxisOffset;
	__IO UINT16	lu16MaxYAxisValue;

	//	This is the value to offset the voltage introduced by 28k resistor which
	//	is in series with the potentiometer
	ls16XAxisOffset = 500;
	ls16YAxisOffset = 410;

	//	Read the input voltages for X and Y axis values
	CYC_SYS_ADC_ReadInputVoltage((UINT16*)lu16RawXYAxisValues, (UINT16*) lu16RawPWRValues);

	//	Compensate for orientation. Joystick component on the board has been placed flipped around
	//	Horizontal axis. So the Vertical axis values need to be compensated.
	lu16MaxYAxisValue = 920;
	lu16RawXYAxisValues[1] = lu16MaxYAxisValue - lu16RawXYAxisValues[1];

	//	Compensate for the 28k resistance offset
	rps16XYAxisValues[0] = lu16RawXYAxisValues[0] - ls16XAxisOffset;
	rps16XYAxisValues[1] = lu16RawXYAxisValues[1] - ls16YAxisOffset;

	int i;
	for (i=0; i<=1; i++) {
		if (rps16XYAxisValues[i] > 500)
			rps16XYAxisValues[i] = 500;
		if (rps16XYAxisValues[i] < -500)
			rps16XYAxisValues[i] = -500;
	}

#if 0
	//	Host application is expecting the values to be in the range between -32768 and 32767.
	//	But the actual values are changing between -480 and 440. Hence the values need to be scaled
	//	Scale it by (32768 / 480) = 68.26. To play safe, scale it by a factor of 64
	ls16AmplifactionFactor = 64;
	rps16XYAxisValues[0] = rps16XYAxisValues[0] * ls16AmplifactionFactor;
	rps16XYAxisValues[1] = rps16XYAxisValues[1] * ls16AmplifactionFactor;
#endif

	return SUCCESS;
}


/* MODULE INTERNAL FUNCTIONS               *fffffff*/


/*-----------------------------EOF-------------------------------------------*/





    
    

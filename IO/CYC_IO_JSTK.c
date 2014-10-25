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
#include "stdint.h"

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
STATUS	CYC_IO_JSTK_ReadJoystickData(INT16 *joystick_output)
{
        int16_t joystick_data[2];
        int i;

        joystick_data[0] = Read_ADC_Voltage(JOYSTICK_X);
        joystick_data[1] = Read_ADC_Voltage(JOYSTICK_Y);

        for (i=0;i<=1;i++) {
            if (joystick_data[i] > 1023)
                joystick_data[i] = 1023;
            else if (joystick_data[i] < 0)
                joystick_data[i] = 0;

            joystick_data[i] -=  511;
        }

        joystick_data [1] *= (-1);

        joystick_output[0]= joystick_data[0];
        joystick_output[1]= joystick_data[1];

	return SUCCESS;
}


/* MODULE INTERNAL FUNCTIONS               *fffffff*/


/*-----------------------------EOF-------------------------------------------*/





    
    

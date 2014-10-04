/*
@************************ CYC_SYS_ADC.c ******************************************

$MODULE IDENT		:  	ADC	$
$DESCRIPTION		: 	This file contains the functionality with respect to the 12-bit ADC

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
#include "CYC_SYS_ADC.h"
#include "CYC_SYS_GPIO.h"
#include "CYC_SYS_TargetConfig.h"
#include "MSP430Ware\adc12_a.h"


/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/

/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

#define NUM_OF_PORTS	5

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/

/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/
//	Vertical and Horizontal axis information
static	__IO INT16 gs16VerticalAxisVal=0;
static	__IO INT16 gs16HorizontalAxisVal=0;

static	__IO INT16 gs16USBPwrVal=0;
static	__IO INT16 gs16BatPwrVal=0;
static	__IO INT16 gs16BTPwrVal=0;


static	__IO UINT16	gu16DataReady = FALSE;

static __IO UINT16	ADC_port[NUM_OF_PORTS];

/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/

/*
@@********************* CYC_SYS_ADC_Init() ***************************************
 *  Function	     :	CYC_SYS_ADC_Init()
 *
 *  Description 	 :	Initializes ADC for the required channels
 *
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_SYS_ADC_Init()
{
	//	Set the vertical and horizontal axis pins to analog input pins
	CYC_SYS_GPIO_SetPeripheralPinAsInput (JOYSTICK_PORT, VERT_AXIS_PIN);
	CYC_SYS_GPIO_SetPeripheralPinAsInput (JOYSTICK_PORT, HORIZ_AXIS_PIN);
	CYC_SYS_GPIO_SetPeripheralPinAsInput (USB_PWR_DETECT_PORT, USB_PWR_DETECT_PIN);
	CYC_SYS_GPIO_SetPeripheralPinAsInput (BAT_PWR_DETECT_PORT, BAT_PWR_DETECT_PIN);
	CYC_SYS_GPIO_SetPeripheralPinAsInput (BT_PWR_DETECT_PORT, BT_PWR_DETECT_PIN);

	//	Initialize the 12-bit ADC module
    ADC12_A_init(ADC12_A_BASE,						//	12-bit ADC base address
    			ADC12_A_SAMPLEHOLDSOURCE_SC,		//	Use internal ADC12_A_A bit as sample/hold signal to start conversion
    			ADC12_A_CLOCKSOURCE_ADC12OSC,		//	USE MODOSC 5MHZ Digital Oscillator as clock source
    			ADC12_A_CLOCKDIVIDER_1);			//	Use default clock divider of 1

    //	Enable the ADC module
    ADC12_A_enable(ADC12_A_BASE);


    //	Setup sampling timer
	ADC12_A_setupSamplingTimer(	ADC12_A_BASE,					//	Base address of ADC12_A_A Module
								ADC12_A_CYCLEHOLD_64_CYCLES,	//	For memory buffers 0-7 sample/hold for 64 clock cycles
								ADC12_A_CYCLEHOLD_4_CYCLES,		//	For memory buffers 8-15 sample/hold for 4 clock cycles (default)
								ADC12_A_MULTIPLESAMPLESENABLE);	//	Enable Multiple Sampling to read both horizontal and vertical axis values

	//	Configure memory buffer 1
	ADC12_A_memoryConfigure(ADC12_A_BASE,			//	Base address of the ADC12_A_A Module
							ADC12_A_MEMORY_1,		//	Configure memory buffer 1
							ADC12_A_INPUT_A1,		//	Map input A1 to memory buffer 1
							ADC12_A_VREFPOS_AVCC,	//	Vref+ = AVcc
							ADC12_A_VREFNEG_AVSS,	//	Vr- = AVss
							ADC12_A_NOTENDOFSEQUENCE);//	Memory buffer 1 is not the end of a sequence
//	Configure memory buffer 2
	ADC12_A_memoryConfigure(ADC12_A_BASE,			//	Base address of the ADC12_A_A Module
							ADC12_A_MEMORY_2,		//	Configure memory buffer 1
							ADC12_A_INPUT_A2,		//	Map input A1 to memory buffer 1
							ADC12_A_VREFPOS_AVCC,	//	Vref+ = AVcc
							ADC12_A_VREFNEG_AVSS,	//	Vr- = AVss
							ADC12_A_NOTENDOFSEQUENCE);//	Memory buffer 1 is not the end of a sequence
//	Configure memory buffer 3
	ADC12_A_memoryConfigure(ADC12_A_BASE,			//	Base address of the ADC12_A_A Module
							ADC12_A_MEMORY_3,		//	Configure memory buffer 1
							ADC12_A_INPUT_A4,		//	Map input A1 to memory buffer 1
							ADC12_A_VREFPOS_AVCC,	//	Vref+ = AVcc
							ADC12_A_VREFNEG_AVSS,	//	Vr- = AVss
							ADC12_A_NOTENDOFSEQUENCE);//	Memory buffer 1 is not the end of a sequence
//	Configure memory buffer 4
	ADC12_A_memoryConfigure(ADC12_A_BASE,			//	Base address of the ADC12_A_A Module
							ADC12_A_MEMORY_4,		//	Configure memory buffer 1
							ADC12_A_INPUT_A6,		//	Map input A1 to memory buffer 1
							ADC12_A_VREFPOS_AVCC,	//	Vref+ = AVcc
							ADC12_A_VREFNEG_AVSS,	//	Vr- = AVss
							ADC12_A_NOTENDOFSEQUENCE);//	Memory buffer 1 is not the end of a sequence

//	Configure memory buffer 5
	ADC12_A_memoryConfigure(ADC12_A_BASE,			//	Base address of the ADC12_A_A Module
							ADC12_A_MEMORY_5,		//	Configure memory buffer 1
							ADC12_A_INPUT_A7,		//	Map input A1 to memory buffer 1
							ADC12_A_VREFPOS_AVCC,	//	Vref+ = AVcc
							ADC12_A_VREFNEG_AVSS,	//	Vr- = AVss
							ADC12_A_ENDOFSEQUENCE);//	Memory buffer 1 is not the end of a sequence

#ifdef	SIGNED_2S_COMPLIMENT
	//	Set the format to provide a read back value in 2s compliment
	ADC12_A_setDataReadBackFormat (ADC12_A_BASE,
									ADC12_A_SIGNED_2SCOMPLEMENT);
#endif
	ADC12_A_setDataReadBackFormat (ADC12_A_BASE,
									ADC12_A_UNSIGNED_BINARY);
	//	Set the resolution to 12 bits
	ADC12_A_setResolution (ADC12_A_BASE,ADC12_A_RESOLUTION_12BIT);



	return SUCCESS;
}

/*
@@********************* CYC_SYS_ADC_ReadInputVoltage(UINT16 *) ***************************************
 *  Function	     :	CYC_SYS_ADC_ReadInputVoltage()
 *
 *  Description 	 :	Read 12-bit unsigned value from ADC for the required channels
 *
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_SYS_ADC_ReadInputVoltage(UINT16 *rpu16JoystickData, UINT16 *rpu16PWRData)
{

	//	Enable memory buffer 2 interrupt. It assumes that both A1 and A2 would have been read
	ADC12_A_clearInterrupt(	ADC12_A_BASE,
							ADC12IFG2);

    ADC12_A_enableInterrupt(ADC12_A_BASE,
    						ADC12IE2);

    //Enable/Start sampling and conversion
    ADC12_A_startConversion(ADC12_A_BASE,			//	Base address of ADC12_A_A Module
							ADC12_A_MEMORY_1,		//	Starting memory buffer is 1
							ADC12_A_SEQOFCHANNELS);	//	Complete one time sequence of reading

    //	Wait until the reading has been completed
    while(gu16DataReady == FALSE);

#ifdef	SIGNED_2S_COMPLIMENT
    //	Data read from ADC is in 2's compliment format, left justified.
    //	Hence, it needs to be right shifted before being sent back
    *rps16JoystickData = (gs16VerticalAxisVal)>>4;
    rps16JoystickData++;
    *rps16JoystickData = (gs16HorizontalAxisVal)>>4;
#endif

    //	Data is read as UNSIGNED 12 bit value, right justified.
    //	Interpretation of the data and normalization happens in the calling function
    *rpu16JoystickData = gs16HorizontalAxisVal;
    rpu16JoystickData++;
    *rpu16JoystickData = gs16VerticalAxisVal;

    *rpu16PWRData = gs16USBPwrVal;
    rpu16PWRData++;
    *rpu16PWRData = gs16BatPwrVal;
    rpu16PWRData++;
    *rpu16PWRData = gs16BTPwrVal;



    //	Reset the flag
    gu16DataReady = FALSE;

    return SUCCESS;
}


UINT16 Read_ADC_Voltage(UINT8 port)
{

	//	Enable memory buffer 2 interrupt. It assumes that both A1 and A2 would have been read
	ADC12_A_clearInterrupt(	ADC12_A_BASE,
							ADC12IFG2);

    ADC12_A_enableInterrupt(ADC12_A_BASE,
    						ADC12IE2);

    //Enable/Start sampling and conversion
    ADC12_A_startConversion(ADC12_A_BASE,			//	Base address of ADC12_A_A Module
							ADC12_A_MEMORY_1,		//	Starting memory buffer is 1
							ADC12_A_SEQOFCHANNELS);	//	Complete one time sequence of reading

    //	Wait until the reading has been completed
    while(gu16DataReady == FALSE);

	UINT16 returnVal = 0;

	switch (port) {
		case JOYSTICK_X:
			returnVal = gs16HorizontalAxisVal;
			break;
		case JOYSTICK_Y:
			returnVal = gs16VerticalAxisVal;
			break;
		case USB_PWR:
			returnVal = gs16USBPwrVal;
			break;
		case BATT_PWR:
			returnVal = gs16BatPwrVal;
			break;
		case BT_PWR:
			returnVal = gs16BTPwrVal;
			break;
		default:
			break;
	}

	gu16DataReady = FALSE;
	return returnVal;
}


/* MODULE INTERNAL FUNCTIONS               *fffffff*/
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_A_ISR (void)
{
    switch (__even_in_range(ADC12IV,34)){
        case  0: break;   //Vector  0:  No interrupt
        case  2: break;   //Vector  2:  ADC overflow
        case  4: break;   //Vector  4:  ADC timing overflow
        case  6:          //Vector  6:  ADC12IFG0
        case  8: break;   //Vector  8:  ADC12IFG1
        case 10:    		//Vector 10:  ADC12IFG2
        {

        	//	Set the flag to indicate that the data is available
        	//gu16DataReady = TRUE;
        }
        break;

        case 12: break;   //Vector 12:  ADC12IFG3
        case 14: break;	  //Vector 14:  ADC12IFG4
        case 16: 	      //Vector 16:  ADC12IFG5
        {
        	gs16VerticalAxisVal = ADC12_A_getResults(	ADC12_A_BASE,
        	                							ADC12_A_MEMORY_1);
        	gs16HorizontalAxisVal = ADC12_A_getResults(	ADC12_A_BASE,
        	        	                				ADC12_A_MEMORY_2);
        	gs16USBPwrVal = ADC12_A_getResults(	ADC12_A_BASE,
        										ADC12_A_MEMORY_3);
        	gs16BatPwrVal = ADC12_A_getResults(	ADC12_A_BASE,
        										ADC12_A_MEMORY_4);
        	gs16BTPwrVal = ADC12_A_getResults(	ADC12_A_BASE,
        										ADC12_A_MEMORY_5);

        	gu16DataReady = TRUE;
        }
        break;
        case 18: break;	  //Vector 18:  ADC12IFG6
        case 20: break;	  //Vector 20:  ADC12IFG7
        case 22: break;   //Vector 22:  ADC12IFG8
        case 24: break;   //Vector 24:  ADC12IFG9
        case 26: break;   //Vector 26:  ADC12IFG10
        case 28: break;   //Vector 28:  ADC12IFG11
        case 30: break;   //Vector 30:  ADC12IFG12
        case 32: break;   //Vector 32:  ADC12IFG13
        case 34: break;   //Vector 34:  ADC12IFG14
        default: break;
    }
}



/*-----------------------------EOF-------------------------------------------*/





    
    

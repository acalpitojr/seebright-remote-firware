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
	CYC_SYS_GPIO_SetPeripheralPinAsInput (GPIO_PORT_P6, GPIO_PIN1); /*VERTICAL*/
	CYC_SYS_GPIO_SetPeripheralPinAsInput (GPIO_PORT_P6, GPIO_PIN2); /*HORIZONTAL*/
	CYC_SYS_GPIO_SetPeripheralPinAsInput (GPIO_PORT_P6, GPIO_PIN6); /*USBPWRDetect*/
	CYC_SYS_GPIO_SetPeripheralPinAsInput (GPIO_PORT_P6, GPIO_PIN7); /*VBatAin*/




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
//	Configure memory buffer 6
	ADC12_A_memoryConfigure(ADC12_A_BASE,			//	Base address of the ADC12_A_A Module
							ADC12_A_MEMORY_6,		//	Configure memory buffer 1
							ADC12_A_INPUT_A6,		//	Map input A1 to memory buffer 1
							ADC12_A_VREFPOS_AVCC,	//	Vref+ = AVcc
							ADC12_A_VREFNEG_AVSS,	//	Vr- = AVss
							ADC12_A_NOTENDOFSEQUENCE);//	Memory buffer 1 is not the end of a sequence
//	Configure memory buffer 7
	ADC12_A_memoryConfigure(ADC12_A_BASE,			//	Base address of the ADC12_A_A Module
							ADC12_A_MEMORY_7,		//	Configure memory buffer 1
							ADC12_A_INPUT_A7,		//	Map input A1 to memory buffer 1
							ADC12_A_VREFPOS_AVCC,	//	Vref+ = AVcc
							ADC12_A_VREFNEG_AVSS,	//	Vr- = AVss
							ADC12_A_ENDOFSEQUENCE);//	make this end of sequence in case we want to update all at the same time



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


#if 0
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

#endif

uint8_t ADC_DATA_READY = 0;


UINT16 Read_ADC_Voltage(uint8_t pin)
{
    /*clear ALL ADC interrupts*/
    uint16_t reading = 0x0000;
    ADC12_A_clearInterrupt( ADC12_A_BASE,  0xFFFF);
    uint16_t channel = 0x0000;
    switch(pin)
    {
    case 0x00:
        channel = ADC12IFG0;
        break;
    case 0x01:
        channel = ADC12IFG1;
            break;
    case 0x02:
        channel = ADC12IFG2;
            break;
    case 0x03:
        channel = ADC12IFG3;
            break;
    case 0x04:
        channel = ADC12IFG4;
            break;
    case 0x05:
        channel = ADC12IFG5;
            break;
    case 0x06:
        channel = ADC12IFG6;
            break;
    case 0x07:
        channel = ADC12IFG7;
            break;
    default:
        channel = ADC12IFG1;
        break;

    }

    ADC12_A_enableInterrupt(ADC12_A_BASE, channel);

    //Enable/Start sampling and conversion
    ADC_DATA_READY = 0;
    ADC12_A_startConversion(ADC12_A_BASE,  pin,  ADC12_A_SINGLECHANNEL); /*start adc conversion of the selected pin*/
    /*wait for conversion to complete*/
    while(ADC_DATA_READY == 0)
    {
        /*wait, might want to add a timeout here*/
    }



    ADC12_A_disableInterrupt(ADC12_A_BASE, channel);

   reading = ADC12_A_getResults( ADC12_A_BASE,  pin);
   return  reading;

}



/* MODULE INTERNAL FUNCTIONS               *fffffff*/
#pragma vector = ADC12_VECTOR
__interrupt void ADC12_A_ISR (void)
{
    switch (__even_in_range(ADC12IV,34)){
        case  0x00: break;   //Vector  0:  No interrupt
        case  0x02: break;   //Vector  2:  ADC overflow
        case  0x04: break;   //Vector  4:  ADC timing overflow
        case  0x06:          //Vector  6:  ADC12IFG0
        /*MEM0 has an ADC READING*/
            ADC_DATA_READY = 1;
            break;
        case  0x08:
            /*MEM1 has an ADC READING*/
            ADC_DATA_READY = 1;
            break;   //Vector  8:  ADC12IFG1
        case 0x0A:          //Vector 10:  ADC12IFG2
            /*MEM2 has an ADC READING*/
            ADC_DATA_READY = 1;
            break;

        case 0x0C: break;   //Vector 12:  ADC12IFG3
        /*MEM3 has an ADC READING*/
        ADC_DATA_READY = 1;

        case 0x0E:    //Vector 14:  ADC12IFG4
        /*MEM4 has an ADC READING*/
            ADC_DATA_READY = 1;
            break;
        case 0x10:        //Vector 16:  ADC12IFG5
            ADC_DATA_READY = 1;
        break;
        case 0x12:
            /*MEM6 has an ADC READING*/
            ADC_DATA_READY = 1;
            break;    //Vector 18:  ADC12IFG6
        case 0x14: /*MEM7 has an ADC READING*/
            ADC_DATA_READY = 1;
            break;      //Vector 20:  ADC12IFG7
        case 0x16:
            ADC_DATA_READY = 1;
            /*MEM8 has an ADC READING*/break;   //Vector 22:  ADC12IFG8
        case 0x18:
            ADC_DATA_READY = 1;
            /*MEM9 has an ADC READING*/break;   //Vector 24:  ADC12IFG9
        case 0x1A:
            ADC_DATA_READY = 1;
            /*MEM10has an ADC READING*/ break;   //Vector 26:  ADC12IFG10
        case 0x1C:
            ADC_DATA_READY = 1;
            /*MEM11has an ADC READING*/ break;   //Vector 28:  ADC12IFG11
        case 0x1E:
            ADC_DATA_READY = 1;
            /*MEM12has an ADC READING*/ break;   //Vector 30:  ADC12IFG12
        case 0x20:
            ADC_DATA_READY = 1;
            /*MEM13has an ADC READING*/ break;   //Vector 32:  ADC12IFG13
        case 0x22:
            ADC_DATA_READY = 1;
            /*MEM14 has an ADC READING*/ break;   //Vector 34:  ADC12IFG14
        case 0x24:
            ADC_DATA_READY = 1;
            /*MEM15 has an ADC READING*/ break;   //Vector 34:  ADC12IFG14
        default:
            break;
    }

    ADC12_A_clearInterrupt( ADC12_A_BASE,  0xFFFF);
}


/*-----------------------------EOF-------------------------------------------*/





    
    

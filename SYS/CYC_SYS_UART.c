/*
@************************ CYC_SYS_UART.c ******************************************

$MODULE IDENT		:  $
$DESCRIPTION		: 

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
#include "CYC_SYS_TargetConfig.h"
#include "CYC_SYS_UART.h"
#include "MSP430Ware\inc\hw_memmap.h"
#include "MSP430Ware\gpio.h"
#include "MSP430Ware\usci_uartbaudrate.h"
#include "MSP430Ware\usci_uart.h"
#include "MSP430Ware\ucs.h"
#include "string.h"


/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/

/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/
//	This is INT (CLK_SOURCE\DESIRED_BAUD_RATE). For Auxiliary Soruce being 12 Mhz and Baudrate being 57600
//	the value is INT(12000000/57600) = 208
//#define		BAUDRATE_CLK_PRESCALER				208
//#define		BAUDRATE_CLK_PRESCALER				26
//#define		BAUDRATE_CLK_PRESCALER				13
#define     BAUDRATE_CLK_PRESCALER              6  /*NEED TO FIX THIS SO WE CAN SELECT ANY BAUD RATE WE WANT*/
//	Modulator value is computed as follows:
//	round((208.333 - 208) x 16)
#define	 	FIRST_STAGE_MODULATOR_VALUE		8

#define		SECOND_STAGE_MODULATOR_VALUE	0

#define		MAX_COMMAND_LENGTH				5
/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/

/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/


UINT8 gu8RxData = 0x00;
UINT8 gu8RxDataCount = 0x00;

/* MODULE INTERNAL FUNCTIONS               *fffffff*/
volatile UINT8 gu8Rx0Buffer[RX_BUFFER_SIZE];
volatile UINT8 gu8Rx1Buffer[RX_BUFFER_SIZE];

/*
@@********************* CYC_SYS_UART_Initialize ***************************************
 *  Function	     :
 *  Description 	 :
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_SYS_UART0_Initialize()
{

	//	Set the values
	UINT32	__IO lu32ACLKValue = 0;

	STATUS	lsReturnValue = SUCCESS;

	//	Get Auxiliary Clock Source value
	lu32ACLKValue = UCS_getACLK(UCS_BASE);

#ifdef TARGET_MSP430F5438A_EXPERIMENTER_BOARD
    //P3.4,5 = USCI_A0 TXD/RXD
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P3,
        GPIO_PIN4
        );

    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P3,
            GPIO_PIN5
            );
#endif

#ifdef TARGET_CYCLOPS_GAME
    //P3.3 = USCI_A0 TXD
    GPIO_setAsPeripheralModuleFunctionOutputPin(
        GPIO_PORT_P3,
        GPIO_PIN3
        );

    //P3.4 = USCI_A0 RXD
    GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P3,
            GPIO_PIN4
            );
#endif

    /*
    Call the MSP43Ware function to initialize the UART port with the following configurations
    	1. PORT 0
    	2. Use SMCLK as Source
    	3. Value of SMCLK is 12MHz
    	4. Prescalar value to generate 57600 is 208
    	5. First stage modulator value is 5
    	6. Second stage modulator is ignored and value is set to 0
    	7. No Parity bits

     */

    /*CHANGE THIS SO WE CAN SET ANY BAUD RATE WE WANT, DATA SHEET PG 907*/
    USCI_UART_initAdvance ( UART_PORT_0_BASE_ADDRESS,
    						USCI_UART_CLOCKSOURCE_SMCLK,
    						BAUDRATE_CLK_PRESCALER,
    						FIRST_STAGE_MODULATOR_VALUE,
    						SECOND_STAGE_MODULATOR_VALUE,
    						USCI_UART_NO_PARITY,
    						USCI_UART_LSB_FIRST,
    						USCI_UART_ONE_STOP_BIT,
    						USCI_UART_MODE,
    						USCI_UART_OVERSAMPLING_BAUDRATE_GENERATION
        				);


    //Enable UART module for operation
    USCI_UART_enable(USCI_A0_BASE);

    //Enable Receive Interrupt
    USCI_UART_clearInterruptFlag(USCI_A0_BASE,
    		USCI_UART_RECEIVE_INTERRUPT
        );
    USCI_UART_enableInterrupt(USCI_A0_BASE,
    		USCI_UART_RECEIVE_INTERRUPT
        );




    return lsReturnValue;
}



STATUS CYC_SYS_UART1_Initialize()
{
//	Set the values
UINT32	__IO lu32ACLKValue = 0;

STATUS	lsReturnValue = SUCCESS;

//	Get Auxiliary Clock Source value
lu32ACLKValue = UCS_getACLK(UCS_BASE);

#ifdef TARGET_MSP430F5438A_EXPERIMENTER_BOARD
//P3.4,5 = USCI_A0 TXD/RXD
GPIO_setAsPeripheralModuleFunctionOutputPin(
    GPIO_PORT_P3,
    GPIO_PIN4
    );

GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P3,
        GPIO_PIN5
        );
#endif

#ifdef TARGET_CYCLOPS_GAME
//P3.3 = USCI_A0 TXD
GPIO_setAsPeripheralModuleFunctionOutputPin(
    GPIO_PORT_P4,
    GPIO_PIN4
    );

//P3.4 = USCI_A0 RXD
GPIO_setAsPeripheralModuleFunctionInputPin(
        GPIO_PORT_P4,
        GPIO_PIN5
        );
#endif

/*
Call the MSP43Ware function to initialize the UART port with the following configurations
	1. PORT 1
	2. Use SMCLK as Source
	3. Value of SMCLK is 12MHz
	4. Prescalar value to generate 57600 is 208
	5. First stage modulator value is 5
	6. Second stage modulator is ignored and value is set to 0
	7. No Parity bits

 */
USCI_UART_initAdvance ( UART_PORT_1_BASE_ADDRESS,
						USCI_UART_CLOCKSOURCE_SMCLK,
						BAUDRATE_CLK_PRESCALER,
						FIRST_STAGE_MODULATOR_VALUE,
						SECOND_STAGE_MODULATOR_VALUE,
						USCI_UART_NO_PARITY,
						USCI_UART_LSB_FIRST,
						USCI_UART_ONE_STOP_BIT,
						USCI_UART_MODE,
						USCI_UART_OVERSAMPLING_BAUDRATE_GENERATION
    				);


//Enable UART module for operation
USCI_UART_enable(USCI_A1_BASE);

//Enable Receive Interrupt
USCI_UART_clearInterruptFlag(USCI_A1_BASE,
		USCI_UART_RECEIVE_INTERRUPT
    );
USCI_UART_enableInterrupt(USCI_A1_BASE,
		USCI_UART_RECEIVE_INTERRUPT
    );




return lsReturnValue;
}

/*
@@********************* CYC_SYS_UART_TransmitData(UINT8 *rpu8Data, UINT8 ru8DataLen) ***************************************
 *  Function	     :
 *  Description 	 :
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_SYS_UART_TransmitData(UINT8 port, UINT8 *rpu8Data, UINT8 ru8DataLen)
{
	int portBase;

	switch (port) {
	case 0:
		portBase = USCI_A0_BASE;
		break;
	case 1:
		portBase = USCI_A1_BASE;
		break;
	default:
		return !SUCCESS;
	}

	STATUS	lsReturnValue = SUCCESS;

	UINT8 lu8TxBufferLen = 0;

	for(lu8TxBufferLen = 0; lu8TxBufferLen < ru8DataLen; lu8TxBufferLen++)
	{
		USCI_UART_transmitData(portBase,rpu8Data[lu8TxBufferLen]);

		//	Keep looping until the BUSY FLAG is set
		while(USCI_UART_queryStatusFlags(portBase,USCI_UART_BUSY));

	}

	return lsReturnValue;
}

/*
@@********************* CYC_SYS_UART_ReadCommandData(UINT8 *rpu8Data, UINT8* ru8DataLen) ***************************************
 *  Function	     :
 *  Description 	 :
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_SYS_UART_ReadCommandData(UINT8 port, UINT8 *rpu8Data, UINT8* ru8DataLen)
{
	__IO UINT16 lu16LoopCount = 0;

	UINT8* portBuffer;

	switch (port) {
	case 0:
		portBuffer = &gu8Rx0Buffer;
		break;
	case 1:
		portBuffer = &gu8Rx1Buffer;
		break;
	default:
		return !SUCCESS;
	}

	//	Check if there is any data
	if(gu8RxDataCount == 0)
	{
		//	Indicate 0 length and return
		*ru8DataLen = gu8RxDataCount;

		return SUCCESS;
	}
	else
	{
		if(gu8RxDataCount == MAX_COMMAND_LENGTH)
		{
			//	Copy the 5 bytes received as command from mobile app
			for(lu16LoopCount=0; lu16LoopCount < MAX_COMMAND_LENGTH; lu16LoopCount++)
			{
				rpu8Data[lu16LoopCount] = &portBuffer[lu16LoopCount];
			}
			//	Reset the buffer count
			gu8RxDataCount = 0;
			//	Update the length
			*ru8DataLen = MAX_COMMAND_LENGTH;
		}
		else
		{
			//	Indicate 0 length and return, as the data received is insuffecient
			*ru8DataLen = 0;

			return SUCCESS;
		}

	}

	return SUCCESS;
}

void SendSerial (UINT8* string)
{

	CYC_SYS_UART_TransmitData(SERIAL_UART_PORT, string, strlen((char)string));

}

//******************************************************************************
//
//This is the USCI_A0 interrupt vector service routine.
//
//******************************************************************************
#pragma vector=USCI_A0_VECTOR
__interrupt void USCI_A0_ISR (void)
{
#if 1
    switch (__even_in_range(UCA0IV,4)){
        //Vector 2 - RXIFG
        case 2:

        	if(gu8RxDataCount <= RX_BUFFER_SIZE)
        	{
        		//Receive the data
				gu8RxData = USCI_UART_receiveData(USCI_A0_BASE);
				gu8Rx0Buffer[gu8RxDataCount] = gu8RxData ;
				gu8RxDataCount++;
				//	Circularly fill the buffer
				gu8RxDataCount = gu8RxDataCount & (RX_BUFFER_SIZE-1);
        	}
            break;
        default: break;
    }
#endif
}

#pragma vector=USCI_A1_VECTOR
__interrupt void USCI_A1_ISR (void)
{
    switch (__even_in_range(UCA1IV,4)){
        //Vector 2 - RXIFG
        case 2:
#if 0
        	if(gu8RxDataCount <= RX_BUFFER_SIZE)
        	{
        		//Receive the data
				gu8RxData = USCI_UART_receiveData(USCI_A1_BASE);
				gu8Rx1Buffer[gu8RxDataCount] = gu8RxData ;
				gu8RxDataCount++;
				//	Circularly fill the buffer
				gu8RxDataCount = gu8RxDataCount & (RX_BUFFER_SIZE-1);
        	}
#endif

        	uint8_t received_byte = USCI_UART_receiveData(USCI_A1_BASE);  /*good for debugging.  reading the register clears the interupt flag?*/
        	INT_SPP_RX_IRQHandler(received_byte);   /*pass the byte from the uart into this function which will store it and parse it accordingly*/


            break;
        default: break;
    }
}



/*-----------------------------EOF-------------------------------------------*/





    
    

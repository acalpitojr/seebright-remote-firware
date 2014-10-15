/*
@************************ <File Name> ******************************************

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
    
@********************** <File Name>*****************************************
*/

 /*
NOTES:

*/



/* INCLUDE FILES: */


/* EXPORTED CONSTANT DEFINITIONS            *ccccccccc*/

/* EXPORTED MACRO DEFINITIONS               *mmmmmmmmm*/
#define		UART_PORT_0						1
#define		UART_PORT_0_BASE_ADDRESS		USCI_A0_BASE
#define		UART_PORT_1_BASE_ADDRESS		USCI_A1_BASE
#define		UART_PORT_0_BAUD_RATE			57600
#define		RX_BUFFER_SIZE					32

#define 		BT_UART_PORT				1
#define			SERIAL_UART_PORT			0

/* EXPORTED TYPE DEFINITIONS                *ttttttttt*/

/* EXPORTED FUNCTIONS                       *ggggggggg*/
uint8_t CYC_SYS_UART0_Initialize();
uint8_t CYC_SYS_UART1_Initialize();

void SendSerial (uint8_t* string);

uint8_t CYC_SYS_UART_TransmitData(uint8_t port, uint8_t *rpu8Data, uint8_t ru8DataLen);

uint8_t CYC_SYS_UART_ReadCommandData(uint8_t port, uint8_t *rpu8Data, uint8_t* ru8DataLen);

/* EXPORTED DATA DEFINITIONS/DECLARATIONS   ddddddd*/
extern uint8_t gu8RxBuffer[RX_BUFFER_SIZE];

/*-----------------------------EOF-------------------------------------------*/

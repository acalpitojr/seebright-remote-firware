/*
@************************ CYC_SYS_I2C.c ******************************************

$MODULE IDENT		:  	I2C	$
$DESCRIPTION		: 	This file contains the firmware functionality for I2C communication

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
#include "CYC_ERROR_CODES.h"
#include "CYC_SYS_I2C.h"
#include "CYC_SYS_Timer.h"
#include "CYC_SYS_TargetConfig.h"
#include "MSP430Ware\ucs.h"

/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/

/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/
typedef enum {
    STATE_WAITING,
    STATE_READING,
    STATE_WRITING
} MasterI2CState;

typedef struct
{
    __IO MasterI2CState msMasterI2CState;

    UINT8	mu8SlaveRegister;		//	First slave register

    UINT8 mu8SlaveRegisterWritten;	//	0 if slave register has not been written yet

    UINT8 *mpu8Data;				//	Data

    UINT16 mu16Length;				//	Length

    UINT8	mu8Enabled;				//	Is I2C enabled?
} MasterI2CInfo_t;


/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/
#define I2C_TIMEOUT_MS  (2500)				//	2500 ms

#if 0
#if defined I2C_B0
#define CTL0    UCB0CTL0
#define CTL1    UCB0CTL1
#define IE      UCB0IE
#define BR0     UCB0BR0
#define BR1     UCB0BR1
#define I2CSA   UCB0I2CSA
#define RXBUF   UCB0RXBUF
#define TXBUF   UCB0TXBUF
#define IFG     UCB0IFG
#define I2C_VEC USCI_B0_VECTOR
#define IV      UCB0IV
#elif defined I2C_B1
#define CTL0    UCB1CTL0
#define CTL1    UCB1CTL1
#define IE      UCB1IE
#define BR0     UCB1BR0
#define BR1     UCB1BR1
#define I2CSA   UCB1I2CSA
#define RXBUF   UCB1RXBUF
#define TXBUF   UCB1TXBUF
#define IFG     UCB1IFG
#define I2C_VEC USCI_B1_VECTOR
#define IV      UCB1IV
#else
#error  Define either I2C_B0 or I2C_B1 in your configuration.
#endif
#endif


#define I2C_B0_MODE(void)  do {P3SEL |= 0x03;} while (0)
#define GPIO_B0_MODE(void) do {P3SEL &= ~0x03;} while (0)
#define SET_B0_SCL(void)   do {P3OUT |= 0x02;} while (0)
#define CLEAR_B0_SCL(void) do {P3OUT &= ~0x02;} while (0)
#define SET_B0_SDA(void)   do {P3OUT |= 0x01;} while (0)
#define CLEAR_B0_SDA(void) do {P3OUT &= ~0x01;} while (0)


#define I2C_B1_MODE(void)  do {P4SEL |= 0x06;} while (0)
#define I2C_B1_GPIO_MODE(void) do {P4SEL &= ~0x06;} while (0)
#define I2C_B1_SET_SCL(void)   do {P4OUT |= 0x04;} while (0)
#define I2C_B1_CLEAR_SCL(void) do {P4OUT &= ~0x04;} while (0)
#define I2C_B1_SET_SDA(void)   do {P4OUT |= 0x02;} while (0)
#define I2C_B1_CLEAR_SDA(void) do {P4OUT &= ~0x02;} while (0)





/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/
static MasterI2CInfo_t gsI2CB0 =
{
    .mu8Enabled = 0
};


static MasterI2CInfo_t gsI2CB1 =
{
    .mu8Enabled = 0
};


/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/

/*
@@********************* CYC_SYS_I2C_Enable ***************************************
 *  Function	     :
 *  Description 	 :
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************/




STATUS CYC_SYS_I2CB0_Enable(void)
{

    UINT32 lu32SMClk;
    UINT16 lu16BaudRate;

    //	If I2C is already enabled, return SUCCESS code and no need to do anything
    if (gsI2CB0.mu8Enabled)
        return SUCCESS;

    //	Put the I2C module in RESET state
    UCB0CTL1 |= UCSWRST;

    //	Select the peripheral mode working for the I2C pins
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3,GPIO_PIN1 + GPIO_PIN0);
    //I2C_B0_MODE();

    //	Set to synchronous master mode
    UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;

    //	Use sub-master clock
    UCB0CTL1 = UCSSEL_2 + UCSWRST;

    //	Set slave clock frequency to 400kHz
    //	Get the SMCLK frequency
    lu32SMClk = UCS_getSMCLK(UCS_BASE);
    //	Divide the source clock frequency by 400 KHz to get the baudrate factor
    lu16BaudRate = lu32SMClk / 400000L;
    //	Assign LSB and MSB values for the baud rate register
    UCB0BR0 = (unsigned char)(lu16BaudRate & 0xFF);
    UCB0BR1 = (unsigned char)((lu16BaudRate >> 8) & 0xFF);

    //	Take I2C module out of reset
    UCB0CTL1 &= ~UCSWRST;

    // Enable interrupts
    UCB0IE |= UCTXIE | UCRXIE | UCNACKIE;

       //  Initialize I2C Info struct
       gsI2CB0.msMasterI2CState = STATE_WAITING;
       gsI2CB0.mu8SlaveRegister = 0;
       gsI2CB0.mu8SlaveRegisterWritten = 0;
       gsI2CB0.mpu8Data = 0;
       gsI2CB0.mu16Length = 0;
       gsI2CB0.mu8Enabled = 1;

    return SUCCESS;

}

STATUS CYC_SYS_I2CB1_Enable(void)
{
    UINT32 lu32SMClk;
    UINT16 lu16BaudRate;



    //  Put the I2C module in RESET state
    UCB1CTL1 |= UCSWRST;

    //  Select the peripheral mode working for the I2C pins
    //I2C_B1_MODE();
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4,GPIO_PIN1 + GPIO_PIN2);
    //  Set to synchronous master mode
    UCB1CTL0 = UCMST + UCMODE_3 + UCSYNC;

    //  Use sub-master clock
    UCB1CTL1 = UCSSEL_2 + UCSWRST;

    //  Set slave clock frequency to 400kHz
    //  Get the SMCLK frequency
    lu32SMClk = UCS_getSMCLK(UCS_BASE);
    //  Divide the source clock frequency by 400 KHz to get the baudrate factor
    lu16BaudRate = lu32SMClk / 400000L;
    //  Assign LSB and MSB values for the baud rate register
    UCB1BR0 = (unsigned char)(lu16BaudRate & 0xFF);
    UCB1BR1 = (unsigned char)((lu16BaudRate >> 8) & 0xFF);

    //  Take I2C module out of reset
    UCB1CTL1 &= ~UCSWRST;




    return SUCCESS;

}
/*
@@********************* CYC_SYS_I2C_Disable ***************************************
 *  Function	     :
 *  Description 	 :
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_SYS_I2CB0_Disable(void)
{
	//	If I2C module is already disabled, nothing to do
    if (!gsI2CB0.mu8Enabled)
        return SUCCESS;

    //	Reset the I2C Module
    UCB0CTL1 |= UCSWRST;

    //	Get the I2C pins to function as GPIO
    GPIO_B0_MODE();
    //	Set the pins to high state
    SET_B0_SCL();
    SET_B0_SDA();

    //	As a final step update the flag status
    gsI2CB0.mu8Enabled = 0;
    return 0;

}



STATUS CYC_SYS_I2CB1_Disable(void)
{
    //  If I2C module is already disabled, nothing to do
    if (!gsI2CB1.mu8Enabled)
        return SUCCESS;

    //  Reset the I2C Module
    UCB1CTL1 |= UCSWRST;

    //  Get the I2C pins to function as GPIO
    GPIO_B1_MODE();
    //  Set the pins to high state
    SET_B1_SCL();
    SET_B1_SDA();

    //  As a final step update the flag status
    gsI2CB1.mu8Enabled = 0;
    return 0;

}


/*
@@********************* CYC_SYS_I2C_Write ***************************************
 *  Function	     :
 *  Description 	 :
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_SYS_I2CB0_Write(	UINT8 ru8SlaveAddress,
							UINT8 ru8RegisterAddress,
							UINT8 ru8Length,
							UINT8 *rpu8Data)
{
	UINT32 lu32StartTimeStamp, lu32CurrentTimeStamp;

	//	Return FAILURE if
	if (!gsI2CB0.mu8Enabled)
		return CYC_SYS_I2C_ERRORS;
	//	If length is 0, it is successful anyways!
	if (!ru8Length)
		return SUCCESS;

    //	Gather the information into  I2C info structure
	gsI2CB0.msMasterI2CState = STATE_WRITING;
	gsI2CB0.mu8SlaveRegister = ru8RegisterAddress;
	gsI2CB0.mu8SlaveRegisterWritten = 0;
	gsI2CB0.mpu8Data = rpu8Data;
	gsI2CB0.mu16Length = ru8Length;

	//	Assign the slave address
	UCB0I2CSA = ru8SlaveAddress;

    //	Begin transmitting
	UCB0CTL1 |= UCTR;
    UCB0CTL1 |= UCTXSTT;

    //	Get the current time stamp, in order to track timeout
    CYC_SYS_TMR_GetClockMs(&lu32StartTimeStamp);

    while(gsI2CB0.msMasterI2CState != STATE_WAITING)   /*HERE WE WAIT UNTIL I2C WRITE PROCESS IS COMPLETE THROUGH ISR*/
    {


    	//	Get current time stamp to see if write operation timed out
    	CYC_SYS_TMR_GetClockMs(&lu32CurrentTimeStamp);

    	//	If timeout has occurred, then reset I2C state and return an error
        if (lu32CurrentTimeStamp >= (lu32StartTimeStamp + I2C_TIMEOUT_MS))
        {
            //	Stop transmission
            UCB0CTL1 |= UCTXSTP;
        	//	Reset I2C to waiting state
            gsI2CB0.msMasterI2CState = STATE_WAITING;
            //	Disable and re-enable the I2C port, sending an error
            CYC_SYS_I2CB0_Disable();
            //	Clear and set I2C pins to high
            CYC_SYS_TMR_DelayInMilliSeconds(1);
            CLEAR_B0_SCL();
            CLEAR_B0_SDA();
            CYC_SYS_TMR_DelayInMilliSeconds(1);
            SET_B0_SCL();
            SET_B0_SDA();
            //	Re-enable I2C port
            CYC_SYS_I2CB0_Enable();
            return CYC_SYS_I2C_ERRORS;
        }
    }

    return	SUCCESS;
}

/*
@@********************* CYC_SYS_I2C_Write ***************************************
 *  Function	     :
 *  Description 	 :
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_SYS_I2CB0_Read(	UINT8 ru8SlaveAddress,
							UINT8 ru8RegisterAddress,
							UINT8 ru8Length,
							UINT8 *rpu8Data)
{
	UINT32 lu32StartTimeStamp, lu32CurrentTimeStamp;

	//	Return FAILURE if
	if (!gsI2CB0.mu8Enabled)
		return CYC_SYS_I2C_ERRORS;
	//	If length is 0, it is successful anyways!
	if (!ru8Length)
		return SUCCESS;

    //	Gather the information into  I2C info structure
	gsI2CB0.msMasterI2CState = STATE_READING;
	gsI2CB0.mu8SlaveRegister = ru8RegisterAddress;
	gsI2CB0.mu8SlaveRegisterWritten = 0;
	gsI2CB0.mpu8Data = rpu8Data;
	gsI2CB0.mu16Length = ru8Length;

	//	Assign the slave address
	UCB0I2CSA = ru8SlaveAddress;

    //	Begin transmitting
	UCB0CTL1 |= UCTR;
    UCB0CTL1 |= UCTXSTT;

    //	Get the current time stamp, in order to track timeout
    CYC_SYS_TMR_GetClockMs(&lu32StartTimeStamp);

    while(gsI2CB0.msMasterI2CState != STATE_WAITING)
    {
        //	Enter into low power mode until the interrupt is raised  DO NOT WANT TO DO THIS
    	//__bis_SR_register(LPM0_bits + GIE);

    	//	Get current time stamp to see if write operation timed out
    	CYC_SYS_TMR_GetClockMs(&lu32CurrentTimeStamp);

    	//	If timeout has occurred, then reset I2C state and return an error
        if (lu32CurrentTimeStamp >= (lu32StartTimeStamp + I2C_TIMEOUT_MS))
        {
            //	Stop transmission
            UCB0CTL1 |= UCTXSTP;
        	//	Reset I2C to waiting state
            gsI2CB0.msMasterI2CState = STATE_WAITING;
            //	Disable and re-enable the I2C port, sending an error
            CYC_SYS_I2CB0_Disable();
            //	Clear and set I2C pins to high
            CYC_SYS_TMR_DelayInMilliSeconds(1);
            CLEAR_B0_SCL();
            CLEAR_B0_SDA();
            CYC_SYS_TMR_DelayInMilliSeconds(1);
            SET_B0_SCL();
            SET_B0_SDA();
            //	Re-enable I2C port
            CYC_SYS_I2CB0_Enable();
            return CYC_SYS_I2C_ERRORS;
        }
    }

    return	SUCCESS;

}

/* MODULE INTERNAL FUNCTIONS               *fffffff*/
#pragma vector = USCI_B0_VECTOR
__interrupt void I2CB0_ISR(void)
{
    switch(__even_in_range(UCB0IV,12))
    {
    	//	No ACK (NAK) interrupt
        case 4:
        {
        	gsI2CB0.msMasterI2CState = STATE_WAITING;	//	Reset the state
        	UCB0CTL1 |= UCTXSTP;
            break;
        }

        //	 RX interrupt
        case 10:
        {
        	//	Reset RX Flag
            UCB0IFG &= ~UCRXIFG;


            gsI2CB0.mu16Length--;
            //	If length is non zero, then keep receiving
            if (gsI2CB0.mu16Length)
            {
                //	If only one byte left, prepare stop signal
                if (gsI2CB0.mu16Length == 1)
                    UCB0CTL1 |= UCTXSTP;
            }
            else
            {
            	//	If length is 0, then next state is waiting
            	gsI2CB0.msMasterI2CState = STATE_WAITING;
            }
            /* Read RXBUF last because we don't want to release SCL until we're
             * sure we're ready.
             */
            *(gsI2CB0.mpu8Data) = UCB0RXBUF;
            //	Make the pointer to point to next empty location
            gsI2CB0.mpu8Data++;

            break;

        }//	End of RX interrupt

        //	TX Interrupt
        case 12:
        {
        	//	Reset the TX Interrupt flag
            UCB0IFG &= ~UCTXIFG;

            //	Handle the case according to the current state
            switch (gsI2CB0.msMasterI2CState)
            {
            	case STATE_WRITING:
            	{
            		//	If slave reigster is not yet written, write it
            		if (!gsI2CB0.mu8SlaveRegisterWritten)
            		{
            			gsI2CB0.mu8SlaveRegisterWritten = 1;
            			UCB0TXBUF = gsI2CB0.mu8SlaveRegister;
            		}
            		else if (gsI2CB0.mu16Length)	//	If length is non-zero then there are bytes to be transmitted
            		{
            			//	Send next byte, increment pointer
            			UINT8 next = gsI2CB0.mpu8Data[0];
            			//	Buffer book keeping
            			gsI2CB0.mpu8Data++;
            			gsI2CB0.mu16Length--;

						/* Writing to TXBUF must always be the final operation. */
            			UCB0TXBUF = next;
            		}
            		else		//	If length is zero, then stop
            		{
						gsI2CB0.msMasterI2CState = STATE_WAITING;
						UCB0CTL1 |= UCTXSTP;
            		}

            	}//	End of case STATE_WRITING
            	break;

            	case STATE_READING:
            	{
            		//	If slave reigster is not yet written, write it
            		if (!gsI2CB0.mu8SlaveRegisterWritten)
            		{
            			gsI2CB0.mu8SlaveRegisterWritten = 1;
            			UCB0TXBUF = gsI2CB0.mu8SlaveRegister;
            		}
            		else
            		{
            			//	Repeated start, switch to RX mode
            		    UCB0CTL1 &= ~UCTR;
            		    UCB0CTL1 |= UCTXSTT;

            			/* If single byte, prepare stop signal immediately. */
            			if (gsI2CB0.mu16Length == 1)
            			{
							/* Well, not IMMEDIATELY. First we need to make sure
							 * the start signal got sent.
							 */
							while (UCB0CTL1 & UCTXSTT);
							UCB0CTL1 |= UCTXSTP;
            			}
            		}

            	}//	End of case STATE_READING:
        		break;

            	case STATE_WAITING:
            	{
            		default:
            			break;
            	}

            }//	End of switch (gsI2CB0.msMasterI2CState)

        }//	End of case 12

        case 0:     /* No interrupt. */
        case 2:     /* Arbitration lost interrupt. */
        case 6:     /* Start condition interrupt. */
        case 8:     /* Stop condition interrupt. */
        default:
            break;
    }
    //__bic_SR_register_on_exit(LPM0_bits);  /*EXIT LOW POWER MODE?*/
}


/*-----------------------------EOF-------------------------------------------*/





    
    

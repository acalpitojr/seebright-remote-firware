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



#define I2C_MODE(void)  do {P3SEL |= 0x03;} while (0)
#define GPIO_MODE(void) do {P3SEL &= ~0x03;} while (0)
#define SET_SCL(void)   do {P3OUT |= 0x02;} while (0)
#define CLEAR_SCL(void) do {P3OUT &= ~0x02;} while (0)
#define SET_SDA(void)   do {P3OUT |= 0x01;} while (0)
#define CLEAR_SDA(void) do {P3OUT &= ~0x01;} while (0)


#define I2C_B1_MODE(void)  do {P4SEL |= 0x06;} while (0)
#define I2C_B1_GPIO_MODE(void) do {P4SEL &= ~0x06;} while (0)
#define I2C_B1_SET_SCL(void)   do {P4OUT |= 0x04;} while (0)
#define I2C_B1_CLEAR_SCL(void) do {P4OUT &= ~0x04;} while (0)
#define I2C_B1_SET_SDA(void)   do {P4OUT |= 0x02;} while (0)
#define I2C_B1_CLEAR_SDA(void) do {P4OUT &= ~0x02;} while (0)





/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/
static MasterI2CInfo_t gsI2C =
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
 ******************************************************************************
 */

STATUS CYC_SYS_I2C_Enable(void)
{
    UINT32 lu32SMClk;
    UINT16 lu16BaudRate;

    //	If I2C is already enabled, return SUCCESS code and no need to do anything
    if (gsI2C.mu8Enabled)
        return SUCCESS;

    //	Put the I2C module in RESET state
    CTL1 |= UCSWRST;

    //	Select the peripheral mode working for the I2C pins
    I2C_MODE();

    //	Set to synchronous master mode
    CTL0 = UCMST + UCMODE_3 + UCSYNC;

    //	Use sub-master clock
    CTL1 = UCSSEL_2 + UCSWRST;

    //	Set slave clock frequency to 400kHz
    //	Get the SMCLK frequency
    lu32SMClk = UCS_getSMCLK(UCS_BASE);
    //	Divide the source clock frequency by 400 KHz to get the baudrate factor
    lu16BaudRate = lu32SMClk / 400000L;
    //	Assign LSB and MSB values for the baud rate register
    BR0 = (unsigned char)(lu16BaudRate & 0xFF);
    BR1 = (unsigned char)((lu16BaudRate >> 8) & 0xFF);

    //	Take I2C module out of reset
    CTL1 &= ~UCSWRST;

    //	Enable interrupts
    IE |= UCTXIE | UCRXIE | UCNACKIE;

    //	Initialize I2C Info struct
    gsI2C.msMasterI2CState = STATE_WAITING;
    gsI2C.mu8SlaveRegister = 0;
    gsI2C.mu8SlaveRegisterWritten = 0;
    gsI2C.mpu8Data = 0;
    gsI2C.mu16Length = 0;
    gsI2C.mu8Enabled = 1;

    return SUCCESS;

}

STATUS CYC_SYS_I2CB1_Enable(void)
{
    UINT32 lu32SMClk;
    UINT16 lu16BaudRate;



    //  Put the I2C module in RESET state
    UCB1CTL1 |= UCSWRST;

    //  Select the peripheral mode working for the I2C pins
    I2C_B1_MODE();

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
STATUS CYC_SYS_I2C_Disable(void)
{
	//	If I2C module is already disabled, nothing to do
    if (!gsI2C.mu8Enabled)
        return SUCCESS;

    //	Reset the I2C Module
    CTL1 |= UCSWRST;

    //	Get the I2C pins to function as GPIO
    GPIO_MODE();
    //	Set the pins to high state
    SET_SCL();
    SET_SDA();

    //	As a final step update the flag status
    gsI2C.mu8Enabled = 0;
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
STATUS CYC_SYS_I2C_Write(	UINT8 ru8SlaveAddress,
							UINT8 ru8RegisterAddress,
							UINT8 ru8Length,
							UINT8 *rpu8Data)
{
	UINT32 lu32StartTimeStamp, lu32CurrentTimeStamp;

	//	Return FAILURE if
	if (!gsI2C.mu8Enabled)
		return CYC_SYS_I2C_ERRORS;
	//	If length is 0, it is successful anyways!
	if (!ru8Length)
		return SUCCESS;

    //	Gather the information into  I2C info structure
	gsI2C.msMasterI2CState = STATE_WRITING;
	gsI2C.mu8SlaveRegister = ru8RegisterAddress;
	gsI2C.mu8SlaveRegisterWritten = 0;
	gsI2C.mpu8Data = rpu8Data;
	gsI2C.mu16Length = ru8Length;

	//	Assign the slave address
    I2CSA = ru8SlaveAddress;

    //	Begin transmitting
    CTL1 |= UCTR | UCTXSTT;

    //	Get the current time stamp, in order to track timeout
    CYC_SYS_TMR_GetClockMs(&lu32StartTimeStamp);

    while(gsI2C.msMasterI2CState != STATE_WAITING)
    {
        //	Enter into low power mode until the interrupt is raised
    	__bis_SR_register(LPM0_bits + GIE);

    	//	Get current time stamp to see if write operation timed out
    	CYC_SYS_TMR_GetClockMs(&lu32CurrentTimeStamp);

    	//	If timeout has occurred, then reset I2C state and return an error
        if (lu32CurrentTimeStamp >= (lu32StartTimeStamp + I2C_TIMEOUT_MS))
        {
            //	Stop transmission
        	CTL1 |= UCTXSTP;
        	//	Reset I2C to waiting state
            gsI2C.msMasterI2CState = STATE_WAITING;
            //	Disable and re-enable the I2C port, sending an error
            CYC_SYS_I2C_Disable();
            //	Clear and set I2C pins to high
            CYC_SYS_TMR_DelayInMilliSeconds(1);
            CLEAR_SCL();
            CLEAR_SDA();
            CYC_SYS_TMR_DelayInMilliSeconds(1);
            SET_SCL();
            SET_SDA();
            //	Re-enable I2C port
            CYC_SYS_I2C_Enable();
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
STATUS CYC_SYS_I2C_Read(	UINT8 ru8SlaveAddress,
							UINT8 ru8RegisterAddress,
							UINT8 ru8Length,
							UINT8 *rpu8Data)
{
	UINT32 lu32StartTimeStamp, lu32CurrentTimeStamp;

	//	Return FAILURE if
	if (!gsI2C.mu8Enabled)
		return CYC_SYS_I2C_ERRORS;
	//	If length is 0, it is successful anyways!
	if (!ru8Length)
		return SUCCESS;

    //	Gather the information into  I2C info structure
	gsI2C.msMasterI2CState = STATE_READING;
	gsI2C.mu8SlaveRegister = ru8RegisterAddress;
	gsI2C.mu8SlaveRegisterWritten = 0;
	gsI2C.mpu8Data = rpu8Data;
	gsI2C.mu16Length = ru8Length;

	//	Assign the slave address
    I2CSA = ru8SlaveAddress;

    //	Begin transmitting
    CTL1 |= UCTR | UCTXSTT;

    //	Get the current time stamp, in order to track timeout
    CYC_SYS_TMR_GetClockMs(&lu32StartTimeStamp);

    while(gsI2C.msMasterI2CState != STATE_WAITING)
    {
        //	Enter into low power mode until the interrupt is raised
    	__bis_SR_register(LPM0_bits + GIE);

    	//	Get current time stamp to see if write operation timed out
    	CYC_SYS_TMR_GetClockMs(&lu32CurrentTimeStamp);

    	//	If timeout has occurred, then reset I2C state and return an error
        if (lu32CurrentTimeStamp >= (lu32StartTimeStamp + I2C_TIMEOUT_MS))
        {
            //	Stop transmission
        	CTL1 |= UCTXSTP;
        	//	Reset I2C to waiting state
            gsI2C.msMasterI2CState = STATE_WAITING;
            //	Disable and re-enable the I2C port, sending an error
            CYC_SYS_I2C_Disable();
            //	Clear and set I2C pins to high
            CYC_SYS_TMR_DelayInMilliSeconds(1);
            CLEAR_SCL();
            CLEAR_SDA();
            CYC_SYS_TMR_DelayInMilliSeconds(1);
            SET_SCL();
            SET_SDA();
            //	Re-enable I2C port
            CYC_SYS_I2C_Enable();
            return CYC_SYS_I2C_ERRORS;
        }
    }

    return	SUCCESS;

}

/* MODULE INTERNAL FUNCTIONS               *fffffff*/
#pragma vector = I2C_VEC
__interrupt void I2C_ISR(void)
{
    switch(__even_in_range(IV,12))
    {
    	//	No ACK (NAK) interrupt
        case 4:
        {
        	gsI2C.msMasterI2CState = STATE_WAITING;	//	Reset the state
            CTL1 |= UCTXSTP;
            break;
        }

        //	 RX interrupt
        case 10:
        {
        	//	Reset RX Flag
            IFG &= ~UCRXIFG;


            gsI2C.mu16Length--;
            //	If length is non zero, then keep receiving
            if (gsI2C.mu16Length)
            {
                //	If only one byte left, prepare stop signal
                if (gsI2C.mu16Length == 1)
                    CTL1 |= UCTXSTP;
            }
            else
            {
            	//	If length is 0, then next state is waiting
            	gsI2C.msMasterI2CState = STATE_WAITING;
            }
            /* Read RXBUF last because we don't want to release SCL until we're
             * sure we're ready.
             */
            *(gsI2C.mpu8Data) = RXBUF;
            //	Make the pointer to point to next empty location
            gsI2C.mpu8Data++;

            break;

        }//	End of RX interrupt

        //	TX Interrupt
        case 12:
        {
        	//	Reset the TX Interrupt flag
            IFG &= ~UCTXIFG;

            //	Handle the case according to the current state
            switch (gsI2C.msMasterI2CState)
            {
            	case STATE_WRITING:
            	{
            		//	If slave reigster is not yet written, write it
            		if (!gsI2C.mu8SlaveRegisterWritten)
            		{
            			gsI2C.mu8SlaveRegisterWritten = 1;
            			TXBUF = gsI2C.mu8SlaveRegister;
            		}
            		else if (gsI2C.mu16Length)	//	If length is non-zero then there are bytes to be transmitted
            		{
            			//	Send next byte, increment pointer
            			UINT8 next = gsI2C.mpu8Data[0];
            			//	Buffer book keeping
            			gsI2C.mpu8Data++;
            			gsI2C.mu16Length--;

						/* Writing to TXBUF must always be the final operation. */
						TXBUF = next;
            		}
            		else		//	If length is zero, then stop
            		{
						gsI2C.msMasterI2CState = STATE_WAITING;
						CTL1 |= UCTXSTP;
            		}

            	}//	End of case STATE_WRITING
            	break;

            	case STATE_READING:
            	{
            		//	If slave reigster is not yet written, write it
            		if (!gsI2C.mu8SlaveRegisterWritten)
            		{
            			gsI2C.mu8SlaveRegisterWritten = 1;
            			TXBUF = gsI2C.mu8SlaveRegister;
            		}
            		else
            		{
            			//	Repeated start, switch to RX mode
            			CTL1 &= ~UCTR;
            			CTL1 |= UCTXSTT;

            			/* If single byte, prepare stop signal immediately. */
            			if (gsI2C.mu16Length == 1)
            			{
							/* Well, not IMMEDIATELY. First we need to make sure
							 * the start signal got sent.
							 */
							while (CTL1 & UCTXSTT);
							CTL1 |= UCTXSTP;
            			}
            		}

            	}//	End of case STATE_READING:
        		break;

            	case STATE_WAITING:
            	{
            		default:
            			break;
            	}

            }//	End of switch (gsI2C.msMasterI2CState)

        }//	End of case 12

        case 0:     /* No interrupt. */
        case 2:     /* Arbitration lost interrupt. */
        case 6:     /* Start condition interrupt. */
        case 8:     /* Stop condition interrupt. */
        default:
            break;
    }
    __bic_SR_register_on_exit(LPM0_bits);
}


/*-----------------------------EOF-------------------------------------------*/





    
    

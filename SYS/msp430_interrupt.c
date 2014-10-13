/*
@************************  ******************************************

$MODULE IDENT		:  IO / MOTS	$
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


/**
 *  @defgroup MSP430 System Layer
 *  @brief  MSP430 System Layer APIs.
 *          To interface with any platform, eMPL needs access to various
 *          system layer functions.
 *
 *  @{
 *      @file       msp430_interrupt.c
 *      @brief      Supports common interrupt vectors using callbacks.
 *      @details    The following MSP430s are supported:
 *
 *                  MSP430F5528
 *                  MSP430F5529
 */

#include <stdio.h>
#include <string.h>
#include "msp430.h"
#include "msp430_interrupt.h"
#include "CYC_Config.h"

//	Sudhi:
//	Added the MACRO defintion __MSP430F5438A__

#if !defined __MSP430F5528__ && !defined __MSP430F5529__ && \
    !defined __MSP430F5229__ && !defined __MSP430F5438A__ \
    && !defined __MSP430F5328__

#error  The interrupt driver does not support this MSP430.
#endif

__IO UINT8 gu8PowerOffMode = FALSE;

#define PINS_PER_PORT   (8)
struct msp430_int_s
{
    void (*p1_cbs[PINS_PER_PORT])(void);
    void (*p2_cbs[PINS_PER_PORT])(void);
    unsigned char p1_exit[PINS_PER_PORT];
    unsigned char p2_exit[PINS_PER_PORT];
    /* Masks for each GPIO pin. */
    unsigned char p1_active_low;
    unsigned char p2_active_low;
};
static struct msp430_int_s msp_int = {0};

static inline unsigned char int_pin_to_index(unsigned short pin)
{
    /* Remove INT_PORT_Px from pin; index = pin/2 - 1. */
    return ((pin & 0x1F) >> 1) - 1;
}

/* Why does this even deserve its own function? */
static inline unsigned char index_to_bit(unsigned char index)
{
    return 1 << index;
}

#pragma vector=PORT1_VECTOR
__interrupt void P1_ISR(void)
{
    unsigned char index, bit;
    index = int_pin_to_index(P1IV);
    bit = index_to_bit(index);

    if (msp_int.p1_cbs[index])
        msp_int.p1_cbs[index]();
    P1IFG &= ~bit;

    switch (msp_int.p1_exit[index]) {
    case INT_EXIT_NONE:
        break;
    case INT_EXIT_LPM0:
        __bic_SR_register_on_exit(LPM0_bits);
        break;
    case INT_EXIT_LPM1:
        __bic_SR_register_on_exit(LPM1_bits);
        break;
    case INT_EXIT_LPM2:
        __bic_SR_register_on_exit(LPM2_bits);
        break;
    case INT_EXIT_LPM3:
        __bic_SR_register_on_exit(LPM3_bits);
        break;
    case INT_EXIT_LPM4:
        __bic_SR_register_on_exit(LPM4_bits);
        break;
    default:
        break;
    }
}

UINT8 gu8InterruptCount = 0;

#pragma vector=PORT2_VECTOR
__interrupt void P2_ISR(void)
{
    __IO UINT8 lu8Port2PinStatus=0;
	unsigned char index, bit;
    index = int_pin_to_index(P2IV);
    bit = index_to_bit(index);

    lu8Port2PinStatus = P2IV;
	//	Read the status of the pins on GPIO port
	lu8Port2PinStatus = P2IFG;

	if(gu8PowerOffMode == TRUE)
	{
		//	clear all the flags
		P2IFG = 0;

		gu8InterruptCount++;

		if(gu8InterruptCount > 3)
		{
			//	clear all the flags
			P2IFG = 0;

			//	Start watchdog timer so that it resets the system
			//WDTCTL = WDTPW ;	// Start watchdog timer
			WDTCTL = 0x11 ;	// Start watchdog timer

			//gu8InterruptCount = 0;
			__bic_SR_register_on_exit(LPM0_bits);

		}

#if 0
		//	Check if both BACK button and OPTION button have been pressed
		if( (lu8Port2PinStatus & 0x02) ||
			(lu8Port2PinStatus & 0x08)	)
		{
			//	clear all the flags
			P2IFG = 0;
			//	See if the interrupt is corresponding to the press-release relating to power off
			//	if so, don't exit from the mode
			if(gu8InterruptCount == 0)
			{
				gu8InterruptCount++;
			}
			else
			{
				//	clear all the flags
				P2IFG = 0;

				//	Start watchdog timer so that it resets the system
				WDTCTL = WDTPW ;	// Start watchdog timer

				//gu8InterruptCount = 0;
				__bic_SR_register_on_exit(LPM0_bits);

			}
		}
		else
		{
			//	clear all the flags
			P2IFG = 0;
		}
#endif

	}

	if(gu8PowerOffMode == FALSE)
	{
		if (msp_int.p2_cbs[index])
			msp_int.p2_cbs[index]();
		P2IFG &= ~bit;

		switch (msp_int.p2_exit[index]) {
		case INT_EXIT_NONE:
			break;
		case INT_EXIT_LPM0:
			__bic_SR_register_on_exit(LPM0_bits);
			break;
		case INT_EXIT_LPM1:
			__bic_SR_register_on_exit(LPM1_bits);
			break;
		case INT_EXIT_LPM2:
			__bic_SR_register_on_exit(LPM2_bits);
			break;
		case INT_EXIT_LPM3:
			__bic_SR_register_on_exit(LPM3_bits);
			break;
		case INT_EXIT_LPM4:
			__bic_SR_register_on_exit(LPM4_bits);
			break;
		default:
			break;
		}
	}
}

int msp430_int_init(void)
{
    memset(&msp_int, 0, sizeof(msp_int));
    msp430_int_enable();
    return 0;
}

int msp430_int_enable(void)
{
    unsigned char index;

    P1IFG &= ~0xFF;
    P1IE &= ~0xFF;
    P2IFG &= ~0xFF;
    P2IE &= ~0xFF;

    for (index = 0; index < 8; index++) {
        unsigned char bit = index_to_bit(index);
        if (msp_int.p1_cbs[index]) {
            P1IFG |= bit;
            P1IE |= bit;
        }
        if (msp_int.p2_cbs[index]) {
            P2IFG |= bit;
            P2IE |= bit;
        }
    }

    return 0;
}

int msp430_int_disable(void)
{
    P1IFG &= ~0xFF;
    P1IE &= ~0xFF;
    P2IFG &= ~0xFF;
    P2IE &= ~0xFF;
    return 0;
}

int msp430_reg_int_cb(void (*cb)(void), unsigned short pin,
    unsigned char lp_exit, unsigned char active_low)
{
    unsigned char index, bit;

    index = int_pin_to_index(pin);
    bit = index_to_bit(index);

    if (pin & INT_PORT_P1) {
        msp_int.p1_cbs[index] = cb;
        if (active_low) {
            /* If interrupt enabled, use pullup resistor.
             * If interrupt disabled, output high.
             */
            P1OUT |= bit;
            /* Flag set on falling edge. */
            P1IES |= bit;
            msp_int.p1_active_low |= bit;
        } else {
            P1OUT &= ~bit;
            msp_int.p1_active_low &= ~bit;
        }

        if (!cb) {
            /* No callback registered. Disable this interrupt if necessary. */
            /* Set to output mode. */
            P1DIR |= bit;
            /* Disable pullup/pulldown resistor. */
            P1REN &= ~bit;
            /* Disable interrupt, clear flag. */
            P1IFG &= ~bit;
            P1IE &= ~bit;
            msp_int.p1_exit[index] = INT_EXIT_NONE;
        } else {
            /* Set to input mode. */
            P1DIR &= ~bit;
            /* Enable pullup/pulldown resistor. */
            P1REN |= bit;
            /* Enable interrupt, clear flag. */
            P1IFG &= ~bit;
           // P1IE |= bit;  /*HE SHOULD NOT BE DOING THIS HERE.  THE APPLICATION IS NOT EVEN READY TO HANDLE INTERRUPTS FROM THIS PIN*/
            msp_int.p1_exit[index] = lp_exit;
        }
    } else if (pin & INT_PORT_P2) {
        msp_int.p2_cbs[index] = cb;
        if (active_low) {
            /* If interrupt enabled, use pullup resistor.
             * If interrupt disabled, output high.
             */
            P2OUT |= bit;
            /* Flag set on falling edge. */
            P2IES |= bit;
            msp_int.p2_active_low |= bit;
        } else {
            P2OUT &= ~bit;
            msp_int.p2_active_low &= ~bit;
        }

        if (!cb) {
            /* No callback registered. Disable this interrupt if necessary. */
            /* Set to output mode. */
            P2DIR |= bit;
            /* Disable pullup/pulldown resistor. */
            P2REN &= ~bit;
            /* Disable interrupt, clear flag. */
            P2IFG &= ~bit;
            P2IE &= ~bit;
            msp_int.p2_exit[index] = INT_EXIT_NONE;
        } else {
            /* Set to input mode. */
            P2DIR &= ~bit;
            /* Enable pullup/pulldown resistor. */
            P2REN |= bit;
            /* Enable interrupt, clear flag. */
            P2IFG &= ~bit;
            P2IE |= bit;
            msp_int.p2_exit[index] = lp_exit;
        }
    }
    return 0;
}

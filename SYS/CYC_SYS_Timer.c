/*
@************************ CYC_SYS_Timer.c ******************************************

$MODULE IDENT		:  	TIMER 	$
$DESCRIPTION		: 	This file contains the functions relating to timers

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
#include	"CYC_Config.h"
#include	"CYC_ERROR_CODES.h"
#include	"CYC_SYS_TargetConfig.h"
#include	"CYC_SYS_Timer.h"
#include 	"msp430.h"

#define		NUM_OF_ARTICFITIAL_TIMERS	16


/* MODULE EXTERNAL DATA DEFINITIONS        *ddddddd*/
CYC_SYS_TMR_TimerInfo_t gasTimerInfo[NUMBER_OF_TIMERS];
static UINT16		Timer_Array[NUM_OF_ARTICFITIAL_TIMERS];
static UINT16 		TimerActiveFlags;
static UINT16		TimerEventFlags;



/* MODULE INTERNAL CONSTANT DEFINITIONS    *ccccccc*/

/* MODULE INTERNAL TYPE DEFINITIONS        *ttttttt*/

/* MODULE INTERNAL MACRO DEFINITIONS       *mmmmmmm*/

/* MODULE INTERNAL FUNCTION PROTOTYPES     *fffffff*/

/* MODULE INTERNAL DATA DEFINITIONS        *ddddddd*/
static CYC_SYS_TMR_TimerInfo_t *spsTimer1Info ;			//	TODO: Initialize it in the init function

/* EXPORTED (GLOBAL or External) FUNCTIONS *ggggggg*/

/*
@@********************* CYC_SYS_TMR_InitTimer1 ***************************************
 *  Function	     :	CYC_SYS_TMR_InitTimer1
 *  Description 	 :	It initializes the Timer Info structure
 *  Input parameters :
 *  Output parameters:
 *  Return      	 :
 *  Note         	 :	TIMER 1 uses channel of TIMER_B in MSP430. This is a 16-bit timer
 *  					It uses the ACLK. ACLK is set to derive its source from internal REF0 Clock
 ******************************************************************************
 */
STATUS CYC_SYS_TMR_InitTimer1()
{
	//Initalize artificial timers
	TimerActiveFlags = 0;
	TimerEventFlags = 0;

    //	Initialize the pointer to the timer info record of Timer 1
    spsTimer1Info = &gasTimerInfo[TIMER_1];

    //	Compute the number of ticks per millisecond
    gasTimerInfo[TIMER_1].mu32ACLKFrequency = REFOCLK_FREQUENCY;
    gasTimerInfo[TIMER_1].mu16TicksPerInterrupt = REFOCLK_FREQUENCY / 1000;

    //	This timer is going to generate an interrupt every 1 ms
    gasTimerInfo[TIMER_1].mu32MillisecondsPerInterrupt = 1;

    //	Update the records to state that the timer has NOT yet been enabled
    gasTimerInfo[TIMER_1].mu8Enabled = 0;

    //	Reset the remaining milliseconds counter
    gasTimerInfo[TIMER_1].mu16TimerRemainingMilliseconds = 0;

    return SUCCESS;
}

/*
@@********************* CYC_SYS_TMR_EnableTimer1 ***************************************
 *  Function	     :	CYC_SYS_TMR_EnableTimer1
 *
 *  Description 	 :	It enables the Timer 1 to start ticking
 *
 *  Input parameters :
 *
 *  Output parameters:
 *
 *  Return      	 :
 *
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_SYS_TMR_EnableTimer1()
{
    //	Enable interrupt for TBCCR0
    TBCCTL0 = CCIE;

    //	Load Capture Compare Register to generate an interrupt after required number of ticks
    TBCCR0 = TBR + gasTimerInfo[TIMER_1].mu16TicksPerInterrupt;

    //	Use ACLK, set timer to up-count mode, and start timer at zero
    TBCTL = TBSSEL_1 | MC_2 | TBCLR;

    //	Update the remaining number of milliseconds count
    gasTimerInfo[TIMER_1].mu16TimerRemainingMilliseconds += (gasTimerInfo[TIMER_1].mu16TimerRemainingMilliseconds %
    		gasTimerInfo[TIMER_1].mu32MillisecondsPerInterrupt);

    //	Update the records to state that the timer has been enabled
    gasTimerInfo[TIMER_1].mu8Enabled = 1;

    /* Enable interrupts. */
    __bis_SR_register(GIE);

    return SUCCESS;
}

/*
@@********************* CYC_SYS_TMR_DelayInMilliSeconds ***************************************
 *  Function	     :	CYC_SYS_TMR_DelayInMilliSeconds
 *
 *  Description 	 :	It is a blocking function call which waits for given number of milliseconds
 *  					to expire.
 *  Input parameters :
 *
 *  Output parameters:
 *
 *  Return      	 :
 *
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_SYS_TMR_DelayInMilliSeconds(UINT32 ru32NumberOfMilliSeconds)
{
    __IO UINT32 lu32StartTime = spsTimer1Info->mu32TimeStamp;

	//	If the timer has not been enabled, return error code
    if (!spsTimer1Info->mu8Enabled)
        return 1;

    //	Wait until the number of milliseconds have expired
    //	NOTE: No need to worry about the timestamp value overflowing. It needs 48 days to overflow!
    while ((spsTimer1Info->mu32TimeStamp - lu32StartTime) < ru32NumberOfMilliSeconds);
//        __bis_SR_register(LPM0_bits + GIE);
    return 0;
}

/*
@@********************* CYC_SYS_TMR_GetClockMs ***************************************
 *  Function	     :	CYC_SYS_TMR_GetClockMs
 *
 *  Description 	 :	It returns the current time stamp
 *
 *  Input parameters :
 *
 *  Output parameters:
 *
 *  Return      	 :
 *
 *  Note         	 :
 ******************************************************************************
 */
STATUS CYC_SYS_TMR_GetClockMs(UINT32 *rpu32Count)
{
    if (!rpu32Count)
        return CYC_SYS_TIMER_ERRORS;

    *rpu32Count = spsTimer1Info->mu32TimeStamp;

    return SUCCESS;
}

VOID CYC_SYS_TMR_DisableTimer1()
{
	TBCTL &= MC_0;

}

//BEGIN ARTIFICIAL TIMER FUNCTIONS
//ADDED BY TAYLOR, WRITTEN BY MAX DUNNE

/*
@@********************* InitTimer********************************************
 *  Function	     :	InitTimer
 *
 *  Description 	 :	Sets and starts an artificial timer with "NewTime" number of milliseconds
 *
 *  Input parameters : 	Num: the number of the timer to set
 *  					NewTimer: Number of milliseconds until TimerExpired event is triggered
 *
 *  Output parameters:
 *
 *  Return      	 : Status
 *
 *  Note         	 : 	This function set the NewTime number of milliseconds to the chosen timer
 *  					designated by Num. InitTimer sets the TimerExpired flag to NOT_EXPIRED, and
 *  					sets the active flag to TIMER_ACTIVE which begins counting.
 *
 ******************************************************************************
 */
STATUS InitTimer(unsigned char Num, unsigned int NewTime)
{
	if (Num >= NUM_OF_ARTICFITIAL_TIMERS)
	    return;
	Timer_Array[Num] = NewTime;
	TimerEventFlags &= ~(1 << Num);
	TimerActiveFlags |= (1 << Num);
	return SUCCESS;
}

/*
@@********************* StartTimer********************************************
 *  Function	     :	StartTimer
 *
 *  Description 	 :	Sets the active flag of timer "Num".
 *
 *  Input parameters : 	Num: the number of the timer to set
 *
 *  Output parameters:
 *
 *  Return      	 : Status
 *
 *  Note         	 : 	Setting the active flag starts counting on the requested timer
 *
 ******************************************************************************
 */
STATUS StartTimer(unsigned char Num)
{
    if (Num >= NUM_OF_ARTICFITIAL_TIMERS)
        return;
    TimerActiveFlags |= (1 << Num);
    return SUCCESS;
}

/*
@@********************* StopTimer********************************************
 *  Function	     :	StopTimer
 *
 *  Description 	 :	Clears the active flag of timer "Num".
 *
 *  Input parameters : 	Num: the number of the timer to set
 *
 *  Output parameters:
 *
 *  Return      	 : Status
 *
 *  Note         	 : 	Clearing the active flag stops counting on the requested timer
 *
 ******************************************************************************
 */
STATUS StopTimer(unsigned char Num)
{
    if (Num >= NUM_OF_ARTICFITIAL_TIMERS)
        return;
    TimerActiveFlags &= ~(1 << Num);
    return SUCCESS;
}

/*
@@********************* SetTimer********************************************
 *  Function	     :	SetTimer
 *
 *  Description 	 :	Sets the time on timer "Num" but does not start it
 *
 *  Input parameters : 	Num: the number of the timer to set
 *
 *  Output parameters:
 *
 *  Return      	 : Status
 *
 *  Note         	 :
 *
 ******************************************************************************
 */
STATUS SetTimer(unsigned char Num, unsigned int NewTime)
{
    if (Num >= NUM_OF_ARTICFITIAL_TIMERS)
        return;
    Timer_Array[Num] = NewTime;
    return SUCCESS;
}

/*
@@********************* IsTimerActive*****************************************
 *  Function	     :	IsTimerActive
 *
 *  Description 	 :	Gets the status of the active flag of a requested timer
 *
 *  Input parameters : 	Num: the number of the timer to set
 *
 *  Output parameters:
 *
 *  Return      	 : TIMER_ACTIVE if timer is counting
 *  					TIMER_NOT_ACTIVE if timer is not counting
 *
 *  Note         	 :
 *
 ******************************************************************************
 */
char   IsTimerActive(unsigned char Num)
{
    if (Num >= NUM_OF_ARTICFITIAL_TIMERS)
        return;
    if ((TimerActiveFlags & (1 << Num)) != 0) {
        return TIMER_ACTIVE;
    } else {
        return TIMER_NOT_ACTIVE;
    }
}

/*
@@********************* IsTimerExpired*****************************************
 *  Function	     :	IsTimerExpired
 *
 *  Description 	 :	Gets the status of the expired flag of a requested timer
 *
 *  Input parameters : 	Num: the number of the timer to set
 *
 *  Output parameters:
 *
 *  Return      	 : 	TIMER_EXPIRED if timer is done counting
 *  					TIMER_NOT_EXPIRED if timer is not done counting
 *
 *  Note         	 :
 *
 ******************************************************************************
 */
char   IsTimerExpired(unsigned char Num)
{
    if (Num >= NUM_OF_ARTICFITIAL_TIMERS)
        return;
    if ((TimerEventFlags & (1 << Num)) != 0) {
        return TIMER_EXPIRED;
    } else {
        return TIMER_NOT_EXPIRED;
    }
}

/*
@@********************* ClearTimerExpiredFlag************************************
 *  Function	     :	ClearTimerExpiredFlag
 *
 *  Description 	 :	Clears the TimerExpired Flag
 *
 *  Input parameters : 	Num: the number of the timer to clear
 *
 *  Output parameters:
 *
 *  Return      	 : 	none
 *
 *  Note         	 : 	Clearing the flag will return TIMER_NOT_EXPIRED when
 *  					IsTimerExpired is called.
 *
 ******************************************************************************
 */
void   ClearTimerExpiredFlag(unsigned char Num)
{
    if (Num >= NUM_OF_ARTICFITIAL_TIMERS)
        return;
    TimerEventFlags &= ~(1 << Num);
}

/* MODULE INTERNAL FUNCTIONS               *fffffff*/


#pragma vector=TIMERB0_VECTOR
__interrupt void CYC_SYS_TMR_Timer1ISR (void)
{
	//	Reload the Capture Compare Register 0
    TBCCR0 = TBR + gasTimerInfo[TIMER_1].mu16TicksPerInterrupt;

    //	Increment the time stamp by the number of milliseconds that just expired
    spsTimer1Info->mu32TimeStamp += spsTimer1Info->mu32MillisecondsPerInterrupt;

    //Increment and check artificial timers
    char CurTimer = 0;
    if (TimerActiveFlags != 0) {
        for (CurTimer = 0; CurTimer < NUM_OF_ARTICFITIAL_TIMERS; CurTimer++) {
            if ((TimerActiveFlags & (1 << CurTimer)) != 0) {
                if (--Timer_Array[CurTimer] == 0) {
                    TimerEventFlags |= (1 << CurTimer);
                    TimerActiveFlags &= ~(1 << CurTimer);
                }
            }
        }
    }

    //	Decrement the remaining milliseconds counter by the number of milliseconds that just expired
    if (spsTimer1Info->mu16TimerRemainingMilliseconds)
    {
    	//	Decrement the remaining milliseconds counter
    	spsTimer1Info->mu16TimerRemainingMilliseconds -= spsTimer1Info->mu32MillisecondsPerInterrupt;

    	//	If the remaining milliseconds is 0, then call the registered call back function
        if (!spsTimer1Info->mu16TimerRemainingMilliseconds)
        {
        	spsTimer1Info->mpfTimerCallBack();
        }

    }
//    __bic_SR_register_on_exit(LPM0_bits);
}


/*-----------------------------EOF-------------------------------------------*/





    
    

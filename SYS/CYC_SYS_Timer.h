/*
@************************ CYC_SYS_Timer.h ******************************************

$MODULE IDENT		:  	TIMER	$
$DESCRIPTION		: 	This file contains the headers relevant to Timer functions

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
#define		NUMBER_OF_TIMERS				3

#define		TIMER_1							0
#define		TIMER_2							1
#define		TIMER_3							2

#define		REFOCLK_FREQUENCY				32768

#define TIMER_ACTIVE 1
#define TIMER_EXPIRED 1

#define TIMER_NOT_ACTIVE 0
#define TIMER_NOT_EXPIRED 0

/* EXPORTED TYPE DEFINITIONS                *ttttttttt*/
typedef struct
{
    __IO UINT32 mu32TimeStamp;
    UINT32 	mu32MCLKFrequency;
    UINT32 	mu32SMCLKFrequency;
    UINT32 	mu32ACLKFrequency;
    UINT16	mu32MillisecondsPerInterrupt;
    UINT8	mu8Enabled;
    UINT16	mu16TicksPerInterrupt;
    UINT32	mu16TimerRemainingMilliseconds;
    void (*mpfTimerCallBack)(void);
}CYC_SYS_TMR_TimerInfo_t;


/* EXPORTED FUNCTIONS                       *ggggggggg*/
STATUS CYC_SYS_TMR_InitTimer1();

STATUS CYC_SYS_TMR_EnableTimer1();

STATUS CYC_SYS_TMR_DelayInMilliSeconds(UINT32 ru32NumberOfMilliSeconds);

STATUS CYC_SYS_TMR_GetClockMs(UINT32 *rpu32Count);

/*
BEGIN ARTIFICIAL TIMER FUNCTION PROTOTYPES
Artificial timers are non-blocking and use event flags to alert program of timer expirations
*/
STATUS InitTimer(unsigned char Num, unsigned int NewTime);

STATUS StartTimer(unsigned char Num);

STATUS StopTimer(unsigned char Num);

STATUS SetTimer(unsigned char Num, unsigned int NewTime);

char   IsTimerActive(unsigned char Num);

char   IsTimerExpired(unsigned char Num);

void   ClearTimerExpiredFlag(unsigned char Num);
/* EXPORTED DATA DEFINITIONS/DECLARATIONS   ddddddd*/

/*-----------------------------EOF-------------------------------------------*/

/*
 * Event_Handler.c
 *
 *  Created on: Oct 20, 2014
 *      Author: Taylor
 *      Original Credit: Ivan Romero
 */

#include "Event_Handler.h"
#include "..\SYS\msp430_interrupt.h"
#include "..\SYS\CYC_SYS_Timer.h"
#include "..\IO\CYC_IO_KEYS.h"
#include "..\IO\CYC_IO_JSTK.h"
#include <stdint.h>

/* DEFINES*/
#define EVENT_QUEUE_SIZE	20

#define ADDED_TO_QUEUE	1
#define NOT_ADDED		0

/*STRUCTURES, ENUMS, AND TYPEDEFS*/
typedef struct {
	unsigned int queueSize;
	unsigned int currIndex;
	unsigned int numEntries;
	unsigned int entriesProcessed;
	MainEvent_t *array;
} Queue_t;
static Queue_t eventQueue;

/*GLOBAL DATA*/
MainEvent_t eventArray[EVENT_QUEUE_SIZE];
static uint8_t lastButtonStatus;
static int intrruptCount;

/*PRIVATE FUNCTION PROTOTYPES*/

void InitQueue (void);
uint8_t AddEventToQueue (MainEvent_t newEvent);
MainEvent_t GetEventFromQueue (void);
uint8_t IsQueueEmpty (void);
uint8_t isQueueFull (void);

/*PUBLIC FUNCTIONPROTOTYPES*/
void InitEventHandler (void)
{
	InitQueue();
	lastButtonStatus = 31;
}

MainEvent_t RunEventHandler (void)
{
	MainEvent_t returnEvent = NO_EVENT;
	uint8_t currentButtonStatus = 0;


	//BT Receive Message EVENT

	//MPU-9250 Event Handler
	if (GetMPU_9250FlagStatus() == NEW_DATA) {
		ClearMPU_9250InterruptFlag();
		intrruptCount++;
		if (AddEventToQueue(MPU_9250_DATA_READY) != ADDED_TO_QUEUE)
			returnEvent = QUEUE_FULL;

	}
	//Joystick Event Handler
	if (IsTimerExpired(JOYSTICK_SAMPLE_TIMER)) {
		ClearTimerExpiredFlag(JOYSTICK_SAMPLE_TIMER);
		InitTimer(JOYSTICK_SAMPLE_TIMER, TIME_JOYSTICK_SAMPLE);
		if(AddEventToQueue(SAMPLE_TIMER) != ADDED_TO_QUEUE)
			returnEvent =  QUEUE_FULL;

	}
	//Button Event Handler
	currentButtonStatus = ReadAllButtons();
	if (currentButtonStatus != lastButtonStatus) {
		if(AddEventToQueue(BUTTON_PRESSED) != ADDED_TO_QUEUE)
			returnEvent = QUEUE_FULL;
		lastButtonStatus = currentButtonStatus;
	}
	//Send BT Data Event Handler
	if (IsTimerExpired(SEND_BT_TIMER)) {
		ClearTimerExpiredFlag(SEND_BT_TIMER);
		InitTimer(SEND_BT_TIMER, TIME_BT_SEND);
		if(AddEventToQueue(SEND_TIMER) != ADDED_TO_QUEUE)
			returnEvent = QUEUE_FULL;

	}

	returnEvent = GetEventFromQueue();

	return returnEvent;
}

/*PRIVATE FUNCTION IMPLEMENTATIONS*/
void InitQueue (void)
{
	eventQueue.array = eventArray;
	eventQueue.queueSize = EVENT_QUEUE_SIZE;
	eventQueue.currIndex = 0;
	eventQueue.numEntries = 0;
}

uint8_t AddEventToQueue (MainEvent_t newEvent)
{
	if(eventQueue.numEntries < eventQueue.queueSize){// Keeps the event queue from overflowing
		eventQueue.array[((eventQueue.currIndex + eventQueue.numEntries)%
				eventQueue.queueSize)] = newEvent;// Current index does not increment to refer to oldest
	    eventQueue.numEntries++;
	    return ADDED_TO_QUEUE;
	}else {
		return NOT_ADDED;
	}

}

MainEvent_t GetEventFromQueue (void){
    MainEvent_t returnEvent = NO_EVENT;
    if(eventQueue.numEntries > 0){
        returnEvent = eventQueue.array[eventQueue.currIndex]; // Returns the queue at current index
        eventQueue.currIndex++;
        if (eventQueue.currIndex >= eventQueue.queueSize) // Repositions the index to fit size
            eventQueue.currIndex = (eventQueue.currIndex % eventQueue.queueSize);
        eventQueue.numEntries--;
        eventQueue.entriesProcessed++;
    }
    else{
        //dbprintf("Queue is Empty!");
    }
    return returnEvent;
}

uint8_t isQueueEmpty(void){
    return(eventQueue.numEntries == 0);
}

uint8_t isQueueFull (void)
{
	return (eventQueue.numEntries >= eventQueue.queueSize);
}

/*PRIVATE FUNCTIONS*/






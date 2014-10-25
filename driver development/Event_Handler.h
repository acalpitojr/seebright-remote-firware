/*
 * Event_Handler.h
 *
 *  Created on: Oct 20, 2014
 *      Author: Taylor
 */

#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

#define JOYSTICK_SAMPLE_TIMER	0
#define SEND_BT_TIMER			1

#define TIME_JOYSTICK_SAMPLE	500
#define	TIME_BT_SEND			15

/*PUBLIC DATA*/
typedef enum {
	NO_EVENT,
	QUEUE_FULL,
	MPU_9250_DATA_READY,
	BUTTON_PRESSED,
	SAMPLE_TIMER,
	SEND_TIMER,
} MainEvent_t;


/*PUBLIC FUNCTION PROTOTYPES*/

void InitEventHandler (void);

MainEvent_t RunEventHandler (void);


#endif /* EVENT_HANDLER_H_ */

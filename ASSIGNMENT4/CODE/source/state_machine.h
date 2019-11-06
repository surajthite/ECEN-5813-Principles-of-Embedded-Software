/*
 * state_machine.h
 *
 *  Created on: Nov 2, 2019
 *      Author:  SURAJ THITE
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "main.h"
#include "i2c.h"

typedef enum
{
	POST_STATES,
	I2C_READ_TEMPERATURE,
	AVERAGE_WAIT,
	TEMP_ALERT,
	DISCONNECT,
	STATE_MACHINE_SWITCH,
	END
}states;


typedef enum
{
	null_event,
	INIT,
	PASS,
	FAIL,
	ALERT,
	COMPLETE,
	DISCONNECT_EVENT,
	TIME_OUT_1_2_3,
	TIME_OUT_4,
	EXIT
}events;

struct transition
{
	states current_state2;
	events event2;
	states next_state_2;
};



events POST_STATE(void);
events I2C_READ_TEMPERATURE_STATE(void);
events AVERAGE_WAIT_STATE(void);
events TMEP_ALERT_STATE(void);
events DISCONNECTED_STATE(void);
events END_STATE(void);


//current_state = POST_STATES;
void state_machine_1();
void state_machine_2(states current_state2);
states table_tansition( states CR, events EC);
states state_transition__in_table(states,events);


#endif /* STATE_MACHINE_H_ */

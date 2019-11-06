/*
 * state_machine.c
 *
 *  Created on: Nov 2, 2019
 *      Author: SURAJ THITE
 */
#include "state_machine.h"
#include "RGBled.h"

//extern global variables
extern int32_t average_temp;
extern uint32_t total_count;
extern int16_t temp_val;
extern states current_state1 ;
extern events event1;
extern uint8_t _15_seconds_counter;
extern modes a;
extern fnnames fn_name;
extern uint8_t averge_15_wait;
extern uint8_t terminate_flag;
uint8_t averge_15_wait = 0;
int switch1 =0;
extern uint8_t _15seconds_passed ;

////////////////////////////////////////////////////////////////////////////////////STATE MACHINE -1 ///////////////////////////////////////////////////////////////////////////////////////////////
/*******************************************************************************************************
 * Function Name:void state_machine_1()
 * Description :This is switch case event driven state machine.
 * @input: void
 * @Return :void
 *******************************************************************************************************/
void state_machine_1()
{

	fn_name=state_machine1;
	switch(current_state1)
	{
	//POST TESTS
	case POST_STATES:
		if(event1 == INIT )
		{
			Log_String(a,state_machine1,"\n \r <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<STATE MACHINE 1>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
			//printf("\n \r <POST_STATES>"); //Use Log_String("<POST_STATES>");
			if (a==Test || a== Status)
				Log_String(a,fn_name,"\n \r  ********************POST_STATES: Running Power on Startup test ********************");
			else
				Log_String(a,fn_name,"\n \r POST_STATES: LED set to green");
			event1 = null_event;
			current_state1 =I2C_READ_TEMPERATURE;
			POST_TEST_read_bytes(0x90, 0x01);	//Set PASS and Fail Event
		}

		break;
		//READ TEMPERATURE VALUE FROM TMP102 IMPLEMENTING I2C
	case I2C_READ_TEMPERATURE:
		if(event1 == PASS || event1 == TIME_OUT_1_2_3)
		{

			uint8_t status =0;
			status = check_connection(0x90,0x00);
			if(status==1)
			{
				printf("\n \r DISCONNECTED");
				current_state1=DISCONNECT;
				event1 =DISCONNECT_EVENT;
				break;
			}
			led_switch(2);
			event1 = null_event;
			total_count= total_count +1;
			temp_val = i2c_read_temperature(0x90, 0x00);	//Read Current Temperature Value
			if (a==Test || a== Status)
				Log_String(a,fn_name,"\n \r <<<<<<<<<<<<<<<<<<<<<<<<<<<< STATE MACHINE 1 >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> \n \r  ******************** ENTERED <STATE I2C_READ_TEMPERATURE> ********************\n \r  ********************CURRENT TEMP VALUE :");
			else
				Log_String(a,fn_name,"\n \r  ********************ENTERED <STATE I2C_READ_TEMPERATURE>  ******************** \n \r Temp Reading: LED set to green");
			Log_integer(a,temp_val);
			event1 = COMPLETE;	//Set Complete event
			current_state1 =AVERAGE_WAIT;
			if(temp_val<=0)
			{
				event1 = ALERT;
				current_state1 = TEMP_ALERT;	//Over write current_state1 if alert
			}
		}
		break;
		//ALERT STATE
	case TEMP_ALERT:

		if(event1==ALERT)
		{

			uint8_t status =0;
			status = check_connection(0x90,0x00);
			if(status==1)
			{
				printf("\n \r DISCONNECTED");
				current_state1=DISCONNECT;
				event1 =DISCONNECT_EVENT;
				break;
			}
				RGB_OFF();
				led_switch(0);
				//printf(" \n \r <TEMP_ALERT>");
				event1 = null_event;
				if (a==Test || a== Status)
					Log_String(a,fn_name,"\n \r \n  ********************ALERT : TEMPERTURE BELOW 0 DEGREE C  ********************");
				else
					Log_String(a,fn_name,"\n \r Temp Alert: LED set to blue ");
				current_state1 =AVERAGE_WAIT; //Change to AVERAGE_WAIT STATE
				event1 = COMPLETE;	//SET EVENT as complete
		}

		break;
		//CALCULATE AVERAGE and set current state to I2C READ TEMPERATURE OR  STATE MACHINE 2 DEPENDING UPON total_count
	case AVERAGE_WAIT:

		if ( event1 == COMPLETE)
		{
			uint8_t status =0;
			status = check_connection(0x90,0x00);
			if(status==1)
			{
				printf("\n \r DISCONNECTED");
				current_state1=DISCONNECT;
				event1 =DISCONNECT_EVENT;
				break;
			}
			led_switch(2);	//Change LED
			//printf("\n \r ENTERED <AVERAGE WAIT>"); // Log_String("ENTERED <AVERAGE WAIT> ");
			if (a==Test || a== Status)
				Log_String(a,fn_name,"\n \r  ********************ENTERED <AVERAGE WAIT>  ******************** \n \r  ********************AVERAGE TEMPERATURE VALUE FOR ITERATION:");
			else
				Log_String(a,fn_name,"\n \r ENTERED <AVERAGE WAIT> : LED set to green");
			event1 = null_event;
			average_temp = ((average_temp * (total_count-1)) + (int32_t)temp_val)/(total_count); //Calculate average value
			Log_integer(a,total_count);
			Log_integer(a,average_temp);

			if (_15_seconds_counter <4)
			{
				current_state1 =I2C_READ_TEMPERATURE;
				Log_String(a,fn_name," ********************STATE CHANGED TO I2C_READ_TEMPERATURE");
				Log_integer(a,_15_seconds_counter);
			}
			//switch to next state machine if counter value is equal to 4
			else
			{	_15_seconds_counter=0;	//Reinitialize the counter to zero
			current_state1 = STATE_MACHINE_SWITCH;
			}
		}
		break;
		// STATE MACHINE SWITCH STATE
	case STATE_MACHINE_SWITCH:
		if(event1 == TIME_OUT_4)
		{
			event1 = null_event;
			current_state1 = STATE_MACHINE_SWITCH;
			while(1)
			{
				state_machine_2(I2C_READ_TEMPERATURE);	//Handle next state machine
				break;
			}
			event1 = INIT;
		}
		break;
		//DISCONNECT STATE
	case DISCONNECT:
		if (event1==DISCONNECT_EVENT)
		{
			printf(" ********************  DISCONNECTED ********************");
			event1 = null_event;
			led_switch(1);	//Change LED to RED
			current_state1=END;
			event1=EXIT;
		}
		break;
	case END:
		if(event1==EXIT)
		{
			Log_String(a, 1,"END STATE");
			event1 = null_event;
			terminate_flag =1;
		}
	}
}
////////////////////////////////////////////////////////////////////////////////////STATE MACHINE -2 ///////////////////////////////////////////////////////////////////////////////////////////////
//STATE TRANSITION TABLE FOR STATE MACHINE 2
struct transition state_table [] =
{				//CURRENT STATE  -- EVENT --   NEXT STATE//
		{ POST_STATES, PASS,  I2C_READ_TEMPERATURE},
		{ POST_STATES, FAIL,  END},
		{ I2C_READ_TEMPERATURE, COMPLETE,  AVERAGE_WAIT},
		{ I2C_READ_TEMPERATURE, ALERT,  TEMP_ALERT},
		{ I2C_READ_TEMPERATURE, DISCONNECT_EVENT,  DISCONNECT},
		{ AVERAGE_WAIT, TIME_OUT_1_2_3,  I2C_READ_TEMPERATURE},
		{ AVERAGE_WAIT, TIME_OUT_4,  POST_STATES},
		{ AVERAGE_WAIT, DISCONNECT_EVENT,  DISCONNECT},
		{ TEMP_ALERT, DISCONNECT_EVENT,  DISCONNECT},
		{ TEMP_ALERT, COMPLETE,  AVERAGE_WAIT},
		{ DISCONNECT, EXIT,  END},

};

// arrays to pointer to functions
events (*state[])(void)=
{
		POST_STATE,
		I2C_READ_TEMPERATURE_STATE,
		AVERAGE_WAIT_STATE,
		TMEP_ALERT_STATE,
		DISCONNECTED_STATE,
		END_STATE
};

/*******************************************************************************************************
 * Function Name:void state_machine_2()
 * Description :This is a table driven state machine.
 * @input: CURRENT STATE
 * @Return :void
 *******************************************************************************************************/


void state_machine_2(states current_state2)
{
	Log_String(a,state_machine2,"\n \r <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<STATE MACHINE 2>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
	events (* state_function_ptr)(void);
	//state current_state = Temp_Reading;
	events event_code;

	while(current_state1 != I2C_READ_TEMPERATURE )	//  Run Loop until current_state 1 is set to POST_STATES
	{
		state_function_ptr = state[current_state2];	// Store the function pointer  from the array
		event_code = state_function_ptr();  // Execute function and store returned event
		current_state2 = state_transition__in_table(current_state2, event_code); //switch to next state depending upon the state table

	}
	current_state1 = I2C_READ_TEMPERATURE; //CURRENT STATE = POST_STATES
	event1 = PASS;
}

/*******************************************************************************************************
 * Function Name:state_transition__in_table( states CR, events EC)
 * Description :This function looks for state and events in the state table
 * @input: state and returned event
 * @Return :void
 *******************************************************************************************************/
states state_transition__in_table( states CR, events EC)
{
	uint16_t max = 0;
	states next_State_TB;
	max = sizeof(state_table) / sizeof(state_table[0]);
	for(int i = 0; i < max ; i++)
	{

		if ((state_table[i].current_state2 == CR) && (state_table[i].event2 == EC))	//Value found
		{
			next_State_TB = state_table[i].next_state_2;
			break;
		}
	}

	return next_State_TB;
}

/*******************************************************************************************************
 * Function Name:events POST_STATE(void)
 * Description :This is the state function for POST TESTS
 * @input: CURRENT STATE
 * @Return :events
 *******************************************************************************************************/

events POST_STATE(void)
{
	fn_name =POSTSTATE;
	if (a==Test || a== Status)
		Log_String(a,POSTSTATE,"\n \r ********************POST_STATES: Running Power on Startup test");
	else
		Log_String(a,POSTSTATE,"\n \r POST_STATES: LED set to green");
	POST_TEST_read_bytes(0x90, 0x01);	//RUN POST
	return PASS;
}

/*******************************************************************************************************
 * Function Name:events I2C_READ_TEMPERATURE_STATE(void)
 * Description :This is the READS the TEMPERATURE and returns the events
 * @input: void
 * @Return :ALERT if Temperature is  less than zero else complete
 *******************************************************************************************************/
events I2C_READ_TEMPERATURE_STATE(void)
{
	//fn_name =I2C_READ_TEMPERATURESTATE;
	//current_state1 = AVERAGE_WAIT;

	uint8_t status =0;
	status = check_connection(0x90,0x00);
	if(status==1)
	{
		printf("\n \r DISCONNECTED");
		return DISCONNECT_EVENT;
	}
	led_switch(2);
	total_count= total_count +1;
	temp_val = i2c_read_temperature(0x90, 0x00); //REad temperature values and store it in a temporary variable
	if (a==Test || a== Status)
		Log_String(a,I2C_READ_TEMPERATURESTATE,"\n \r ENTERED <STATE I2C_READ_TEMPERATURE> \n \r ********************CURRENT TEMP VALUE :");
	else
		Log_String(a,I2C_READ_TEMPERATURESTATE,"\n \r Temp Reading: LED set to green");
	//Log_String(a,fn_name,"\n \r ENTERED <STATE I2C_READ_TEMPERATURE>:");

	//Log_String(a,fn_name,"CURRENT TEMP VALUE :");
	Log_integer(a,temp_val);
	if(temp_val <=0)	//CHECK FOR ALTERT EVENT
		return ALERT;
	else
		return COMPLETE;	//Else change it to COMPLETE state
}

/*******************************************************************************************************
 * Function Name:events AVERAGE_WAIT_STATE(void)
 * Description :This function calculates average and waits for 15 seconds to pass thus returning the events.
 * @input: void
 * @Return :TIMEOUT1_2_3 if counter value is less than 4.
 *******************************************************************************************************/

events AVERAGE_WAIT_STATE(void)
{
	uint8_t status =0;
	status = check_connection(0x90,0x00);
	if(status==1)
	{
		printf("\n \r DISCONNECTED");
		return DISCONNECT_EVENT;
	}
	led_switch(2);
	fn_name =AVERAGE_WAITSTATE;
	average_temp = ((average_temp * (total_count-1)) + (int32_t)temp_val)/(total_count);
	//printf("\n \r>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> Entered Average State");
	if (a==Test || a== Status)
		Log_String(a,AVERAGE_WAITSTATE,"ENTERED <AVERAGE WAIT> \n \r ********************AVERAGE TEMPERATURE VALUE FOR ITERATION:");
	else
		Log_String(a,AVERAGE_WAITSTATE,"\n \r Average Wait: LED set to green");
	Log_integer(a,total_count);
	Log_integer(a,average_temp);
	int current_cnt_temp = _15_seconds_counter;	//Store current count in temporary variable
	while(1)
	{
		if(current_cnt_temp != _15_seconds_counter)	//Wait for Systick timer to timeout
		{
			break;
		}
	}

	if (_15_seconds_counter <3)
		return TIME_OUT_1_2_3;
	else if (_15_seconds_counter ==3)
	{
		_15_seconds_counter =0;
		current_state1 = I2C_READ_TEMPERATURE;
		event1 = PASS;
	}
}

/*******************************************************************************************************
 * Function Name:events TMEP_ALERT_STATE(void)
 * Description :This function handles the temperature alert state
 * @input: void
 * @Return :COMPLETE event
 *******************************************************************************************************/
events TMEP_ALERT_STATE(void)
{

	uint8_t status;
	status = check_connection(0x90,0x00);
	if(status==1)
	{
		printf("\n \r DISCONNECTED");
		return DISCONNECT_EVENT;
	}
	RGB_OFF();
	led_switch(0);
	fn_name =TMEP_ALERTSTATE;
	if (a==Test || a== Status)
		Log_String(a,TMEP_ALERTSTATE,"\n \r \n ********************ALERT : TEMPERTURE BELOW 0 DEGREE C********************");
	return COMPLETE;

}

/*******************************************************************************************************
 * Function Name:events DISCONNECTED_STATE(void)
 * Description :This function handles the disconnection state.
 * @input: void
 * @Return :EXIT EVENT
 *******************************************************************************************************/
events DISCONNECTED_STATE(void)
{
	led_switch(1);
	fn_name=DISCONNECTEDSTATE;
	if (a==Test || a== Status)
		Log_String(a,DISCONNECTEDSTATE,"\n \r \n ******************** Disconnected State ***********************");
	else
		Log_String(a,DISCONNECTEDSTATE,"\n \r Disconnected: LED set to Red ");
	return EXIT;
}
/*******************************************************************************************************
 * Function Name:events END_STATE(void)
 * Description :This function terminates the program upon disconnection
 * @input: void
 * @Return :void
 *******************************************************************************************************/

events END_STATE(void)
{
	printf("\n \r ******************** END STATE ********************");
	terminate_flag =1;
}

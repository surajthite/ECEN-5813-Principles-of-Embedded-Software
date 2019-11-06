/*
 * i2c_interrupt.c
 *
 *  Created on: Oct 29, 2019
 *      Author: SURAJ THITE
 *
 */


#include "i2c.h"
#include "logger.h"

extern events event1;
extern states current_state1;
extern int _15seconds_counter;
extern uint8_t averge_15_wait;

#define I2C_M_START  	I2C0->C1 |= I2C_C1_MST_MASK
#define I2C_M_STOP    	I2C0->C1 &= ~I2C_C1_MST_MASK
#define I2C_M_RESTART	I2C0->C1 |= I2C_C1_RSTA_MASK


#define I2C_TRANS		I2C0-> C1 |= I2C_C1_TX_MASK
#define I2C_REC 		I2C0-> C1 &= ~I2C_C1_TX_MASK

#define I2C_WAIT 	    while((I2C0->S & I2C_S_IICIF_MASK) ==0)	{} \
		I2C0->S |= I2C_S_IICIF_MASK;

#define ACK I2C0->C1 &= ~I2C_C1_TXAK_MASK
#define NACK I2C0->C1 |= I2C_C1_TXAK_MASK



#define POST_CONFIG_REGISTER_VALUE0 96

#define POST_CONFIG_REGISTER_VALUE1 160


const uint8_t TMP102_addr = 0x90U; //TMP102 Address

bool Negative_Temp_Alert;	//Flag for negative temperature alert
uint8_t _15_seconds_counter;	//Flag for 15 seconds counter
bool mutex;
extern modes a;
extern fnnames fn_name;

uint8_t _15seconds_passed =0;
/*******************************************************************************************************
 * Function Name:void i2c_init(void)
 * Description :This Function Initializes the I2C bus
 * @input: void
 * @Return : Void
 *******************************************************************************************************/
void i2c_init(void)
{

	//ENable Clock Gating
	SIM->SCGC4 |= SIM_SCGC4_I2C0_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;

	//Set Pins for I2C functionality
	PORTC->PCR[8] |=  PORT_PCR_MUX(2);
	PORTC->PCR[9] |=  PORT_PCR_MUX(2);


	//Frequency Divider
	I2C0->F = I2C_F_ICR(0x11) | I2C_F_MULT(0);
	I2C0->C1 |= I2C_C1_IICEN_MASK;

	//Select High Drive Mode by setting HDRS bit in Control Register 2
	I2C0->C2 |= (I2C_C2_HDRS_MASK);

}

/*******************************************************************************************************
 * Function Name:void i2c_write(uint8_t addr, uint8_t reg,uint8_t data)
 * Description :This function writes data to the register pointed by addr address
 * @input: device address, register address, data
 * @Return : Void
 *******************************************************************************************************/

void i2c_write(uint8_t addr, uint8_t reg,uint8_t data)
{
	//Start transmission
	I2C_TRANS;
	I2C_M_START;

	//Send the device address to the i2c bus
	I2C0->D = addr;

	//wait for ack from slave
	I2C_WAIT

	//Write register address to i2c bus
	I2C0->D =reg;
	I2C_WAIT

	//Write data to the i2c bus
	I2C0->D = data;
	I2C_WAIT

	//Stop transaction
	I2C_M_STOP;
}

/*******************************************************************************************************
 * Function Name:int16_t i2c_read_temperature(uint8_t dev, uint8_t reg)
 * Description :This function returns the temperature value recieved from TMP102 module via I2C Transactions
 * @input: device address , register address
 * @Return : Void
 *******************************************************************************************************/
int16_t i2c_read_temperature(uint8_t dev, uint8_t reg)
{
	fn_name = i2creadtemperature;
	int16_t tempc;
	uint8_t data[2];

	//Start I2C write
	I2C_TRANS;
	I2C_M_START;
	I2C0->D = dev;
	i2c_dealy1();

	I2C0->D =reg;
	i2c_dealy1();

	I2C_M_RESTART;
	I2C0->D =(dev |0x01);
	i2c_dealy1();

	//Start I2C read
	I2C_REC;
	ACK;

	data[0]=I2C0->D; //Store data in a variable
	i2c_dealy1();

	data[0]=I2C0->D;
	i2c_dealy1();	//Dummy read

	NACK;

	data[1] = I2C0->D;	//store data in a uint8 variable
	i2c_dealy1();

	//IF MSB is SET the negative value and set ALert flag
	if ((data[0] >>7 ) ==1)
	{
		Negative_Temp_Alert =1;
	}

	//Stop transaction
	I2C_M_STOP;
	//printf("/n /r %d ......%d",data[0],data[1]);


	data[1] = data[1] >> 4; // Right shift by 4 bits

	tempc = ((data[0] << 4) | data[1]);	//Store the result in a temporary variable
	event1 = COMPLETE;	//set read complete event

	//Return Negtive temperature value
	if(Negative_Temp_Alert)
	{
		Negative_Temp_Alert =0;
		return ((257-(tempc*0.0625))*(-1));

	}

	//Return Positive temperature value
	return (tempc*0.0625);
}
/*******************************************************************************************************
 * Function Name:Init_SysTick(void)
 * Description :This function Initializes the SysTick Timer for 15 seconds interrupts.
 * @input: void
 * @Return : Void
 *******************************************************************************************************/
void Init_SysTick(void)
{
	SysTick->LOAD = (48000000L/5);
	NVIC_SetPriority(SysTick_IRQn,3);		//Enable NVIC Interrupt with priority 3
	SysTick->VAL=0;
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;	//Enable interrupt
}

/*******************************************************************************************************
 * Function Name:void POST_TEST_read_bytes(uint8_t dev, uint8_t reg)
 * Description :This function RUNS POST TESTS by reading value in the CONFIGURATION REGISTER VALUES
 * @input: device address,register address
 * @Return : Void
 *******************************************************************************************************/
void POST_TEST_read_bytes(uint8_t dev, uint8_t reg)
{

	fn_name = POST_TESTread_bytes;
	uint8_t data[2];
	if(a!=Debug)
		Log_String(a,fn_name,"POST-----");

	I2C_TRANS;

	I2C_M_START;

	I2C0->D = dev;

	i2c_dealy1();

	I2C0->D =reg;

	i2c_dealy1();

	I2C_M_RESTART;

	I2C0->D =(dev |0x01);

	i2c_dealy1();

	I2C_REC;
	ACK;

	data[0]=I2C0->D;
	i2c_dealy1();

	data[0]=I2C0->D;
	i2c_dealy1();

	NACK;

	data[1] = I2C0->D;
	i2c_dealy1();

	I2C_M_STOP;

	if(data[0]==POST_CONFIG_REGISTER_VALUE0 && data[1] ==POST_CONFIG_REGISTER_VALUE1)  // Check for POST Default values in the config register
	{
		if(a!=Debug)
		{
			Log_String(a,fn_name,"POST SUCCESSFULL ------POST CONFIG REGISTER VALUES---C0 --- C1 are: ");
			Log_integer(a, data[0]);	//Print Config register values
			Log_integer(a, data[1]);	//Print COnfig register value
		}
		else
			Log_String(1,fn_name,"POST PASS : LED set to green");
		if (event1 != TIME_OUT_4)
			event1=PASS;	//Set event to PASS

	}
	else
	{
		Log_String(a,fn_name,"POST FAILED");
		current_state1 = END;	//Set state to END
		if (event1 != TIME_OUT_4)
			event1=FAIL;	//  event to fail
		else
			return FAIL;
	}
}

/*******************************************************************************************************
 * Function Name:uint8_t check_connection(uint8_t dev, uint8_t reg)
 * Description :This function checks whether TMP102 device is active on I2C bus and returns connection status
 * @input: device address,register address
 * @Return : Connection Status
 *******************************************************************************************************/

uint8_t check_connection(uint8_t dev, uint8_t reg)
{

	//int16_t tempc;
	uint8_t data[2];
	//bool disconnect_flag;
	uint8_t temp;
	uint8_t total=0;
	//Start I2C write
	I2C_TRANS;
	I2C_M_START;
	I2C0->D = dev;

	temp = i2c_dealy1();
	if (temp==1)
	total = total + temp;
	I2C0->D =reg;

	temp = i2c_dealy1();
	total = total + temp;

	I2C_M_RESTART;
	I2C0->D =(dev |0x01);

	temp = i2c_dealy1();
	total = total + temp;

	//Start I2C read
	I2C_REC;
	ACK;

	data[0]=I2C0->D; //Store data in a variable

	temp = i2c_dealy1();
	total = total + temp;

	data[0]=I2C0->D;

	temp = i2c_dealy1();
	total = total + temp;

	NACK;

	data[1] = I2C0->D;

	temp = i2c_dealy1();
	total = total + temp;

	I2C_M_STOP;
	printf("\n \r ************CONNECTION HEALTH*********: %d",total);
	if (total >1)
	{
		return 1;
	}
	else return 0;
}


/*******************************************************************************************************
 * Function Name:void SysTick_Handler()
 * Description :This function is the IRQ Handler
 * This function generates event for TIMEOUT_1_2_3 and TIMEOUT4 for changing states to READ TEMPERATURE AND
 * SWITCH STATE MACHINE
 * @input: void
 * @Return : void
 *******************************************************************************************************/
//Event handler for SystickTimer for 15 seconds delay
void SysTick_Handler()
{
	_15seconds_passed = _15seconds_passed +1;
	fn_name = SysTickHandler;
	_15_seconds_counter = _15_seconds_counter +1 ;
	if (_15_seconds_counter < 4)
	{
		event1 =TIME_OUT_1_2_3;
	}
	else
	{
		event1 = TIME_OUT_4;
		current_state1=STATE_MACHINE_SWITCH;
		_15_seconds_counter =0;
	}
	//reset in else condition for second state machine
}

/*******************************************************************************************************
 * Function Name:uint16_t CONFIG_REGISTER_VALUE()
 * Description :This function returns current config register value
 * @input: void
 * @Return : void
 *******************************************************************************************************/
uint16_t CONFIG_REGISTER_VALUE()
{
	uint8_t dev =0x90;
	uint8_t reg =0x01;
	uint8_t data[2];
	uint16_t temp;
	I2C_TRANS;
	I2C_M_START;
	I2C0->D = dev;
	I2C_WAIT;

	I2C0->D =reg;
	I2C_WAIT;

	I2C_M_RESTART;
	I2C0->D =(dev |0x01);
	I2C_WAIT;

	I2C_REC;
	ACK;

	data[0]=I2C0->D;
	I2C_WAIT;

	data[0]=I2C0->D;
	I2C_WAIT;

	NACK;

	data[1] = I2C0->D;
	I2C_WAIT;

	I2C_M_STOP;

	temp = (data[0]*256 + data[1]);

	return temp;
}

/*******************************************************************************************************
 * Function Name:uint8_t i2c_dealy1()
 * Description :This function returns the connection status of the i2c connection
 * @input: void
 * @Return : connection status
 *******************************************************************************************************/
uint8_t i2c_dealy1()
{
	uint16_t temp=0;
	while((I2C0->S & I2C_S_IICIF_MASK) ==0)
	{
		temp++;
		if(temp > 250 )
		{
			break;

		}

	}
	I2C0->S = I2C0->S | I2C_S_IICIF_MASK;
	if(temp>250)
	{
		//printf("\n \r CONNECTION FAILED : %d",temp);
		return 1;
	}
	else
	{
		//printf("\n \r CONNECTION PASSED :%d",temp);
		return 0;

	}
}

#ifndef LOGGER_H_
#define LOGGER_H_

///////////////ENUM for test, debug and status///////////////////
typedef enum
{
	Test,
	Debug,
	Status
}modes ;


/////////////////////////////////////////////////////////////

typedef enum
{
	state_machine1,
	i2cwrite,
	i2creadtemperature,
	POST_TESTread_bytes,
	checkconnection,
	SysTickHandler,
	InitSystick,
	state_machine2,
	state_transition__intable,
	POSTSTATE,
	I2C_READ_TEMPERATURESTATE,
	AVERAGE_WAITSTATE,
	TMEP_ALERTSTATE,
	DISCONNECTEDSTATE,
	ENDSTATE

}fnnames;

void Log_enable();
void Log_disable();
uint8_t Log_status();
void Log_data (uint32_t *, uint32_t );
void Log_String(uint8_t ,uint8_t, char *);
void Log_integer(uint8_t ,int16_t);
uint8_t Log_level();

#endif

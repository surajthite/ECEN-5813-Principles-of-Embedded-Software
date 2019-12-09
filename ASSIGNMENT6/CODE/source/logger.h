#ifndef LOGGER_H_
#define LOGGER_H_

///////////////ENUM for test, debug and status///////////////////
typedef enum
{
	Test,
	Debug,
	Normal
}modes;


/////////////////////////////////////////////////////////////

typedef enum
{
	dactask,
	adctask,
	startdsp,
	dmacallback,
	Main

}fnnames;

void Log_enable();
void Log_disable();
uint8_t Log_status();
void Log_data (uint32_t *, uint32_t );
void Log_String(uint8_t ,uint8_t,char *str);
void Log_integer(uint8_t ,int16_t);
uint8_t Log_level();

#endif



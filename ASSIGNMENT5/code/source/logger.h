#ifndef LOGGER_H_
#define LOGGER_H_

///////////////ENUM for test, debug and status///////////////////
typedef enum
{
	Test,
	Debug,
	Normal
}modes ;


/////////////////////////////////////////////////////////////

typedef enum
{
	cbuffinit,
	cbuffcheck_full,
	cbuffisempty,
	cbuffadd,
	cbuffdelete,
	verifyinit,
	verifyptr,
	cbuffresize,
	cbuffprint,
	InitUART0,
	Uartrx,
	Uarttx,
	Transmitwait,
	Recievewait,
	UART0printstring,
	UART0print_int,
	putchcbuff,
	UART0IRQHandler,
	cbuffstring,
	Getinfo,
	charactercount,
	Application_poll,
	Application_int,
	Echo_function_poll,
	Echo_function_interrupt,
	Generate_report,
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

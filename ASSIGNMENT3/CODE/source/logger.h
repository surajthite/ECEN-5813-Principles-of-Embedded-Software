#ifndef LOGGER_H_
#define LOGGER_H_

void Log_enable();
void Log_disable();
uint8_t Log_status();
void Log_data (uint32_t *, uint32_t );
void Log_string(char* str);
void Log_integer(uint32_t);

#endif

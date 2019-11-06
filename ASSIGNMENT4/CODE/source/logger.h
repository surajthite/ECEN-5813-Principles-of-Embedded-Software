#ifndef LOGGER_H_
#define LOGGER_H_

void Log_enable();
void Log_disable();
uint8_t Log_status();
void Log_data (uint32_t *, uint32_t );
void Log_String(uint8_t ,uint8_t, char *);
void Log_integer(uint8_t ,int16_t);
uint8_t Log_level();

#endif

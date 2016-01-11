#include "settime.h"
//Standard C
#include <string.h>
//ASF
//Custom
#include "modules/serial.h"
#include "modules/datetime.h"

void serial_handler_settime(char identifier, char type, char* body, int body_length)
{
	uint32_t millis = 0;
	memcpy(&millis, body, sizeof(uint32_t));
	datetime_set_time(millis);
	serial_send_packet(identifier, type, NULL, 0);
}
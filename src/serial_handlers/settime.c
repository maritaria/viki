#include "settime.h"
//Standard C
#include <string.h>
//ASF
//Custom
#include "modules/serial.h"
#include "modules/datetime.h"

void serial_handler_settime(char identifier, char type, char* body, int body_length)
{
	char response[1] = {0};
	uint64_t millis = 0;
	if (body_length == sizeof(millis))
	{
		memcpy(&millis, body, sizeof(millis));
		datetime_set_time(millis);
		response[0] = 1;
	}
	else
	{
		response[0] = 0;
	}
	serial_send_packet(identifier, type, response, 1);
}
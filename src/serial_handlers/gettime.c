#include "gettime.h"
//Standard C
#include <string.h>
//ASF
//Custom
#include "modules/serial.h"
#include "modules/datetime.h"

void serial_handler_gettime(char identifier, char type, char* body, int body_length)
{
	uint64_t millis = datetime_get_milliseconds();
	char responseBody[sizeof(millis)] = {0};
	memcpy(responseBody, &millis, sizeof(millis));
	serial_send_packet(identifier, type, responseBody, sizeof(millis));
}
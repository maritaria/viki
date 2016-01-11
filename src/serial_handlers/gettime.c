#include "gettime.h"
//Standard C
#include <string.h>
//ASF
//Custom
#include "modules/serial.h"
#include "modules/datetime.h"

void serial_handler_gettime(char identifier, char type, char* body, int body_length)
{
	char responseBody[4] = {0};
	uint32_t millis = datetime_get_milliseconds();
	
	memcpy(responseBody, &millis, sizeof(uint32_t));
	
	serial_send_packet(identifier, type, responseBody, 4);
}
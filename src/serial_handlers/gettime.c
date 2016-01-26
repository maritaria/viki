#include "handlers.h"
//Standard C
#include <string.h>
//ASF
//Custom
#include "modules/datetime.h"

//Writes a packet when requesting the time of the system
void serial_handler_gettime(serial_args_t args)
{
	uint64_t millis = datetime_get_milliseconds();
	char responseBody[sizeof(millis)] = {0};
	memcpy(responseBody, &millis, sizeof(millis));
	serial_send_packet(args.identifier, args.type, responseBody, sizeof(millis));
}
#include "handlers.h"
//Standard C
#include <string.h>
//ASF
//Custom
#include "modules/datetime.h"

void serial_handler_settime(serial_args_t args)
{
	char response[1] = {0};
	uint64_t millis = 0;
	if (args.body_length == sizeof(millis))
	{
		memcpy(&millis, args.body, sizeof(millis));
		datetime_set_time(millis);
		response[0] = 1;
	}
	else
	{
		response[0] = 0;
	}
	serial_send_packet(args.identifier, args.type, response, 1);
}
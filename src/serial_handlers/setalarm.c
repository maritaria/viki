#include "handlers.h"
//Standard C
#include <string.h>
//ASF
//Custom
#include "modules/config.h"
#include "modules/timeswitches.h"

void serial_handler_setalarm(serial_args_t args)
{
	if (args.body_length != 1)
	{
		serial_send_quick_response(args.identifier, args.type, 0);
		return;
	}
	char alarmIndex = args.body[0];
	if (alarmIndex > 4)
	{
		serial_send_quick_response(args.identifier, args.type, 0);
		return;
	}
	char responseBody[sizeof(timeswitch_config_t)] = {0};
	memcpy(responseBody, &CONFIG.timers[alarmIndex], sizeof(timeswitch_config_t));
	serial_send_packet(args.identifier, args.type, responseBody, sizeof(timeswitch_config_t));
}
#include "handlers.h"
//Standard C
#include <string.h>
//ASF
//Custom
#include "modules/config.h"
#include "modules/timeswitches.h"

void serial_handler_getalarm(serial_args_t args)
{
	if (args.body_length != 1)
	{
		serial_send_failure_response(args.identifier, args.type);
		return;
	}
	char alarmIndex = args.body[0];
	if (alarmIndex > 4)
	{
		serial_send_failure_response(args.identifier, args.type);
		return;
	}
	
	timeswitch_config_t* timeswitch = &CONFIG.timers[alarmIndex];
	char packet[19] = {0};
	char* packet_pointer = packet;
	packet[0] = alarmIndex;
	packet[1] = timeswitch->enabled;
	packet[2] = timeswitch->behaviour;
	memcpy(&timeswitch->output, packet_pointer + 3, sizeof(uint16_t));
	memcpy(&timeswitch->repeat_count, packet_pointer + 5, sizeof(uint16_t));
	memcpy(&timeswitch->repeat_interval, packet_pointer + 7, sizeof(uint32_t));
	memcpy(&timeswitch->timestamp, packet_pointer + 11, sizeof(uint64_t));
	
	serial_send_packet(args.identifier, args.type, packet, 19);
}
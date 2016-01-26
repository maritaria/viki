#include "handlers.h"
//Standard C
//ASF
//Custom

void serial_handler_echo(serial_args_t args)
{
	//Send the packet back exactly
	serial_send_packet(args.identifier, args.type, args.body, args.body_length);
}
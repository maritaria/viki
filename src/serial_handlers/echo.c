#include "echo.h"
//Standard C
//ASF
//Custom
#include "modules/serial.h"

void serial_handler_echo(char identifier, char type, char* body, int body_length)
{
	serial_send_packet(identifier, type, body, body_length);
}
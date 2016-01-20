#ifndef MODULES__SERIAL_H_
#define MODULES__SERIAL_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"

bool serial_init(void);
bool serial_cdc_enable(uint8_t port);
void serial_cdc_disable(uint8_t port);
void serial_cdc_rx_notify(uint8_t port);
char serial_calculate_checksum(char* body, int body_length);
void serial_cdc_dtr_changed(uint8_t port, bool enabled);
void serial_send_packet(char identifier, char type, char* body, int body_length);
void serial_send_quick_response(char identifier, char type, char value);
void serial_send_failure_response(char identifier, char type);

DEFINE_TYPE(enum, packet_type_t)
{
	unknown = 0x00,
	echo = 0x01,
	get_time = 0x02,
	set_time = 0x03,
	get_alarm = 0x04,
	set_alarm = 0x05,
};

DEFINE_TYPE(struct, serial_args_t)
{
	char identifier;
	packet_type_t type;
	char* body;
	char body_length;
};

#endif /* MODULES__SERIAL_H_ */
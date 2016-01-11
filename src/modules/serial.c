#include "modules/serial.h"
//C standard library
#include <string.h>
//ASF
//Modules
#include "modules/config.h"
#include "serial_handlers/echo.h"

bool serial_init(void)
{
	udc_start();
	return true;
}

bool serial_cdc_enable(uint8_t port)
{
	//Communication has opened
	LED_On(LED0);
	return true;//Allow
}

void serial_cdc_disable(uint8_t port)
{
	//Communication has closed
	LED_Off(LED0);
}

#define PACKET_MAX_BODY_SIZE (255)
#define PACKET_HEADER (0x2F)

#define STATE_IDLE (0)
#define STATE_IDENTIFIER (1)
#define STATE_TYPE (2)
#define STATE_LENGTH (3)
#define STATE_BODY (4)
#define STATE_CHECKSUM (5)

char packet_body[PACKET_MAX_BODY_SIZE] = {0};
char packet_identifier = 0;
int packet_body_index = 0;
int packet_state = STATE_IDLE;
char packet_body_length = 0;
char packet_checksum = 0;
char packet_type = 0;

void serial_enter_idle_state();
void serial_handle(char incomming);
void serial_handle_idle(char incomming);
void serial_enter_identifier_state();
void serial_handle_identifier(char incomming);
void serial_enter_type_state();
void serial_handle_type(char incomming);
void serial_enter_length_state();
void serial_handle_length(char incomming);
void serial_enter_body_state();
void serial_handle_body(char incomming);
void serial_append_to_body(char data);
void serial_check_body_state_end();
void serial_enter_checksum_state();
void serial_handle_checksum(char incomming);
void serial_finish_packet();
void serial_try_handle_packet();
bool serial_is_packet_valid();
bool serial_is_checksum_valid();
void serial_handle_packet();

void serial_cdc_rx_notify(uint8_t port)
{
	while(udi_cdc_is_rx_ready())
	{
		char incomming = (char)udi_cdc_getc();
		serial_handle(incomming);
	}
}

void serial_cdc_dtr_changed(uint8_t port, bool comEnabled)
{
	if (comEnabled)
	{
		LED_On(LED1);
		CONFIG.com_enabled = true;
	}
	else
	{
		LED_Off(LED1);
		CONFIG.com_enabled = false;
	}
}

void serial_send_packet(char identifier, char type, char* body, int body_length)
{
	udi_cdc_putc(PACKET_HEADER);
	udi_cdc_putc(identifier);
	udi_cdc_putc(type);
	udi_cdc_putc(body_length);
	for(int i = 0; i < body_length;i++)
	{
		udi_cdc_putc(body[i]);
	}
	char checksum = serial_calculate_checksum(body, body_length);
	udi_cdc_putc(checksum);
}


void serial_enter_idle_state()
{
	packet_state = STATE_IDLE;
}

void serial_handle(char incomming)
{
	switch(packet_state)
	{
		case STATE_IDLE: serial_handle_idle(incomming); break;
		case STATE_IDENTIFIER: serial_handle_identifier(incomming); break;
		case STATE_TYPE: serial_handle_type(incomming); break;
		case STATE_LENGTH: serial_handle_length(incomming); break;
		case STATE_BODY: serial_handle_body(incomming); break;
		case STATE_CHECKSUM: serial_handle_checksum(incomming); break;
	}
}

void serial_handle_idle(char incomming)
{
	if (incomming == PACKET_HEADER)
	{
		serial_enter_identifier_state();
	}
}

void serial_enter_identifier_state()
{
	packet_state = STATE_IDENTIFIER;
}

void serial_handle_identifier(char incomming)
{
	packet_body_length = incomming;
	serial_enter_type_state();
}


void serial_enter_type_state()
{
	packet_state = STATE_TYPE;
}

void serial_handle_type(char incomming)
{
	packet_type = incomming;
	serial_enter_length_state();
}

void serial_enter_length_state()
{
	packet_state = STATE_LENGTH;
}

void serial_handle_length(char incomming)
{
	packet_body_length = incomming;
	serial_enter_body_state();
}

void serial_enter_body_state()
{
	packet_state = STATE_BODY;
	memset(packet_body, 0, sizeof(packet_body));
	packet_body_index = 0;
	serial_check_body_state_end();
}

void serial_handle_body(char incomming)
{
	serial_append_to_body(incomming);
	serial_check_body_state_end();
}

void serial_append_to_body(char data)
{
	packet_body[packet_body_index++] = data;
}

void serial_check_body_state_end()
{
	if (packet_body_index >= packet_body_length)
	{
		serial_enter_checksum_state();
	}
}

void serial_enter_checksum_state()
{
	packet_state = STATE_CHECKSUM;
}

void serial_handle_checksum(char incomming)
{
	packet_checksum = incomming;
	serial_finish_packet();
}

void serial_finish_packet()
{
	serial_try_handle_packet();
	serial_enter_idle_state();
}

void serial_try_handle_packet()
{
	if (serial_is_packet_valid())
	{
		serial_handle_packet();
	}
}

bool serial_is_packet_valid()
{
	return serial_is_checksum_valid();
}

bool serial_is_checksum_valid()
{
	return serial_calculate_checksum(packet_body, packet_body_length) == packet_checksum;
}

char serial_calculate_checksum(char* body, int body_length)
{
	char answer = 0x00;
	for(int i = 0; i < body_length;i++)
	{
		answer ^= body[i];
	}
	return answer;
}

void serial_handle_packet()
{
	serial_handler_echo(packet_identifier, packet_type, packet_body, packet_body_index);
}

/*
 * module_serial.c
 *
 * Created: 1-9-2015 11:01:40
 *  Author: Eigenaar
 */

#include <string.h>

#include "modules/serial.h"
#include "modules/config.h"
#include "modules/display.h"

bool serial_init(void)
{
	udc_start();
	return true;
}

bool serial_cdc_enable(uint8_t port)
{
	//Communication has opened
	LED_On(LED0);
	display_clear();
	display_print("USB Ready");
	return true;//Allow
}

void serial_cdc_disable(uint8_t port)
{
	//Communication has closed
	LED_Off(LED0);
}

#define SERIAL_SCREEN_BUFFER (40)
char buffer[SERIAL_SCREEN_BUFFER] = { ' ' };
int buffer_index = 0;
void serial_cdc_rx_notify(uint8_t port)
{
	display_clear();
	display_print("Received:\t");
	while(udi_cdc_is_rx_ready())
	{
		buffer[buffer_index++] = (char)udi_cdc_getc();
		if (buffer_index >= SERIAL_SCREEN_BUFFER)
		{
			buffer_index = 0;
		}
	}
	display_printf(5 + SERIAL_SCREEN_BUFFER, "USB:\n%s", buffer);
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
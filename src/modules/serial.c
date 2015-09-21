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

result serial_init(void)
{
	irq_initialize_vectors();
	cpu_irq_enable();
	sleepmgr_init();
	sysclk_init();
	udc_start();
	return success;
}

bool serial_cdc_enable(uint8_t port)
{
	//Communication has opened
	LED_On(LED0);
	display_clear();
	display_write("USB Ready");
	//Allow
	return true;
}

void serial_cdc_disable(uint8_t port)
{
	//Communication has closed
	LED_Off(LED0);
}
int buffer_size = 40;
char buffer[40] = { ' ' };
int buffer_index = 0;
void serial_cdc_rx_notify(uint8_t port)
{
	display_clear();
	display_write("Received:\t");
	while(udi_cdc_is_rx_ready())
	{
		buffer[buffer_index++] = (char)udi_cdc_getc();
		if (buffer_index >= buffer_size - 1)
		{
			buffer_index = 0;
		}
		buffer[buffer_size] = '\0';
	}
	display_write(buffer);
}

void serial_cdc_dtr_changed(uint8_t port, bool comEnabled)
{
	if (comEnabled)
	{
		LED_On(LED1);
		config_get()->com_enabled = true;
	}
	else
	{
		LED_Off(LED1);
		config_get()->com_enabled = false;
	}
}
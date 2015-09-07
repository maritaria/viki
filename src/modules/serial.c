/*
 * module_serial.c
 *
 * Created: 1-9-2015 11:01:40
 *  Author: Eigenaar
 */

#include "modules/serial.h"
#include "modules/config.h"

result serial_init(void)
{
	irq_initialize_vectors();
	cpu_irq_enable();
	sleepmgr_init();
	sysclk_init();
	udc_start();
	return failure;
}

bool serial_cdc_enable(uint8_t port)
{
	//Communication has opened
	
	//Allow
	return true;
}

void serial_cdc_disable(uint8_t port)
{
	//Communication has closed
	
}

void serial_cdc_rx_notify(uint8_t port)
{
	int value = udi_cdc_getc();
	char text = (char)value;
}

void serial_cdc_dtr_changed(uint8_t port, bool comEnabled)
{
	if (comEnabled)
	{
		LED_On(LED0);
		config_get()->com_enabled = true;
	}
	else
	{
		LED_On(LED1);
		config_get()->com_enabled = false;
	}
}
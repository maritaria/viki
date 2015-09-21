/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
 /**
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>

#include "modules/config.h"
#include "modules/display.h"
#include "modules/input.h"
#include "modules/serial.h"

int main (void)
{
	sysclk_init();
	irq_initialize_vectors();
	board_init();
	config_init();
	serial_init();
	display_init();
	input_init();
	while(true)
	{
		//sleepmgr_enter_sleep();
		display_update();
	}
}

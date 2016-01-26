//Standard C
//ASF
#include <asf.h>
//Custom
#include "modules/clock.h"
#include "modules/config.h"
#include "modules/datetime.h"
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/serial.h"
#include "modules/timeswitches.h"
#include "modules/flash_memory.h"

void init_device(void);
void init_modules(void);
void run_application(void);

int main (void)
{
	init_device();
	init_modules();
	run_application();
}
//call init functions of ASF modules
void init_device()
{
	INTC_init_interrupts();
	irq_initialize_vectors();
	cpu_irq_enable();
	sleepmgr_init();
	sysclk_init();
	board_init();
}
//Call init functions of custom modules
void init_modules()
{
	config_init();
	serial_init();
	display_init();
	joystick_init();
	clock_init();
	menu_init(); 
	datetime_init();
	timeswitches_init();
}
//Main loop
void run_application()
{
	display_clear();
	display_print("Application started");
	display_printf(20, "%8i", sizeof(config_t));
	while(true)
	{
		menu_update();//Draw/update the current menu; these implement handling user input as well
		display_update();//Draw the buffer to the screen device
		clock_update();//Adjust the RTC clock (hack)
	}
}
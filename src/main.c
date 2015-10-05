//Standard C
//ASF
#include <asf.h>
//Custom
#include "modules/config.h"
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/serial.h"
#include "modules/menu.h"

void init_device(void);
void init_modules(void);
void run_application(void);

int main (void)
{
	init_device();
	init_modules();
	run_application();
}

void init_device()
{
	irq_initialize_vectors();
	cpu_irq_enable();
	sleepmgr_init();
	sysclk_init();
	board_init();
}

void init_modules()
{
	config_init();
	serial_init();
	display_init();
	joystick_init();
	menu_init();
}

void run_application()
{
	display_clear();
	display_print("Application started");
	while(true)
	{
		menu_update();
		display_update();
	}
}
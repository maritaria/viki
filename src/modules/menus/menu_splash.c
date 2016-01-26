#include "modules/menus/menu_default.h"
//C standard library
//ASF
//Modules
#include "modules/datetime.h"
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/menu.h"

void menu_splash_render(menu_t* menu);

void menu_splash_tick(menu_t* menu)
{
	if (joystick_is_left())
	{
		joystick_clear_left();
		menu_pop_safe();
	}
	else
	{
		menu_splash_render(menu);
	}
}

void menu_splash_render(menu_t* menu)
{
	display_clear();
	uint64_t timestamp = datetime_get_milliseconds();
	uint32_t seconds = timestamp / 1000;
	uint16_t milliseconds = timestamp % 1000;
	struct calendar_date date = {0};
	calendar_timestamp_to_date(seconds, &date);
	display_printf(20, "%4i-%2i-%2i\n", date.year, date.month+1, date.date+1);
	display_printf(20, "%2ih%2im%2is%3ims\n", date.hour, date.minute, date.second, milliseconds);
}

menu_t* generate_splash_menu(menu_t* parentMenu)
{
	menu_t* splash = menu_add_submenu(parentMenu, "Time");
	splash->tick = menu_splash_tick;
	return splash;
}
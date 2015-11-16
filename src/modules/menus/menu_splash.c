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
	struct calendar_date date = {0};
	calendar_timestamp_to_date(datetime_get_seconds(), &date);
	uint16_t milliseconds = datetime_get_milliseconds();
	display_printf(20, "%2ih%2im%2is%3ims", date.hour, date.minute, date.second, milliseconds);
}
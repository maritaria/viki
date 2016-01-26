#include "modules/menus/item_default.h"
//C standard library
#include <string.h>
//ASF
//Modules
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/config.h"
#include "modules/datetime.h"

//This code adds function to the menu item "Demo mode" on the main menu

char* item_demo_get_text(menu_item_t* item, bool selected)
{
	item_default_get_text(item, selected);
}

void item_demo_on_selected(menu_item_t* item)
{
	item_default_on_selected(item);
}

void setup_alarm(timeswitch_config_t* config, int i)
{
	config->timestamp = 1000;
	config->repeat_interval = 10;
	config->repeat_count = (1 << 16) - 1;
	config->behaviour = toggle;
	config->enabled = true;
	config->output = 1 + i;
}

void setup_alarms()
{
	for(int i = 0; i < TIMER_CONFIG_COUNT; i++)
	{
		setup_alarm(&CONFIG.timers[i], i);
	}
	//30 ms toggle
	CONFIG.timers[0].behaviour = toggle;
	CONFIG.timers[0].enabled = true;
	CONFIG.timers[0].repeat_count = (1 << 16) - 1;
	CONFIG.timers[0].repeat_interval = 30;
	CONFIG.timers[0].timestamp = 1000;
	CONFIG.timers[0].output = 1;
	//30 ms +10ms on
	CONFIG.timers[1].behaviour = on;
	CONFIG.timers[1].enabled = true;
	CONFIG.timers[1].repeat_count = (1 << 16) - 1;
	CONFIG.timers[1].repeat_interval = 30;
	CONFIG.timers[1].timestamp = 1010;
	CONFIG.timers[1].output = 2;
	//30 ms +20ms off
	CONFIG.timers[2].behaviour = off;
	CONFIG.timers[2].enabled = true;
	CONFIG.timers[2].repeat_count = (1 << 16) - 1;
	CONFIG.timers[2].repeat_interval = 30;
	CONFIG.timers[2].timestamp = 1020;
	CONFIG.timers[2].output = 2;
}

void reset_time()
{
	datetime_set_time(0);
}

void item_demo_on_click(menu_item_t* item)
{
	setup_alarms();
	reset_time();
}

menu_item_t* generate_demo_item(menu_t* parentMenu)
{
	menu_item_t* item = menu_add_item(parentMenu, "Demo mode");
	item->get_text = item_demo_get_text;
	item->on_selected = item_demo_on_selected;
	item->on_click = item_demo_on_click;
	return item;
}
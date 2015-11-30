//#include "modules/menus/menu_alert.h"
//C standard library
//ASF
//Modules
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/timeswitches.h"

#define ALERT_FUNC(FUNCNAME) void FUNCNAME(menu_item_t*)

menu_item_t* generate_alert_item(menu_t* parentMenu,  timeswitch_config_t* config, void (*on_click)(menu_item_t*), const char* item_title)
{
	menu_item_t* item = menu_add_item(parentMenu,item_title);
	item->on_click = on_click;
	item->user_data = config;
}

void interval_setting(menu_item_t*);
void target_one(menu_item_t*);
void target_two(menu_item_t*);
void target_three(menu_item_t*);
void target_four(menu_item_t*);
void behavior_on(menu_item_t*);
void behavior_off(menu_item_t*);
void behavior_toggle(menu_item_t*);
void enable_alert(menu_item_t*);
void disable_alert(menu_item_t*);
void clear_settings(menu_item_t*);



menu_t* generate_alert_menu(menu_t* parentMenu, timeswitch_config_t* config, const char* menu_title)
{
	menu_t* alert_menu = menu_add_submenu(parentMenu, menu_title);
	
	menu_t* start_menu = menu_add_submenu(alert_menu, "Start");
	//tijd instellingen hier
	
	menu_t* interval_menu = menu_add_submenu(alert_menu, "Interval");
	//interval instellingen hier
	generate_alert_item(interval_menu, config, interval_setting, "No repeat");
	
	menu_t* repeat_menu = menu_add_submenu(alert_menu, "Repeat");
	
	menu_t* target_menu = menu_add_submenu(alert_menu, "Target");
	generate_alert_item(target_menu, config, target_one, "Target one");
	generate_alert_item(target_menu, config, target_two, "Target two");
	generate_alert_item(target_menu, config, target_three, "Target three");
	generate_alert_item(target_menu, config, target_four, "Target four");
	
	menu_t* behavior_menu = menu_add_submenu(alert_menu, "Behavior");
	generate_alert_item(behavior_menu, config, behavior_on, "On");
	generate_alert_item(behavior_menu, config, behavior_off, "Off");
	generate_alert_item(behavior_menu, config, behavior_toggle, "Toggle");
	
	generate_alert_item(alert_menu, config, enable_alert, "Enable");
	generate_alert_item(alert_menu, config, disable_alert, "Disable");
	generate_alert_item(alert_menu, config, clear_settings, "Clear settings");
}

void interval_setting(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	if(joystick_is_up())
	{
		if(config->repeat_count == -1)
		{
			config->repeat_count = 1;
		}
		else
		{
			config->repeat_count++;
		}
	}
	if(joystick_is_down())
	{
		config->repeat_count--;
		if(config->repeat_count == 0)
		{
			config->repeat_count = -1;
		}
	}
}

void target_one(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->output = 1;
}

void target_two(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->output = 2;
}
void target_three(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->output = 3;
}
void target_four(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->output = 4;
}



void behavior_on(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->behaviour = on;
}

void behavior_off(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->behaviour = off;
}

void behavior_toggle(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->behaviour = toggle;
}



void enable_alert(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->enabled = true;
}

void disable_alert(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->enabled = false;
}



void clear_settings(menu_item_t* item)
{
	timeswitch_config_t* config = item->user_data;
	config->behaviour = off;
	config->enabled = false;
	config->output = 0;
	config->repeat_count = 0;
	config->repeat_interval = 0;
	config->timestamp = 0;
}
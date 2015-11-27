//#include "modules/menus/menu_alert.h"
//C standard library
//ASF
//Modules
#include "modules/menu.h"
#include "modules/timeswitches.h"

#define ALERT_FUNC(FUNCNAME) void FUNCNAME(menu_item_t*)

menu_item_t* generate_alert_item(menu_t* parentMenu,  timeswitch_config_t* config, void (*on_click)(menu_item_t*), const char* item_title)
{
	menu_item_t* item = menu_add_item(parentMenu,item_title);
	item->on_click = on_click;
	item->user_data = config;
}

void behavior_on(menu_item_t*);
void behavior_off(menu_item_t*);
void behavior_toggle(menu_item_t*);
void enable_alert(menu_item_t*);
void disable_alert(menu_item_t*);



menu_t* generate_alert_menu(menu_t* parentMenu, timeswitch_config_t* config, const char* menu_title)
{
	menu_t* alert_menu = menu_add_submenu(parentMenu, menu_title);

	menu_t* behavior_menu = menu_add_submenu(alert_menu, "Behavior");
	generate_alert_item(behavior_menu, config, behavior_on, "On");
	generate_alert_item(behavior_menu, config, behavior_off, "Off");
	generate_alert_item(behavior_menu, config, behavior_toggle, "Toggle");
	
	generate_alert_item(alert_menu, config, enable_alert, "Enable");
	generate_alert_item(alert_menu, config, disable_alert, "Disable");
	
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
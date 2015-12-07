#include "modules/menu.h"
//Standard C
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//ASF
//Custom
#include "modules/config.h"
#include "modules/display.h"
#include "modules/menus/menu_alert.h"
#include "modules/menus/menu_default.h"
#include "modules/menus/menu_splash.h"
#include "modules/menus/item_default.h"
#include "modules/menus/item_submenu.h"


volatile menu_t* active_menu_stack[MAXIMUM_ACTIVE_MENUS] = {0};
volatile int active_menu_index = -1;

menu_t* menu_create_empty(void);
void menu_create_state(menu_t* menu);
void menu_create_submenu_item(const char* defaultTitle, menu_t* parentMenu, menu_t* menu);

void testfunctie(menu_item_t* item){
	item = NULL;
}

bool menu_init()
{
	menu_t* main_menu = menu_create("Main menu");
	
	generate_alerts_menu(main_menu, &CONFIG);
	
	menu_t* usb_settings = menu_add_submenu(main_menu, "USB Settings");
	
	menu_t* usb_edit_baud = menu_add_submenu(usb_settings, "Baud rate");
	menu_add_item(usb_edit_baud, "9600");
	menu_add_item(usb_edit_baud, "56000");
	menu_add_item(usb_edit_baud, "115200");
	
	menu_t* usb_edit_databits = menu_add_submenu(usb_settings, "Data bits");
	menu_add_item(usb_edit_databits, "7");
	menu_add_item(usb_edit_databits, "8");
	
	menu_t* usb_edit_parity = menu_add_submenu(usb_settings, "Parity");
	menu_add_item(usb_edit_parity, "Even");
	menu_add_item(usb_edit_parity, "Odd");
	menu_add_item(usb_edit_parity, "Mark");
	
	menu_add_item(usb_settings, "Enable");
	menu_add_item(usb_settings, "Disable");
	menu_add_item(usb_settings, "Restart");
	
	menu_t* test = menu_add_submenu(main_menu, "Test");
	menu_item_t* testitem = menu_add_item(test, "test1");
	testitem->on_click = testfunctie;
	
	menu_t* splash = menu_add_submenu(main_menu, "Time");
	splash->tick = menu_splash_tick;
		
	/*splash_screen,
	idle,
	menu,
	alert_list,//STATIC COUNT
	alert_settings,
	alert_edit_start, //DISABLE AFTER FIRST INTERVAL
	alert_edit_interval,
	alert_edit_repeat,
	alert_edit_target,
	alert_edit_behaviour,
	alert_edit_enable,
	alert_edit_clear,
	usb_settings,
	usb_edit_baud,//9600, 56000, 115200
	usb_edit_databits,//7, 8
	usb_edit_parity,//ON EVEN ODD MARK
	usb_edit_enable, //ON OFF RESTART
	power_settings,
	screen_edit_power,//0..4
	screen_edit_hybernate,//ALWAYS ON, HYBERNATE
	screen_edit_inversion,//ENABLED, DISABLED
	help_main,
	help_navigation,
	help_alerts_basic,
	help_alerts_behaviour,
	help_alerts_repeat,*/
	
	menu_push(main_menu);
	return true;
}

void menu_update()
{
	menu_t* menu = menu_peek();
	if (menu)
	{
		menu->tick(menu);
	}
}

menu_t* menu_create(const char* defaultTitle)
{
	menu_t* menu = menu_create_empty();
	menu->default_title = (char*)defaultTitle;
	menu->get_title = menu_default_get_title;
	menu->tick = menu_default_tick;
	menu_create_state(menu);
	return menu;
}

menu_t* menu_create_empty()
{
	menu_t* menu = malloc(sizeof(menu_t));
	*menu = (menu_t){0};
	return menu;
}

void menu_create_state(menu_t* menu)
{
	menu_state_t* menu_state = malloc(sizeof(menu_state_t));
	menu_state->scroll = 0;
	menu_state->selected_index = 0;
	menu->user_data = menu_state;
}

void menu_create_submenu_item(const char* defaultTitle, menu_t* parentMenu, menu_t* menu)
{
	menu_item_t* item = menu_add_item(parentMenu, defaultTitle);
	item->user_data = (void*)menu;
	item->get_text = item_submenu_get_text;
	item->on_selected = item_submenu_on_selected;
	item->on_click = item_submenu_on_click;
}

menu_item_t* menu_add_item(menu_t* parentMenu, const char* defaultText)
{
	menu_item_t* item = malloc(sizeof(menu_item_t));
	*item = (menu_item_t){0};
	item->default_text = (char*)defaultText;
	item->get_text = item_default_get_text;
	item->on_selected = item_default_on_selected;
	item->on_click = item_default_on_click;
	menu_item_t* lastItem = menu_get_last_item(parentMenu);
	if (lastItem)
	{
		lastItem->next_item = item;
	}
	else
	{
		parentMenu->first_item = item;
	}
	return item;
}

menu_t* menu_add_submenu(menu_t* parentMenu, const char* defaultTitle)
{
	menu_t* menu = menu_create(defaultTitle);
	menu_create_submenu_item(defaultTitle, parentMenu, menu);
	return menu;
}

void menu_push(menu_t* menu)
{
	while (menu_count() >= MAXIMUM_ACTIVE_MENUS);
	active_menu_index++;
	active_menu_stack[active_menu_index] = menu;
}

void menu_pop()
{
	while(menu_count() <= 0);
	active_menu_stack[active_menu_index] = NULL;
	active_menu_index--;
}

void menu_pop_safe()
{
	if (menu_count() > 1)
	{
		menu_pop();
	}
}

menu_t* menu_peek()
{
	if (menu_count() > 0)
	{
		return active_menu_stack[active_menu_index];	
	}
	else
	{
		return NULL;
	}
}

int menu_count()
{
	return active_menu_index + 1;
}

char* menu_get_title(menu_t* menu)
{
	return menu->get_title(menu);
}

menu_item_t* menu_get_item_at(menu_t* menu, unsigned int index)
{
	menu_item_t* item = menu->first_item;
	for(int i = 0; i < index; i++)
	{
		if (item)
		{
			item = item->next_item;
		}
		else
		{
			return NULL;
		}
	}
	return item;
}

menu_item_t* menu_get_last_item(menu_t* menu)
{
	menu_item_t* item = menu->first_item;
	if (item)
	{
		while(item->next_item)
		{
			item = item->next_item;
		}
	}
	return item;
}

int menu_get_item_count(menu_t* menu)
{
	menu_item_t* item = menu->first_item;
	if (!item)
	{
		return 0;
	}
	int count = 1;
	while(item->next_item)
	{
		item = item->next_item;
		count++;
	}
	return count;
}

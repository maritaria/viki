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
#include "modules/menus/menu_datetime.h"
#include "modules/menus/item_demo.h"

//This variable stores the stack of menu's, when a menu is removed the menu below it will be shown (until no menu's are available no more)
//The maximum number of active menus is controlled through a define-constant
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
	generate_splash_menu(main_menu);
	generate_datetime_menu(main_menu);
	generate_demo_item(main_menu);
	menu_push(main_menu);
	return true;
}

//Updates and draws the currently shown menu, called from main() in while(true)
void menu_update()
{
	menu_t* menu = menu_peek();
	if (menu)
	{
		menu->tick(menu);
	}
}

//Creates a menu with a given title; and returns a pointer to it
menu_t* menu_create(const char* defaultTitle)
{
	menu_t* menu = menu_create_empty();
	menu->default_title = (char*)defaultTitle;
	menu->get_title = menu_default_get_title;
	menu->tick = menu_default_tick;
	menu->on_load = menu_default_on_load;
	menu_create_state(menu);
	return menu;
}

menu_t* menu_create_empty()
{
	//The entire menu system exists on the heap (except for strings)
	menu_t* menu = malloc(sizeof(menu_t));
	*menu = (menu_t){0};
	return menu;
}
//A menu state is used with default menu's it's to keep track of the current selected item and the amount the user has scrolled down in the list of items
void menu_create_state(menu_t* menu)
{
	menu_state_t* menu_state = malloc(sizeof(menu_state_t));
	menu_state->scroll = 0;
	menu_state->selected_index = 0;
	menu->user_data = menu_state;
}
//This function creates a menu item on an existing menu(parentMenu) and makes it so it opens a second menu
void menu_create_submenu_item(const char* defaultTitle, menu_t* parentMenu, menu_t* menu)
{
	menu_item_t* item = menu_add_item(parentMenu, defaultTitle);
	item->user_data = (void*)menu;//user_data contains the new menu to be opened
	item->get_text = item_submenu_get_text;
	item->on_selected = item_submenu_on_selected;
	item->on_click = item_submenu_on_click;
}
//Creates a new menu item to an existing menu
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
//Creates a new submenu on a given menu; creates and returns the submenu and creates a menu item on the parentMenu that opens the new menu when selected by the user
menu_t* menu_add_submenu(menu_t* parentMenu, const char* defaultTitle)
{
	menu_t* menu = menu_create(defaultTitle);
	menu_create_submenu_item(defaultTitle, parentMenu, menu);
	return menu;
}
//Push a menu on top of the stack; causing it to be updated and drawn
void menu_push(menu_t* menu)
{
	while (menu_count() >= MAXIMUM_ACTIVE_MENUS);//assertion
	active_menu_index++;
	active_menu_stack[active_menu_index] = menu;
	menu->on_load(menu);
}
//Remove the menu currently being shown
void menu_pop()
{
	while(menu_count() <= 0);//assertion
	active_menu_stack[active_menu_index] = NULL;
	active_menu_index--;
}
//Only removes a menu if there is one
void menu_pop_safe()
{
	if (menu_count() > 1)
	{
		menu_pop();
	}
}
//Get the menu currently being shown
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
//Get the number of menus on the stack
int menu_count()
{
	return active_menu_index + 1;
}
//Get the title of a given menu
char* menu_get_title(menu_t* menu)
{
	return menu->get_title(menu);
}
//The menu items work via a linked list system rather than an array system (easier memory wise)
//This function walks through the linked list until it finds the menu item at a given index; returns NULL if no item was found or out of bounds
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
//Gets the last item in the linked list of items belonging to a menu
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
//Get the number of items in the linked list of items belonging to a menu (expensive)
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

#include "modules/menu.h"
//Standard C
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
//ASF
//Custom
#include "modules/config.h"
#include "modules/display.h"

volatile menu_t* active_menu_stack[MAXIMUM_ACTIVE_MENUS] = {0};
volatile int active_menu_count = 0;

char* __default_menu_get_title(menu_t* menu);
void __default_menu_update(menu_t* menu);
char* __default_menu_item_get_text(menu_item_t* item);
void __default_menu_item_on_item_selected(menu_item_t* item);
char* __submenu_item_get_text(menu_item_t* item);
void __submenu_item_on_item_selected(menu_item_t* item);

bool menu_init()
{
	menu_t* mainMenu = menu_create("Main menu", NULL);
	menu_t* subMenu = menu_create("My awesome sub menu", mainMenu);
	
	menu_item_t* myItem = menu_add_item("My item", subMenu);
	menu_item_t* advancedItem = menu_add_item("Hello world", subMenu);
	advancedItem->get_text = __default_menu_item_get_text;
	
	menu_push(mainMenu);
	menu_push(subMenu);
	return true;
}

void menu_update()
{
	menu_t* menu = menu_peek();
	if (menu)
	{
		menu->update(menu);
	}
}

menu_t* menu_create(const char* defaultTitle, menu_t* parentMenu)
{
	menu_t* menu = malloc(sizeof(menu_t));
	*menu = (menu_t){0};
	menu->default_title = defaultTitle;
	menu->get_title = __default_menu_get_title;
	menu->update = __default_menu_update;
	if (parentMenu)
	{
		menu_item_t* item = menu_add_item(defaultTitle, parentMenu);
		item->user_data = (void*)menu;
		item->get_text = __submenu_item_get_text;
		item->on_item_selected = __submenu_item_on_item_selected;
	}
	return menu;
}

menu_item_t* menu_add_item(const char* defaultText, menu_t* parentMenu)
{
	menu_item_t* item = malloc(sizeof(menu_item_t));
	*item = (menu_item_t){0};
	item->default_text = defaultText;
	item->get_text = __default_menu_item_get_text;
	item->on_item_selected = __default_menu_item_on_item_selected;
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

void menu_push(menu_t* menu)
{
	while (active_menu_count >= MAXIMUM_ACTIVE_MENUS);
	active_menu_stack[active_menu_count] = menu;
	active_menu_count++;
}

menu_t* menu_pop()
{
	while(active_menu_count <= 0);
	menu_t* active_menu = menu_peek();
	active_menu_stack[active_menu_count] = NULL;
	active_menu_count--;
	return active_menu;
}

menu_t* menu_peek()
{
	if (active_menu_count > 0)
	{
		return active_menu_stack[active_menu_count - 1];	
	}
	else
	{
		return NULL;
	}
}

char* menu_get_title(menu_t* menu)
{
	return menu->get_title(menu);
}

char* menu_item_get_text(menu_item_t* item)
{
	return item->get_text(item);
}

menu_item_t* menu_item_at(menu_t* menu, unsigned int index)
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
	int count = 0;
	while(item->next_item)
	{
		item = item->next_item;
		count++;
	}
	return count;
}


char* __default_menu_get_title(menu_t* menu)
{
	return menu->default_title;
}

void __default_menu_update(menu_t* menu)
{
	display_set_cursor(false);
	display_clear();
	display_print(menu->get_title(menu));
	
	int item_count = menu_get_item_count(menu);
	menu_item_t* item = menu->first_item;
	for(int i = 0; i < 3; i++)
	{
		if (item)
		{
			display_printf(21, "\n%i: %s", i, item->get_text(item));
			item = item->next_item;
		}
	}
}

char* __default_menu_item_get_text(menu_item_t* item)
{
	return item->default_text;
}

void __default_menu_item_on_item_selected(menu_item_t* item)
{
	menu_pop();
}

char* __submenu_item_get_text(menu_item_t* item)
{
	menu_t* menu = (menu_t*) item->user_data;
	return menu->get_title(menu);
}

void __submenu_item_on_item_selected(menu_item_t* item)
{
	menu_t* menu = (menu_t*)item->user_data;
	menu_push(menu);
}
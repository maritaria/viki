#include "modules/menus/item_submenu.h"
//C standard library
//ASF
//Modules
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/menus/item_default.h"

char* item_submenu_get_text(menu_item_t* item, bool selected)
{
	menu_t* menu = (menu_t*) item->user_data;
	item->default_text = menu->get_title(menu);
	return item_default_get_text(item, selected);
}

void item_submenu_on_selected(menu_item_t* item)
{
	item_default_on_selected(item);
}

void item_submenu_on_click(menu_item_t* item)
{
	menu_t* menu = (menu_t*)item->user_data;
	menu_push(menu);
}
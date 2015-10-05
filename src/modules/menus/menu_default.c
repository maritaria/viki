#include "modules/menus/menu_default.h"
//C standard library
//ASF
//Modules
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/menus/item_submenu.h"



void menu_default_update(menu_t* menu);
void menu_default_handle_input(menu_t* menu, menu_state_t* state);
void menu_default_select_previous(menu_t* menu, menu_state_t* state);
void menu_default_select_next(menu_t* menu, menu_state_t* state);
void menu_default_selection_changed(menu_t* menu, menu_state_t* state);
void menu_default_click_item(menu_t* menu, menu_state_t* state);
void menu_default_clamp_scroll(menu_state_t* state);

void menu_default_render(menu_t* menu);

bool menu_item_is_submenu(menu_item_t* item);

char* menu_default_get_title(menu_t* menu)
{
	return menu->default_title;
}

void menu_default_tick(menu_t* menu)
{
	menu_default_update(menu);
	menu_default_render(menu);
}

void menu_default_update(menu_t* menu)
{
	menu_state_t* state = (menu_state_t*)menu->user_data;
	menu_default_handle_input(menu, state);	
	menu_default_clamp_scroll(state);
}

void menu_default_handle_input(menu_t* menu, menu_state_t* state)
{
	if (joystick_is_up())
	{
		joystick_clear_up();
		menu_default_select_previous(menu, state);
	}
	if (joystick_is_down())
	{
		joystick_clear_down();
		menu_default_select_next(menu, state);
	}
	if (joystick_is_right())
	{
		joystick_clear_right();
		if (menu_item_is_submenu(menu_get_item_at(menu, state->selected_index)))
		{
			menu_default_click_item(menu, state);
		}
	}
	if (joystick_is_left())
	{
		joystick_clear_left();
		menu_pop_safe();
	}
	if (joystick_is_pressed())
	{
		joystick_clear_pressed();
		menu_default_click_item(menu, state);
	}
}

void menu_default_select_previous(menu_t* menu, menu_state_t* state)
{
	if (state->selected_index > 0)
	{
		state->selected_index--;
	}
	menu_default_selection_changed(menu, state);
}

void menu_default_select_next(menu_t* menu, menu_state_t* state)
{
	if (state->selected_index < menu_get_item_count(menu) - 1)
	{
		state->selected_index++;
	}
	menu_default_selection_changed(menu, state);
}

void menu_default_selection_changed(menu_t* menu, menu_state_t* state)
{
	menu_item_t* new_item = menu_get_item_at(menu, state->selected_index);
	new_item->on_selected(new_item);
}

void menu_default_click_item(menu_t* menu, menu_state_t* state)
{
	menu_item_t* item = menu_get_item_at(menu, state->selected_index);
	item->on_click(item);
}

void menu_default_clamp_scroll(menu_state_t* state)
{
	state->scroll = clamp(state->scroll, state->selected_index - MENU_VISIBLE_ITEM_COUNT + 1, state->selected_index);
}

void menu_default_render(menu_t* menu)
{
	menu_state_t* state = (menu_state_t*)menu->user_data;
	display_set_cursor(false);
	display_clear();
	
	int item_count = menu_get_item_count(menu);
	if (!menu->first_item)
	{
		display_print("\n     Empty menu     ");
		return;
	}
	
	char scroll_up = ' ';
	if (state->selected_index > 0)
	{
		scroll_up = 0xDE;
	}
	char scroll_down = ' ';
	if (state->selected_index < item_count - 1)
	{
		scroll_down = 0xE0;
	}
	
	display_printf(20, "%-17s %c%c\n", menu->get_title(menu), scroll_up, scroll_down);
	
	menu_item_t* item = menu_get_item_at(menu, state->scroll);
	for(int i = state->scroll; i < state->scroll + MENU_VISIBLE_ITEM_COUNT; i++)
	{
		if (item)
		{
			bool selected = i == state->selected_index;
			char cursor = ' ';
			if (selected)
			{
				cursor = 0xDF;
			}
			char folder = ' ';
			if (menu_item_is_submenu(item))
			{
				folder = 0x10;
			}
			display_printf(20, "%c%-18s%c\n", cursor, item->get_text(item, selected), folder);
			item = item->next_item;
		}
		else
		{
			display_print("\n");
		}
	}
}

bool menu_item_is_submenu(menu_item_t* item)
{
	return (item->on_click == item_submenu_on_click);
}
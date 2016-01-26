#include "modules/menus/editor_integer.h"
//C standard library
//ASF
//Modules
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/menus/menu_default.h"

void editor_integer_update(menu_t* menu, editor_integer_data_t* data);
void editor_integer_render(menu_t* menu, editor_integer_data_t* data);


char* editor_integer_get_title(menu_t* menu)
{
	return menu_default_get_title(menu);

}

void editor_integer_tick(menu_t* menu)
{
	editor_integer_data_t* data = (editor_integer_data_t*)menu->user_data;
	editor_integer_update(menu, data);
	editor_integer_render(menu, data);
}

void editor_integer_update(menu_t* menu, editor_integer_data_t* data)
{
	int newValue = (data->value);
	if (joystick_is_up())
	{
		//TODO; clamp here
		joystick_clear_up();
		newValue++;
	}
	if (joystick_is_down())
	{
		joystick_clear_down();
		newValue--;
	}
	data->value = clamp(newValue, data->min, data->max);
	
	if (joystick_is_left())
	{
		joystick_clear_left();
		menu_pop_safe();
		data->on_cancel(menu, data);
	}
	
	if (joystick_is_right())
	{
		joystick_clear_right();
		menu_pop_safe();
		data->on_completed(menu, data);
	}
}

void editor_integer_render(menu_t* menu, editor_integer_data_t* data)
{
	display_clear();
	display_printf(20, "%-20s\n", menu->get_title(menu));
	
	display_printf(20, "  Value: %i\n", data->value);	
}

void editor_integer_on_load(menu_t* menu)
{
	editor_integer_data_t* editor = (editor_integer_data_t*)menu->user_data;
	if(editor->on_load)
	{
		editor->on_load(menu, editor);
	}
}
//Creates a new menu for the editor and sets it up by copying over the dataTemplate
menu_t* generate_editor_integer(menu_t* parentMenu, const char* defaultTitle, editor_integer_data_t dataTemplate)
{
	menu_t* newMenu = menu_add_submenu(parentMenu, defaultTitle);
	newMenu->get_title = editor_integer_get_title;
	newMenu->tick = editor_integer_tick;
	newMenu->on_load = editor_integer_on_load;
	free(newMenu->user_data);
	editor_integer_data_t* data = malloc(sizeof(editor_integer_data_t));
	data->value = dataTemplate.value;
	data->min = dataTemplate.min;
	data->max = dataTemplate.max;
	data->on_cancel = dataTemplate.on_cancel;
	data->on_completed = dataTemplate.on_completed;
	data->on_load = dataTemplate.on_load;
	data->user_data = dataTemplate.user_data;
	newMenu->user_data = (void*)data;
	return newMenu;
}
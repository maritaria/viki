#include "modules/menus/editor_timestamp.h"
//C standard library
//ASF
//Modules
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/menus/menu_default.h"

void editor_timestamp_update(menu_t*, editor_timestamp_data_t* editor);
void editor_timestamp_next_field(editor_timestamp_data_t* editor);
void editor_timestamp_previous_field(editor_timestamp_data_t* editor);
void editor_timestamp_increment_field(editor_timestamp_data_t* editor);
void editor_timestamp_decrement_field(editor_timestamp_data_t* editor);
void editor_timestamp_click_field(menu_t*, editor_timestamp_data_t* editor);

void editor_timestamp_render(menu_t* menu);
void editor_timestamp_render_title(menu_t* menu);
void editor_timestamp_render_date(editor_timestamp_data_t* editor);
void editor_timestamp_render_time(editor_timestamp_data_t* editor);
void editor_timestamp_render_actions(editor_timestamp_data_t* editor);

int increment_year(editor_timestamp_data_t* editor);
int increment_month(editor_timestamp_data_t* editor);
int increment_date(editor_timestamp_data_t* editor);
int increment_hour(editor_timestamp_data_t* editor);
int increment_minute(editor_timestamp_data_t* editor);
int increment_second(editor_timestamp_data_t* editor);
int increment_milliseconds(editor_timestamp_data_t* editor);

int decrement_year(editor_timestamp_data_t* editor);
int decrement_month(editor_timestamp_data_t* editor);
int decrement_date(editor_timestamp_data_t* editor);
int decrement_hour(editor_timestamp_data_t* editor);
int decrement_minute(editor_timestamp_data_t* editor);
int decrement_second(editor_timestamp_data_t* editor);
int decrement_milliseconds(editor_timestamp_data_t* editor);

void editor_timestamp_accept(menu_t*, editor_timestamp_data_t*);
void editor_timestamp_cancel(menu_t*, editor_timestamp_data_t*);
void editor_timestamp_reset(menu_t*, editor_timestamp_data_t*);

char* editor_timestamp_get_title(menu_t* menu)
{
	return menu_default_get_title(menu);
}

void editor_timestamp_tick(menu_t* menu)
{
	editor_timestamp_data_t* editor = (editor_timestamp_data_t*)menu->user_data;
	editor_timestamp_update(menu, editor);
	editor_timestamp_render(menu);
}

void editor_timestamp_update(menu_t* menu, editor_timestamp_data_t* editor)
{
	if (joystick_is_left())
	{
		joystick_clear_left();
		editor_timestamp_previous_field(editor);
	}
	if (joystick_is_right())
	{
		joystick_clear_right();
		editor_timestamp_next_field(editor);
	}
	if (joystick_is_up())
	{
		joystick_clear_up();
		editor_timestamp_increment_field(editor);
	}
	if (joystick_is_down())
	{
		joystick_clear_down();
		editor_timestamp_decrement_field(editor);
	}
	if (joystick_is_pressed())	
	{
		joystick_clear_pressed();
		editor_timestamp_click_field(menu, editor);
	}
}

void editor_timestamp_next_field(editor_timestamp_data_t* editor)
{
	switch(editor->current_field)
	{
		case date_year: editor->current_field = date_month; break;
		case date_month: editor->current_field = date_day; break;
		case date_day: editor->current_field = time_hour; break;
		case time_hour: editor->current_field = time_minute; break;
		case time_minute: editor->current_field = time_second; break;
		case time_second: editor->current_field = time_millisecond; break;
		case time_millisecond: editor->current_field = action_accept; break;
		case action_accept: editor->current_field = action_cancel; break;
		case action_cancel: editor->current_field = action_reset; break;
		case action_reset: editor->current_field = date_year; break;
		
		default: editor->current_field = date_year; break;
	}
}

void editor_timestamp_previous_field(editor_timestamp_data_t* editor)
{
	switch(editor->current_field)
	{
		case date_year: editor->current_field = action_reset; break;
		case date_month: editor->current_field = date_year; break;
		case date_day: editor->current_field = date_month; break;
		case time_hour: editor->current_field = date_day; break;
		case time_minute: editor->current_field = time_hour; break;
		case time_second: editor->current_field = time_minute; break;
		case time_millisecond: editor->current_field = time_second; break;
		case action_accept: editor->current_field = time_millisecond; break;
		case action_cancel: editor->current_field = action_accept; break;
		case action_reset: editor->current_field = action_cancel; break;
		
		default: editor->current_field = date_year; break;
	}
}

void editor_timestamp_increment_field(editor_timestamp_data_t* editor)
{
	switch(editor->current_field)
	{
		case date_year: increment_year(editor); break;
		case date_month: increment_month(editor); break;
		case date_day: increment_date(editor); break;
		case time_hour: increment_hour(editor); break;
		case time_minute: increment_minute(editor); break;
		case time_second: increment_second(editor); break;
		case time_millisecond: increment_milliseconds(editor); break;
		
		default: break;
	}
}

void editor_timestamp_decrement_field(editor_timestamp_data_t* editor)
{
	switch(editor->current_field)
	{
		case date_year: decrement_year(editor); break;
		case date_month: decrement_month(editor); break;
		case date_day: decrement_date(editor); break;
		case time_hour: decrement_hour(editor); break;
		case time_minute: decrement_minute(editor); break;
		case time_second: decrement_second(editor); break;
		case time_millisecond: decrement_milliseconds(editor); break;
		
		default: break;
	}
}

void editor_timestamp_click_field(menu_t* menu, editor_timestamp_data_t* editor)
{
	switch(editor->current_field)
	{
		case action_accept:
			editor_timestamp_accept(menu, editor);
		break;
		case action_cancel:
			editor_timestamp_cancel(menu, editor);
		break;
		case action_reset:
			editor_timestamp_reset(menu, editor);
		break;
	}
}

void editor_timestamp_render(menu_t* menu)
{
	display_clear();
	editor_timestamp_render_title(menu);
	editor_timestamp_data_t* editor = (editor_timestamp_data_t*)menu->user_data;
	editor_timestamp_render_date(editor);
	editor_timestamp_render_time(editor);
	editor_timestamp_render_actions(editor);
}

void editor_timestamp_render_title(menu_t* menu)
{
	display_printf(20, "%s\n", editor_timestamp_get_title(menu));
}

void editor_timestamp_render_date(editor_timestamp_data_t* editor)
{
	display_printf(20, "Date: %.4i-%.2i-%.2i    ",
		editor->user_input.calendar_date.year,
		editor->user_input.calendar_date.month + 1,
		editor->user_input.calendar_date.date + 1
	);
}

void editor_timestamp_render_time(editor_timestamp_data_t* editor)
{
	display_printf(20, "Time: %.2i:%.2i:%.2i %.3ims",
		editor->user_input.calendar_date.hour,
		editor->user_input.calendar_date.minute,
		editor->user_input.calendar_date.second,
		editor->user_input.milliseconds
	);
}

void editor_timestamp_render_actions(editor_timestamp_data_t* editor)
{
	char accept = DISPLAY_SPACE;
	char cancel = DISPLAY_SPACE;
	char reset = DISPLAY_SPACE;
	switch(editor->current_field)
	{
		case action_accept: accept = DISPLAY_ARROW_RIGHT; break;
		case action_cancel: cancel = DISPLAY_ARROW_RIGHT; break;
		case action_reset: reset = DISPLAY_ARROW_RIGHT; break;
	}
	
	
	display_printf(20, "%cOK %cCancel %cReset",
		accept,
		cancel,
		reset
	);
}
//Creates a new menu for the editor and sets it up by copying over the dataTemplate
menu_t* generate_editor_timestamp(menu_t* parentMenu, const char* defaultTitle, editor_timestamp_data_t dataTemplate)
{
	menu_t* newMenu = menu_add_submenu(parentMenu, defaultTitle);
	newMenu->get_title = editor_timestamp_get_title;
	newMenu->tick = editor_timestamp_tick;
	newMenu->on_load = editor_timestamp_on_load;
	free(newMenu->user_data);
	editor_timestamp_data_t* data = malloc(sizeof(editor_timestamp_data_t));
	data->current_field = dataTemplate.current_field;
	data->field_offset = dataTemplate.field_offset;
	data->initial_input = dataTemplate.initial_input;
	data->on_cancel = dataTemplate.on_cancel;
	data->on_completed = dataTemplate.on_completed;
	data->on_load = dataTemplate.on_load;
	data->user_data = dataTemplate.user_data;
	data->user_input = dataTemplate.user_input;
	newMenu->user_data = (void*)data;
	return newMenu;
}

int increment_year(editor_timestamp_data_t* editor)
{
	editor->user_input.calendar_date.year++;
	if(editor->user_input.calendar_date.year > 9999)
	{
		editor->user_input.calendar_date.year = 9999;
	}
	return editor->user_input.calendar_date.year;
}

int increment_month(editor_timestamp_data_t* editor)
{
	editor->user_input.calendar_date.month++;
	if(editor->user_input.calendar_date.month >= 11)
	{
		editor->user_input.calendar_date.month = 11;
	}
	return editor->user_input.calendar_date.month;
}

int increment_date(editor_timestamp_data_t* editor)
{
	editor->user_input.calendar_date.date++;
	if(editor->user_input.calendar_date.date >= 30)
	{
		editor->user_input.calendar_date.date = 30;
	}
	return editor->user_input.calendar_date.date;
}

int increment_hour(editor_timestamp_data_t* editor)
{
	editor->user_input.calendar_date.hour++;
	if(editor->user_input.calendar_date.hour > 23)
	{
		editor->user_input.calendar_date.hour = 23;
	}
	return editor->user_input.calendar_date.hour;
}

int increment_minute(editor_timestamp_data_t* editor)
{
	editor->user_input.calendar_date.minute++;
	if(editor->user_input.calendar_date.minute > 59)
	{
		editor->user_input.calendar_date.minute = 59;
	}
	return editor->user_input.calendar_date.minute;
}

int increment_second(editor_timestamp_data_t* editor)
{
	editor->user_input.calendar_date.second++;
	if(editor->user_input.calendar_date.second > 59)
	{
		editor->user_input.calendar_date.second = 59;
	}
	return editor->user_input.calendar_date.second;
}

int increment_milliseconds(editor_timestamp_data_t* editor)
{
	editor->user_input.milliseconds++;
	if(editor->user_input.milliseconds > 999)
	{
		editor->user_input.milliseconds = 999;
	}
	return editor->user_input.milliseconds;
}

int decrement_year(editor_timestamp_data_t* editor)
{
	if(editor->user_input.calendar_date.year > 0)
	{
		editor->user_input.calendar_date.year--;
	}
	return editor->user_input.calendar_date.year;
}

int decrement_month(editor_timestamp_data_t* editor)
{
	if(editor->user_input.calendar_date.month > 0)
	{
		editor->user_input.calendar_date.month--;
	}
	return editor->user_input.calendar_date.month;
}

int decrement_date(editor_timestamp_data_t* editor)
{
	if(editor->user_input.calendar_date.date > 0)
	{
		editor->user_input.calendar_date.date--;
	}
	return editor->user_input.calendar_date.date;
}

int decrement_hour(editor_timestamp_data_t* editor)
{
	if(editor->user_input.calendar_date.hour > 0)
	{
		editor->user_input.calendar_date.hour--;
	}
	return editor->user_input.calendar_date.hour;
}

int decrement_minute(editor_timestamp_data_t* editor)
{
	if(editor->user_input.calendar_date.minute > 0)
	{
		editor->user_input.calendar_date.minute--;
	}
	return editor->user_input.calendar_date.minute;
}

int decrement_second(editor_timestamp_data_t* editor)
{
	if(editor->user_input.calendar_date.second > 0)
	{
		editor->user_input.calendar_date.second--;
	}
	return editor->user_input.calendar_date.second;
}

int decrement_milliseconds(editor_timestamp_data_t* editor)
{
	if(editor->user_input.milliseconds > 0)
	{
		editor->user_input.milliseconds--;
	}
	return editor->user_input.milliseconds;
}

void editor_timestamp_accept(menu_t* menu, editor_timestamp_data_t* editor)
{
	menu_pop_safe();
	editor->on_completed(menu, editor);
}

void editor_timestamp_cancel(menu_t* menu, editor_timestamp_data_t* editor)
{
	menu_pop_safe();
	editor->on_cancel(menu, editor);
}

void editor_timestamp_reset(menu_t* menu, editor_timestamp_data_t* editor)
{
	editor->user_input = editor->initial_input;	
}

void editor_timestamp_on_load(menu_t* menu)
{
	editor_timestamp_data_t* editor = (editor_timestamp_data_t*)menu->user_data;
	if(editor->on_load)
	{
		editor->on_load(menu, editor);
	}	
}
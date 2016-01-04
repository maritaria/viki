#include "modules/menus/editor_interval.h"
//C standard library
//ASF
//Modules
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/menus/menu_default.h"

#define BLINK_INTERVAL (30)
#define USE_BLINK (editor_blink_time > (BLINK_INTERVAL/2))
int editor_blink_time = 0;

void editor_interval_update(menu_t*, editor_interval_data_t* editor);
void editor_interval_next_field(editor_interval_data_t* editor);
void editor_interval_previous_field(editor_interval_data_t* editor);
void editor_interval_increment_interval_field(editor_interval_data_t* editor);
void editor_interval_decrement_interval_field(editor_interval_data_t* editor);
void editor_interval_click_field(menu_t*, editor_interval_data_t* editor);

void editor_interval_render(menu_t* menu);
void editor_interval_render_title(menu_t* menu);
void editor_interval_render_date(editor_interval_data_t* editor);
void editor_interval_render_time(editor_interval_data_t* editor);
void editor_interval_render_actions(editor_interval_data_t* editor);

int increment_interval_date(editor_interval_data_t* editor);
int increment_interval_hour(editor_interval_data_t* editor);
int increment_interval_minute(editor_interval_data_t* editor);
int increment_interval_second(editor_interval_data_t* editor);
int increment_interval_milliseconds(editor_interval_data_t* editor);

int decrement_interval_date(editor_interval_data_t* editor);
int decrement_interval_hour(editor_interval_data_t* editor);
int decrement_interval_minute(editor_interval_data_t* editor);
int decrement_interval_second(editor_interval_data_t* editor);
int decrement_interval_milliseconds(editor_interval_data_t* editor);

void editor_interval_accept(menu_t*, editor_interval_data_t*);
void editor_interval_cancel(menu_t*, editor_interval_data_t*);
void editor_interval_reset(menu_t*, editor_interval_data_t*);

char* editor_interval_get_title(menu_t* menu)
{
	return menu_default_get_title(menu);
}

void editor_interval_tick(menu_t* menu)
{
	editor_interval_data_t* editor = (editor_interval_data_t*)menu->user_data;
	editor_interval_update(menu, editor);
	editor_interval_render(menu);
}

void editor_interval_update(menu_t* menu, editor_interval_data_t* editor)
{
	if (joystick_is_left())
	{
		joystick_clear_left();
		editor_interval_previous_field(editor);
	}
	if (joystick_is_right())
	{
		joystick_clear_right();
		editor_interval_next_field(editor);
	}
	if (joystick_is_up())
	{
		joystick_clear_up();
		editor_interval_increment_interval_field(editor);
	}
	if (joystick_is_down())
	{
		joystick_clear_down();
		editor_interval_decrement_interval_field(editor);
	}
	if (joystick_is_pressed())
	{
		joystick_clear_pressed();
		editor_interval_click_field(menu, editor);
	}
}

void editor_interval_next_field(editor_interval_data_t* editor)
{
	switch(editor->current_field)
	{
		case interval_day: editor->current_field = interval_hour; break;
		case interval_hour: editor->current_field = interval_minute; break;
		case interval_minute: editor->current_field = interval_second; break;
		case interval_second: editor->current_field = interval_millisecond; break;
		case interval_millisecond: editor->current_field = interval_action_accept; break;
		case interval_action_accept: editor->current_field = interval_action_cancel; break;
		case interval_action_cancel: editor->current_field = interval_action_reset; break;
		case interval_action_reset: editor->current_field = interval_day; break;
		
		default: editor->current_field = interval_day; break;
	}
}

void editor_interval_previous_field(editor_interval_data_t* editor)
{
	switch(editor->current_field)
	{
		case interval_day: editor->current_field = interval_action_reset; break;
		case interval_hour: editor->current_field = interval_day; break;
		case interval_minute: editor->current_field = interval_hour; break;
		case interval_second: editor->current_field = interval_minute; break;
		case interval_millisecond: editor->current_field = interval_second; break;
		case interval_action_accept: editor->current_field = interval_millisecond; break;
		case interval_action_cancel: editor->current_field = interval_action_accept; break;
		case interval_action_reset: editor->current_field = interval_action_cancel; break;
		
		default: editor->current_field = interval_day; break;
	}
}

void editor_interval_increment_interval_field(editor_interval_data_t* editor)
{
	switch(editor->current_field)
	{
		case interval_day: increment_interval_date(editor); break;
		case interval_hour: increment_interval_hour(editor); break;
		case interval_minute: increment_interval_minute(editor); break;
		case interval_second: increment_interval_second(editor); break;
		case interval_millisecond: increment_interval_milliseconds(editor); break;
		
		default: break;
	}
}

void editor_interval_decrement_interval_field(editor_interval_data_t* editor)
{
	switch(editor->current_field)
	{
		case interval_day: decrement_interval_date(editor); break;
		case interval_hour: decrement_interval_hour(editor); break;
		case interval_minute: decrement_interval_minute(editor); break;
		case interval_second: decrement_interval_second(editor); break;
		case interval_millisecond: decrement_interval_milliseconds(editor); break;
		
		default: break;
	}
}

void editor_interval_click_field(menu_t* menu, editor_interval_data_t* editor)
{
	switch(editor->current_field)
	{
		case interval_action_accept:
		editor_interval_accept(menu, editor);
		break;
		case interval_action_cancel:
		editor_interval_cancel(menu, editor);
		break;
		case interval_action_reset:
		editor_interval_reset(menu, editor);
		break;
	}
}

void editor_interval_render(menu_t* menu)
{
	display_clear();
	editor_blink_update();
	editor_interval_render_title(menu);
	editor_interval_data_t* editor = (editor_interval_data_t*)menu->user_data;
	editor_interval_render_date(editor);
	editor_interval_render_time(editor);
	editor_interval_render_actions(editor);
}

void editor_interval_render_title(menu_t* menu)
{
	display_printf(20, "%s\n", editor_interval_get_title(menu));
}

void editor_interval_render_date(editor_interval_data_t* editor)
{
	display_printf(20, "Days: %.1i\n",
	editor->user_input.calendar_date.date
	);
}

void editor_interval_render_time(editor_interval_data_t* editor)
{
	display_printf(20, "Time: %.2i:%.2i:%.2i %.3ims",
	editor->user_input.calendar_date.hour,
	editor->user_input.calendar_date.minute,
	editor->user_input.calendar_date.second,
	editor->user_input.milliseconds
	);
}

void editor_interval_render_actions(editor_interval_data_t* editor)
{
	char accept = DISPLAY_SPACE;
	char cancel = DISPLAY_SPACE;
	char reset = DISPLAY_SPACE;
	switch(editor->current_field)
	{
		case interval_action_accept: accept = DISPLAY_ARROW_RIGHT; break;
		case interval_action_cancel: cancel = DISPLAY_ARROW_RIGHT; break;
		case interval_action_reset: reset = DISPLAY_ARROW_RIGHT; break;
	}
	
	
	display_printf(20, "%cOK %cCancel %cReset",
	accept,
	cancel,
	reset
	);
}

menu_t* generate_editor_interval(menu_t* parentMenu, const char* defaultTitle, editor_interval_data_t dataTemplate)
{
	menu_t* newMenu = menu_add_submenu(parentMenu, defaultTitle);
	newMenu->get_title = editor_interval_get_title;
	newMenu->tick = editor_interval_tick;
	free(newMenu->user_data);
	editor_interval_data_t* data = malloc(sizeof(editor_interval_data_t));
	data->current_field = dataTemplate.current_field;
	data->field_offset = dataTemplate.field_offset;
	data->initial_input = dataTemplate.initial_input;
	data->on_cancel = dataTemplate.on_cancel;
	data->on_completed = dataTemplate.on_completed;
	data->user_data = dataTemplate.user_data;
	data->user_input = dataTemplate.user_input;
	newMenu->user_data = (void*)data;
	return newMenu;
}

int increment_interval_date(editor_interval_data_t* editor)
{
	editor->user_input.calendar_date.date++;
	if(editor->user_input.calendar_date.date >= 7)
	{
		editor->user_input.calendar_date.date = 7;
	}
	return editor->user_input.calendar_date.date;
}

int increment_interval_hour(editor_interval_data_t* editor)
{
	editor->user_input.calendar_date.hour++;
	if(editor->user_input.calendar_date.hour > 23)
	{
		editor->user_input.calendar_date.hour = 23;
	}
	return editor->user_input.calendar_date.hour;
}

int increment_interval_minute(editor_interval_data_t* editor)
{
	editor->user_input.calendar_date.minute++;
	if(editor->user_input.calendar_date.minute > 59)
	{
		editor->user_input.calendar_date.minute = 59;
	}
	return editor->user_input.calendar_date.minute;
}

int increment_interval_second(editor_interval_data_t* editor)
{
	editor->user_input.calendar_date.second++;
	if(editor->user_input.calendar_date.second > 59)
	{
		editor->user_input.calendar_date.second = 59;
	}
	return editor->user_input.calendar_date.second;
}

int increment_interval_milliseconds(editor_interval_data_t* editor)
{
	editor->user_input.milliseconds++;
	if(editor->user_input.milliseconds > 999)
	{
		editor->user_input.milliseconds = 999;
	}
	return editor->user_input.milliseconds;
}

int decrement_interval_date(editor_interval_data_t* editor)
{
	if(editor->user_input.calendar_date.date > 0)
	{
		editor->user_input.calendar_date.date--;
	}
	return editor->user_input.calendar_date.date;
}

int decrement_interval_hour(editor_interval_data_t* editor)
{
	if(editor->user_input.calendar_date.hour > 0)
	{
		editor->user_input.calendar_date.hour--;
	}
	return editor->user_input.calendar_date.hour;
}

int decrement_interval_minute(editor_interval_data_t* editor)
{
	if(editor->user_input.calendar_date.minute > 0)
	{
		editor->user_input.calendar_date.minute--;
	}
	return editor->user_input.calendar_date.minute;
}

int decrement_interval_second(editor_interval_data_t* editor)
{
	if(editor->user_input.calendar_date.second > 0)
	{
		editor->user_input.calendar_date.second--;
	}
	return editor->user_input.calendar_date.second;
}

int decrement_interval_milliseconds(editor_interval_data_t* editor)
{
	if(editor->user_input.milliseconds > 0)
	{
		editor->user_input.milliseconds--;
	}
	return editor->user_input.milliseconds;
}

void editor_interval_accept(menu_t* menu, editor_interval_data_t* editor)
{
	menu_pop_safe();
	editor->on_completed(menu, editor);
}

void editor_interval_cancel(menu_t* menu, editor_interval_data_t* editor)
{
	menu_pop_safe();
	editor->on_cancel(menu, editor);
}

void editor_interval_reset(menu_t* menu, editor_interval_data_t* editor)
{
	editor->user_input = editor->initial_input;
}

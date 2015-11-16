#include "modules/menus/editor_timestamp.h"
//C standard library
//ASF
//Modules
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/menus/menu_default.h"

void editor_timestamp_update(editor_timestamp_data_t* editor);
void editor_timestamp_next_field(editor_timestamp_data_t* editor);
void editor_timestamp_previous_field(editor_timestamp_data_t* editor);
void editor_timestamp_increment_field(editor_timestamp_data_t* editor);
void editor_timestamp_decrement_field(editor_timestamp_data_t* editor);
void editor_timestamp_click_field(editor_timestamp_data_t* editor);

void editor_timestamp_render(menu_t* menu);
void editor_timestamp_render_title(menu_t* menu);
void editor_timestamp_render_date(editor_timestamp_data_t* editor);
void editor_timestamp_render_time(editor_timestamp_data_t* editor);
void editor_timestamp_render_actions(editor_timestamp_data_t* editor);

char* editor_timestamp_get_title(menu_t* menu)
{
	return menu_default_get_title(menu);
}

void editor_timestamp_tick(menu_t* menu)
{
	editor_timestamp_data_t* editor = (editor_timestamp_data_t*)menu->user_data;
	editor_timestamp_update(editor);
	editor_timestamp_render(menu);
}

void editor_timestamp_update(editor_timestamp_data_t* editor)
{
	if (joystick_is_left())
	{
		joystick_clear_left();
		editor_timestamp_next_field(editor);
	}
	if (joystick_is_right())
	{
		joystick_clear_right();
		editor_timestamp_previous_field(editor);
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
		editor_timestamp_click_field(editor);
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
	assert(!"The method or operation is not implemented.");
}

void editor_timestamp_decrement_field(editor_timestamp_data_t* editor)
{
	assert(!"The method or operation is not implemented.");
}

void editor_timestamp_click_field(editor_timestamp_data_t* editor)
{
	switch(editor->current_field)
	{
		case action_accept:
			//editor_timestamp_accept(editor);
		break;
		case action_cancel:
			//editor_timestamp_cancel(editor);
		break;
		case action_reset:
			//editor_timestamp_reset(editor);
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
		editor->user_input.year,
		editor->user_input.month,
		editor->user_input.date
	);
}

void editor_timestamp_render_time(editor_timestamp_data_t* editor)
{
	display_printf(20, "Time: %.2i:%.2i:%.2i %.3ims",
		editor->user_input.hour,
		editor->user_input.minute,
		editor->user_input.second
		/* editor->user_input.millisecond */
	);
}

void editor_timestamp_render_actions(editor_timestamp_data_t* editor)
{
	display_printf(20, "%cOK %cReset %cCancel",
		DISPLAY_ARROW_LEFT,
		DISPLAY_SPACE,
		DISPLAY_SPACE
	);
}

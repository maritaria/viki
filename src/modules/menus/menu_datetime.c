#include "modules/menus/menu_alert.h"
//C standard library
//ASF
//Modules
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/config.h"
#include "modules/menus/editor_timestamp.h"

timeswitch_config_t holder = {0};

void datetime_on_load(menu_t* menu, editor_timestamp_data_t* data);
void datetime_canceled(menu_t* menu, editor_timestamp_data_t* data);
void datetime_completed(menu_t* menu, editor_timestamp_data_t* data);

menu_t* generate_datetime_menu(menu_t* parentMenu)
{
	editor_timestamp_data_t data_timestamp = {0};
	data_timestamp.current_field = date_year;
	data_timestamp.on_cancel = datetime_canceled;
	data_timestamp.on_completed = datetime_completed;
	data_timestamp.on_load = datetime_on_load;
	data_timestamp.user_data = &holder;
	generate_editor_timestamp(parentMenu, "Edit time", data_timestamp);
}

void datetime_on_load(menu_t* menu, editor_timestamp_data_t* data)
{
	holder.timestamp = datetime_get_milliseconds();
	timeswitch_config_t* config = data->user_data;
	
	calendar_timestamp_to_date(config->timestamp / 1000, &data->user_input.calendar_date);
	data->user_input.milliseconds = config->timestamp % 1000;
	
	calendar_timestamp_to_date(config->timestamp / 1000, &data->initial_input.calendar_date);
	data->initial_input.milliseconds = config->timestamp % 1000;
}

void datetime_canceled(menu_t* menu, editor_timestamp_data_t* data)
{
	
}

void datetime_completed(menu_t* menu, editor_timestamp_data_t* data)
{
	timeswitch_config_t* config = data->user_data;
	uint64_t timestamp = calendar_date_to_timestamp(&data->user_input.calendar_date);
	timestamp *= 1000;
	timestamp += data->user_input.milliseconds;
	datetime_set_time(timestamp);
}
#include "modules/datetime.h"
//Standard C
#include <string.h>
//ASF
#include <asf.h>
#include <calendar.h>
//Custom
#include "modules/clock.h"
#include "modules/config.h"

uint16_t milliseconds = 0;
struct calendar_date current_time = {0};

void datetime_init(void)
{
	//TODO: Load timestamp from flash :D
	calendar_timestamp_to_date(0, &current_time);
}

void datetime_get_time(struct calendar_date* date)
{
	memmove(date, &current_time, sizeof(struct calendar_date));
}

uint16_t datetime_get_milliseconds()
{
	return milliseconds;
}

void datetime_increment_by_millisecond()
{
	milliseconds++;
	if (milliseconds >= 1000)
	{
		milliseconds -= 1000;
		LED_Toggle(LED2);
		calendar_add_second_to_date(&current_time);
	}
	
}

void datetime_tick()
{
	//TODO: Save timestamp to flash :D
}
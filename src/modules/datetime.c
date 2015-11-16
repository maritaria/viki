#include "modules/datetime.h"
//Standard C
#include <string.h>
//ASF
#include <asf.h>
#include <calendar.h>
//Custom
#include "modules/clock.h"
#include "modules/config.h"

uint16_t seconds = 0;
uint16_t milliseconds = 0;

void datetime_init(void)
{
	//TODO: Load timestamp from flash :D
}

uint16_t datetime_get_seconds()
{
	return seconds;
}

uint16_t datetime_get_milliseconds()
{
	return milliseconds;
}

void datetime_set_time(uint16_t new_seconds, uint16_t new_milliseconds)
{
	seconds = new_seconds;
	milliseconds = new_milliseconds;
}

void datetime_increment_millisecond()
{
	milliseconds++;
	if (milliseconds >= 1000)
	{
		milliseconds -= 1000;
		LED_Toggle(LED2);
		seconds++;
	}
}
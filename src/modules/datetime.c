#include "modules/datetime.h"
//Standard C
#include <string.h>
//ASF
#include <asf.h>
#include <calendar.h>
//Custom
#include "modules/clock.h"
#include "modules/config.h"

uint32_t milliseconds = 0;

void datetime_init(void)
{
	//TODO: Load timestamp from flash :D
}

uint32_t datetime_get_milliseconds()
{
	return milliseconds;
}

void datetime_set_time(uint32_t new_milliseconds)
{
	milliseconds = new_milliseconds;
}

void datetime_increment_millisecond()
{
	milliseconds++;
}
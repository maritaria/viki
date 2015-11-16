#include "timeswitches.h"
//Standard C
//ASF
//Custom
#include "modules/config.h"
#include "modules/clock.h"
#include "modules/datetime.h"

void timeswitches_init()
{
	timeswitch_config_t* sw = &CONFIG.timers[0];
	sw->enabled = true;
	sw->timestamp = 10800;
	sw->repeat_count = -1;
	sw->repeat_interval = 1000;
	sw->behaviour = toggle;
}

void timeswitches_update_specific(timeswitch_config_t* timeswitch);
bool should_enable_switch(timeswitch_config_t* timeswitch);
void apply_switch(timeswitch_config_t* timeswitch);
void update_interval(timeswitch_config_t* timeswitch);

void timeswitches_update()
{
	for (int i = 0; i < TIMER_CONFIG_COUNT; i++)
	{
		timeswitches_update_specific(&CONFIG.timers[i]);
	}
}

void timeswitches_update_specific(timeswitch_config_t* timeswitch)
{
	if (should_enable_switch(timeswitch))
	{
		apply_switch(timeswitch);
		update_interval(timeswitch);
	}
}

bool should_enable_switch(timeswitch_config_t* timeswitch)
{
	return timeswitch->enabled && (timeswitch->timestamp == datetime_get_milliseconds());
}

void apply_switch(timeswitch_config_t* timeswitch)
{
	switch(timeswitch->behaviour)
	{
		case on: LED_On(LED3); break;
		case off: LED_Off(LED3); break;
		case toggle: LED_Toggle(LED3); break;
	}
}

void update_interval(timeswitch_config_t* timeswitch)
{
	if(timeswitch->repeat_count != 0)
	{
		timeswitch->timestamp += timeswitch->repeat_interval;
		if(timeswitch->repeat_count > 0)
		{
			timeswitch->repeat_count --;	
		}
	}
}
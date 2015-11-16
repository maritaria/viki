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
	sw->timestamp = 30;
	sw->timestamp_milliseconds = 800;
}
void timeswitches_update_specific(timeswitch_config_t timeswitch);

void timeswitches_update()
{
	for (int i = 0; i < TIMER_CONFIG_COUNT; i++)
	{
		timeswitches_update_specific(CONFIG.timers[i]);
	}
}

bool should_enable_switch(timeswitch_config_t timeswitch);
void apply_switch(timeswitch_config_t timeswitch);

void timeswitches_update_specific(timeswitch_config_t timeswitch)
{
	if (should_enable_switch(timeswitch))
	{
		apply_switch(timeswitch);
	}
}

bool should_enable_switch(timeswitch_config_t timeswitch)
{
	return timeswitch.enabled && (timeswitch.timestamp == datetime_get_seconds()) && (timeswitch.timestamp_milliseconds == datetime_get_milliseconds());
}

void apply_switch(timeswitch_config_t timeswitch)
{
	LED_Toggle(LED3);
}
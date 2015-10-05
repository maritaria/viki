#include "modules/config.h"

#include "modules/timeswitches.h"
#include "modules/joystick.h"

timeswitch_config_t timers[4] = {};
input_t input_flags = {};

void config_init_timers(timeswitch_config_t[]);
void config_init_timer(timeswitch_config_t*, int i);

bool config_init(void)
{
	CONFIG.com_enabled = false;
	config_init_timers(CONFIG.timers);
	return true;
}

void config_init_timers(timeswitch_config_t timers[])
{
	for (int i = 0; i < TIMER_CONFIG_COUNT; i ++)
	{
		config_init_timer(&timers[i], i);
	}
}

void config_init_timer(timeswitch_config_t* timer, int i)
{
	timer->timestamp = i;
	timer->enabled = true;
	timer->repeat_interval = 15;
	timer->repeat_count = 1;
	timer->behaviour = toggle;
}
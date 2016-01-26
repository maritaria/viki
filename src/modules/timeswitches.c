#include "timeswitches.h"
//Standard C
//ASF
//Custom
#include "modules/config.h"
#include "modules/clock.h"
#include "modules/datetime.h"

void timeswitches_init()
{
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
	switch(timeswitch->output)
	{
		case 1: 
		{
			switch(timeswitch->behaviour)
			{
				case on: LED_On(LED0); break;
				case off: LED_Off(LED0); break;
				case toggle: LED_Toggle(LED0); break;
			}
			break;
		}
		
		case 2:
		{
			switch(timeswitch->behaviour)
			{
				case on: LED_On(LED1); break;
				case off: LED_Off(LED1); break;
				case toggle: LED_Toggle(LED1); break;
			}
			break;
		}
		
		case 3:
		{
			switch(timeswitch->behaviour)
			{
				case on: LED_On(LED2); break;
				case off: LED_Off(LED2); break;
				case toggle: LED_Toggle(LED2); break;
			}
			break;
		}
		
		case 4:
		{
			switch(timeswitch->behaviour)
			{
				case on: LED_On(LED3); break;
				case off: LED_Off(LED3); break;
				case toggle: LED_Toggle(LED3); break;
			}
			break;
		}
		
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
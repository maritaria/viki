/*
 * module_config.c
 *
 * Created: 7-9-2015 9:02:39
 *  Author: Eigenaar
 */

#include "modules/config.h"

core_config_t myConfig;
timer_config_t timers[4];

void config_initTimer(timer_config_t*);

result config_init(void)
{
	myConfig.com_enabled = false;
	for (int i = 0; i < 4; i ++)
	{
		timer_config_t* pTimer = &timers[i];
		config_initTimer(pTimer);
		myConfig.config1 = pTimer;
	}
	return success;
}

void config_initTimer(timer_config_t* myTimer)
{
	myTimer->timestamp = 0;
	myTimer->interval = 15;
	myTimer->enabled = true;
	myTimer->repeatCount = 1;
	myTimer->mode = toggle;
}

core_config_t* config_get(void)
{
	return &myConfig;
}

result config_save(void)
{
	return failure;
}

result config_load(void)
{
	return failure;
}

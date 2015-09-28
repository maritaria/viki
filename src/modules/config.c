#include "modules/config.h"

timer_config_t timers[4] = {};
input_flags_t input_flags = {};

void config_init_timers(timer_config_t[]);
void config_init_timer(timer_config_t*, int i);
void config_init_input_flags(input_flags_t*);

result config_init(void)
{
	config_instance.com_enabled = false;
	config_init_timers(config_instance.timers);
	config_init_input_flags(&config_instance.input_flags);
	return success;
}

void config_init_timers(timer_config_t timers[])
{
	for (int i = 0; i < TIMER_CONFIG_COUNT; i ++)
	{
		config_init_timer(&timers[i], i);
	}
}

void config_init_timer(timer_config_t* timer, int i)
{
	timer->timestamp = i;
	timer->interval = 15;
	timer->enabled = true;
	timer->repeatCount = 1;
	timer->mode = toggle;
}

void config_init_input_flags(input_flags_t* input_flags)
{
	input_flags->joystick_up = false;
	input_flags->joystick_down = false;
	input_flags->joystick_left = false;
	input_flags->joystick_right = false;
	input_flags->joystick_push = false;
	input_flags->button0 = false;
	input_flags->button1 = false;
	input_flags->button2 = false;
}

global_config_t* config_get(void)
{
	return &config_instance;
}

result config_save(void)
{
	return failure;
}

result config_load(void)
{
	return failure;
}

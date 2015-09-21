/*
 * module_config.h
 *
 * Created: 7-9-2015 9:02:53
 *  Author: Eigenaar
 */ 


#ifndef MODULES__CONFIG_H_
#define MODULES__CONFIG_H_


#include <asf.h>
#include "defines.h"

DEFINE_TYPE(enum, timer_mode) {
	turnOn,
	turnOff,
	toggle
};

DEFINE_TYPE(struct, timer_config_t) {
	int timestamp;
	int interval;
	bool enabled;
	int repeatCount;
	timer_mode mode;
};

DEFINE_TYPE(struct, input_flags_t) {
	bool joystick_up;
	bool joystick_down;
	bool joystick_left;
	bool joystick_right;
	bool joystick_push;
	bool button0;
	bool button1;
	bool button2;
};

#define TIMER_CONFIG_COUNT 4
DEFINE_TYPE(struct, global_config_t) {
	timer_config_t timers[TIMER_CONFIG_COUNT];
	input_flags_t input_flags;
	bool com_enabled;
};

result config_init(void);
global_config_t* config_get(void);
result config_save(void);
result config_load(void);


#endif /* MODULES__CONFIG_H_ */
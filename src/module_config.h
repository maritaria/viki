/*
 * module_config.h
 *
 * Created: 7-9-2015 9:02:53
 *  Author: Eigenaar
 */ 


#ifndef MODULE_CONFIG_H_
#define MODULE_CONFIG_H_

#include <asf.h>
#include "defines.h"

typedef enum timer_mode timer_mode;
typedef struct timer_config_t timer_config_t;
typedef struct core_config_t core_config_t;

enum timer_mode {
	turnOn,
	turnOff,
	toggle
};

struct timer_config_t {
	int timestamp;
	int interval;
	bool enabled;
	int repeatCount;
	timer_mode mode;
};

struct core_config_t {
	timer_config_t* config1;
	timer_config_t* config2;
	timer_config_t* config3;
	timer_config_t* config4;
	bool com_enabled;
};

result config_init(void);
core_config_t* config_get(void);
result config_save(void);
result config_load(void);

#endif /* MODULE_CONFIG_H_ */
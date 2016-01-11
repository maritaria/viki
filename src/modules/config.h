#ifndef MODULES__CONFIG_H_
#define MODULES__CONFIG_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/serial.h"
#include "modules/timeswitches.h"
#define TIMER_CONFIG_COUNT (4)

DEFINE_TYPE(struct, config_t) {
	timeswitch_config_t timers[TIMER_CONFIG_COUNT];
	input_t input;
	bool com_enabled;
};

bool config_init(void);

volatile config_t config_instance;
#define CONFIG (config_instance)

#endif /* MODULES__CONFIG_H_ */
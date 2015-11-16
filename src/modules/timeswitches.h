#ifndef TIMESWITCHES_H_
#define TIMESWITCHES_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"

DEFINE_TYPE(enum, timeswitch_behaviour) { on, off, toggle };

#define TIMESWITCH_INFINITE_REPEAT (0)

DEFINE_TYPE(struct, timeswitch_config_t) {
	bool enabled;
	uint16_t timestamp;
	uint8_t timestamp_milliseconds;
	int repeat_interval;
	int repeat_count;
	timeswitch_behaviour behaviour;
};

void timeswitches_init(void);
void timeswitches_update(void);

#endif /* TIMESWITCHES_H_ */
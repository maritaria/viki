#ifndef TIMESWITCHES_H_
#define TIMESWITCHES_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"

DEFINE_TYPE(enum, timeswitch_behaviour) { on = 0, off = 1, toggle = 2 };

#define TIMESWITCH_INFINITE_REPEAT (0)

DEFINE_TYPE(struct, timeswitch_config_t) {
	bool enabled;
	uint64_t timestamp;
	uint32_t repeat_interval;
	uint16_t repeat_count;
	timeswitch_behaviour behaviour;
	uint16_t output;
};

void timeswitches_init(void);
void timeswitches_update(void);

#endif /* TIMESWITCHES_H_ */
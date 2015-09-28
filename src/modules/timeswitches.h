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
	int timestamp;
	int repeat_interval;
	int repeat_count;
	timeswitch_behaviour behaviour;
};


#endif /* TIMESWITCHES_H_ */
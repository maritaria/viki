#ifndef MODULES__SYSTEM_CLOCK_H_
#define MODULES__SYSTEM_CLOCK_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"

void sysclock_init(void);
int rtcSec(void);
void sysclock_start_timer(int, int);

#endif /* MODULES__SYSTEM_CLOCK_H_ */
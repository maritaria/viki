#ifndef MODULES__DATETIME_H_
#define MODULES__DATETIME_H_

//Standard C
//ASF
#include <asf.h>
#include <calendar.h>
//Custom
#include "macros.h"

void datetime_init(void);
uint32_t datetime_get_milliseconds();
void datetime_set_time(uint32_t new_milliseconds);
void datetime_increment_millisecond(void);
void datetime_tick(void);


#endif /* MODULES__DATETIME_H_ */
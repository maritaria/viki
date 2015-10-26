#ifndef MODULES__DATETIME_H_
#define MODULES__DATETIME_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"

DEFINE_TYPE(struct, datetime_t) {
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	int millisecond;
};

void datetime_init(void);
void datetime_increment_by_ms(int elapsed_ms);
void datetime_current_time(datetime_t* date);


#endif /* MODULES__DATETIME_H_ */
#ifndef MODULES__DATETIME_H_
#define MODULES__DATETIME_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"

DEFINE_TYPE(struct, datetime_t){
	int ms;
	int s;
	int m;
	int h;
	int d;
	int month;
	int y;
};

void datetime_init(void);
void datetime_increment_by_ms(int elapsed_ms);
void datetime_current_time(datetime_t* date);


#endif /* MODULES__DATETIME_H_ */
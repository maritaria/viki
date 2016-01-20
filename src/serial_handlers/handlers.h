#ifndef MODULES__SERIAL_HANDLERS__HANDLERS_H_
#define MODULES__SERIAL_HANDLERS__HANDLERS_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"
#include "modules/serial.h"

void serial_handler_echo(serial_args_t args);
void serial_handler_gettime(serial_args_t args);
void serial_handler_settime(serial_args_t args);
void serial_handler_getalarm(serial_args_t args);
void serial_handler_setalarm(serial_args_t args);

#endif /* MODULES__SERIAL_HANDLERS__HANDLERS_H_ */
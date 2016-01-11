#ifndef MODULES__SERIAL_HANDLERS__ECHO_H_
#define MODULES__SERIAL_HANDLERS__ECHO_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"

void serial_handler_echo(char identifier, char type, char* body, int body_length);

#endif /* MODULES__SERIAL_HANDLERS__ECHO_H_ */
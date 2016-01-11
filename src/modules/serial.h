#ifndef MODULES__SERIAL_H_
#define MODULES__SERIAL_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"

bool serial_init(void);
bool serial_cdc_enable(uint8_t port);
void serial_cdc_disable(uint8_t port);
void serial_cdc_rx_notify(uint8_t port);
char serial_calculate_checksum(char* body, int body_length);
void serial_cdc_dtr_changed(uint8_t port, bool enabled);
void serial_send_packet(char identifier, char type, char* body, int body_length);

#endif /* MODULES__SERIAL_H_ */
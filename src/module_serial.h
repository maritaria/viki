/*
 * module_serial.h
 *
 * Created: 1-9-2015 11:01:52
 *  Author: Eigenaar
 */ 


#ifndef MODULE_SERIAL_H_
#define MODULE_SERIAL_H_

#include "defines.h"
#include <asf.h>

result serial_init(void);

bool serial_cdc_enable(uint8_t port);
void serial_cdc_disable(uint8_t port);
void serial_cdc_rx_notify(uint8_t port);
void serial_cdc_dtr_changed(uint8_t port, bool enabled);


#endif /* MODULE_SERIAL_H_ */
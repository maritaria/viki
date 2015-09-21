/*
 * module_serial.h
 *
 * Created: 1-9-2015 11:01:52
 *  Author: Eigenaar
 */ 


#ifndef MODULES__DISPLAY_H_
#define MODULES__DISPLAY_H_


#include "defines.h"
#include <asf.h>

#define DISPLAY_WIDTH (20)
#define DISPLAY_HEIGHT (4)
#define DISPLAY_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT)

result display_init(void);
void display_update(void);

void display_set_cursor(bool enabled);
bool display_get_cursor(void);

void display_set_pos(unsigned char x, unsigned char y);
void display_get_pos(unsigned char* x, unsigned char* y);

void display_clear(void);
void display_write(const char* text);
void display_write_char(char character);

#endif /* MODULES__DISPLAY_H_ */
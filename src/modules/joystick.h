#ifndef MODULES__JOYSTICK_H_
#define MODULES__JOYSTICK_H_

//Standard C
//ASF
#include <asf.h>
#include <compiler.h>
#include <board.h>
#include <gpio.h>
//Custom
#include "macros.h"

DEFINE_TYPE(struct, input_t) {
	bool joystick_up;
	bool joystick_down;
	bool joystick_left;
	bool joystick_right;
	bool joystick_pressed;
	bool button0;
	bool button1;
	bool button2;
};

bool joystick_init(void);
bool joystick_is_up(void);
bool joystick_is_down(void);
bool joystick_is_left(void);
bool joystick_is_down(void);
bool joystick_is_pressed(void);

__always_inline static int joystick_is_up_raw(void)
{
	return (gpio_get_pin_value(GPIO_JOYSTICK_UP)) == GPIO_JOYSTICK_UP_PRESSED;
}

__always_inline static int joystick_is_down_raw(void)
{
	return (gpio_get_pin_value(GPIO_JOYSTICK_DOWN)) == GPIO_JOYSTICK_DOWN_PRESSED;
}

__always_inline static int joystick_is_left_raw(void)
{
	return (gpio_get_pin_value(GPIO_JOYSTICK_LEFT)) == GPIO_JOYSTICK_LEFT_PRESSED;
}

__always_inline static int joystick_is_right_raw(void)
{
	return (gpio_get_pin_value(GPIO_JOYSTICK_RIGHT)) == GPIO_JOYSTICK_RIGHT_PRESSED;
}

__always_inline static int joystick_is_pressed_raw(void)
{
	return (gpio_get_pin_value(GPIO_JOYSTICK_PUSH)) == GPIO_JOYSTICK_PUSH_PRESSED;
}

#endif /* MODULES__JOYSTICK_H_ */
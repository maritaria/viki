/*
 * input.c
 *
 * Created: 15-9-2015 10:40:02
 *  Author: Eigenaar
 */ 

#include "input.h"

#include <asf.h>
#include <evk1100.h>
#include "config.h"

#if __GNUC__
__attribute__((__interrupt__))
#elif __ICCAVR32__
#pragma handler = AVR32_GPIO_IRQ_0, AVR32_INTC_INT3
__interrupt
#endif
void input_interrupt_callback(void);

result input_init()
{
	//Enable interrupts
	gpio_enable_pin_interrupt(GPIO_JOYSTICK_UP , GPIO_PIN_CHANGE);
	gpio_enable_pin_interrupt(GPIO_JOYSTICK_DOWN , GPIO_PIN_CHANGE);
	gpio_enable_pin_interrupt(GPIO_JOYSTICK_RIGHT , GPIO_PIN_CHANGE);
	gpio_enable_pin_interrupt(GPIO_JOYSTICK_LEFT , GPIO_PIN_CHANGE);
	gpio_enable_pin_interrupt(GPIO_JOYSTICK_PUSH , GPIO_PIN_CHANGE);
	//Register handlers
	Disable_global_interrupt();
	INTC_register_interrupt((__int_handler)&input_interrupt_callback, AVR32_GPIO_IRQ_0 + (GPIO_JOYSTICK_UP / 8), AVR32_INTC_INT3);
	INTC_register_interrupt((__int_handler)&input_interrupt_callback, AVR32_GPIO_IRQ_0 + (GPIO_JOYSTICK_PUSH / 8), AVR32_INTC_INT3);
	Enable_global_interrupt();
	return failure;
}

#if __GNUC__
__attribute__((__interrupt__))
#elif __ICCAVR32__
#pragma handler = AVR32_GPIO_IRQ_0, AVR32_INTC_INT3
__interrupt
#endif
void input_interrupt_callback(void)
{
	if (gpio_get_pin_interrupt_flag(GPIO_JOYSTICK_UP))
	{
		
		gpio_clear_pin_interrupt_flag(GPIO_JOYSTICK_UP);
	}
}

void input_process(void)
{
	
}
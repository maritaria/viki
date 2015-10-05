#include "joystick.h"
//Standard C
//ASF
//Custom
#include "modules/config.h"

INTERRUPT_FUNCTION(joystick_interrupt_callback);

volatile bool joystick_flags_up = false;
volatile bool joystick_flags_down = false;
volatile bool joystick_flags_left = false;
volatile bool joystick_flags_right = false;
volatile bool joystick_flags_pressed = false;

bool joystick_init()
{
	//Enable interrupts
	gpio_enable_pin_interrupt(GPIO_JOYSTICK_UP , GPIO_PIN_CHANGE);
	gpio_enable_pin_interrupt(GPIO_JOYSTICK_DOWN , GPIO_PIN_CHANGE);
	gpio_enable_pin_interrupt(GPIO_JOYSTICK_RIGHT , GPIO_PIN_CHANGE);
	gpio_enable_pin_interrupt(GPIO_JOYSTICK_LEFT , GPIO_PIN_CHANGE);
	gpio_enable_pin_interrupt(GPIO_JOYSTICK_PUSH , GPIO_PIN_CHANGE);
	//Register handlers
	Disable_global_interrupt();
	INTC_register_interrupt((__int_handler)&joystick_interrupt_callback, AVR32_GPIO_IRQ_0 + (GPIO_JOYSTICK_LEFT / 8), AVR32_INTC_INT1);
	INTC_register_interrupt((__int_handler)&joystick_interrupt_callback, AVR32_GPIO_IRQ_0 + (GPIO_JOYSTICK_RIGHT / 8), AVR32_INTC_INT1);
	INTC_register_interrupt((__int_handler)&joystick_interrupt_callback, AVR32_GPIO_IRQ_0 + (GPIO_JOYSTICK_UP / 8), AVR32_INTC_INT1);
	INTC_register_interrupt((__int_handler)&joystick_interrupt_callback, AVR32_GPIO_IRQ_0 + (GPIO_JOYSTICK_DOWN / 8), AVR32_INTC_INT1);
	INTC_register_interrupt((__int_handler)&joystick_interrupt_callback, AVR32_GPIO_IRQ_0 + (GPIO_JOYSTICK_PUSH / 8), AVR32_INTC_INT1);
	//INTC_register_interrupt((__int_handler)&joystick_interrupt_callback, AVR32_GPIO_IRQ_0 + (GPIO_JOYSTICK_PUSH / 8), AVR32_INTC_INT3);
	Enable_global_interrupt();
	//Clear flags
	joystick_clear();
	return true;
}

static void joystick_interrupt_callback(void)
{
	if (gpio_get_pin_interrupt_flag(GPIO_JOYSTICK_LEFT))
	{
		CONFIG.input.joystick_left = joystick_is_left_raw();
		gpio_clear_pin_interrupt_flag(GPIO_JOYSTICK_LEFT);
	}
	if (gpio_get_pin_interrupt_flag(GPIO_JOYSTICK_RIGHT))
	{
		CONFIG.input.joystick_right = joystick_is_right_raw();
		gpio_clear_pin_interrupt_flag(GPIO_JOYSTICK_RIGHT);
	}
	if (gpio_get_pin_interrupt_flag(GPIO_JOYSTICK_UP))
	{
		CONFIG.input.joystick_up = joystick_is_up_raw();
		gpio_clear_pin_interrupt_flag(GPIO_JOYSTICK_UP);
	}
	if (gpio_get_pin_interrupt_flag(GPIO_JOYSTICK_DOWN))
	{
		CONFIG.input.joystick_down = joystick_is_down_raw();
		gpio_clear_pin_interrupt_flag(GPIO_JOYSTICK_DOWN);
	}
	if (gpio_get_pin_interrupt_flag(GPIO_JOYSTICK_PUSH))
	{
		CONFIG.input.joystick_pressed = joystick_is_pressed_raw();
		gpio_clear_pin_interrupt_flag(GPIO_JOYSTICK_PUSH);
	}
}

bool joystick_is_up(void)
{
	return CONFIG.input.joystick_up;
}

bool joystick_is_down(void)
{
	return CONFIG.input.joystick_down;
}

bool joystick_is_left(void)
{
	return CONFIG.input.joystick_left;
}

bool joystick_is_right(void)
{
	return CONFIG.input.joystick_right;
}

bool joystick_is_pressed(void)
{
	return CONFIG.input.joystick_pressed;
}

void joystick_clear()
{
	joystick_clear_left();
	joystick_clear_right();
	joystick_clear_up();
	joystick_clear_down();
	joystick_clear_pressed();
}

void joystick_clear_left()
{
	CONFIG.input.joystick_left = false;
}

void joystick_clear_right()
{
	CONFIG.input.joystick_right = false;
}

void joystick_clear_up()
{
	CONFIG.input.joystick_up = false;
}

void joystick_clear_down()
{
	CONFIG.input.joystick_down = false;
}

void joystick_clear_pressed()
{
	CONFIG.input.joystick_pressed = false;
}
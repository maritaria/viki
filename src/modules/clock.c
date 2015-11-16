#include "modules/clock.h"
//Standard C
#include <string.h>
//ASF
#include <asf.h>
//Custom
#include "modules/config.h"
#include "modules/datetime.h"

volatile float behind = 0;
static volatile float potvalue = 0;

INTERRUPT_FUNCTION(rtc_irq);
static void rtc_hack(void);

void clock_init(void)
{
	Disable_global_interrupt();
	INTC_register_interrupt(&rtc_irq, AVR32_RTC_IRQ, AVR32_INTC_INT0);
	if (!rtc_init(&AVR32_RTC, RTC_OSC_32KHZ, 0))
	{
		while(1);
	}
	rtc_set_top_value(&AVR32_RTC, 15);
	rtc_enable_interrupt(&AVR32_RTC);
	rtc_enable(&AVR32_RTC);
	Enable_global_interrupt();
}

void clock_update()
{
	uint16_t raw = 639;
	potvalue = (float)raw / (float)0x3FF;
	potvalue -= 0.5;
	potvalue *= 4;
	potvalue /= 10000;
}

static void rtc_irq()
{
	rtc_clear_interrupt(&AVR32_RTC);
	rtc_hack();
	datetime_increment_millisecond();
	timeswitches_update();
	LED_Toggle(LED1);
}

static void rtc_hack()
{
	double delta = 0.3837 + potvalue;
	behind += delta;
	if (behind >= 1)
	{
		behind -= 1;
		(&AVR32_RTC)->top = 16;
	}
	else
	{
		(&AVR32_RTC)->top = 15;
	}
	return;
}
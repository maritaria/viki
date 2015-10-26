#include "modules/clock.h"
//Standard C
//ASF
#include <asf.h>
//Custom
#include "modules/config.h"

#define CLOCK_HACK_COUNT (7)
const int clock_hack[CLOCK_HACK_COUNT] = {15,16,15,16,15,16,15};
volatile int clock_hack_index = 0;

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
	rtc_set_top_value(&AVR32_RTC, clock_hack[0]);
	rtc_enable_interrupt(&AVR32_RTC);
	rtc_enable(&AVR32_RTC);
	Enable_global_interrupt();
}

static void rtc_irq()
{
	rtc_clear_interrupt(&AVR32_RTC);
	rtc_hack();
}

static void rtc_hack()
{
	(&AVR32_RTC)->top = clock_hack[clock_hack_index];
	clock_hack_index++;
	if(clock_hack_index >= CLOCK_HACK_COUNT)
	{
		clock_hack_index = 0;
	}
}
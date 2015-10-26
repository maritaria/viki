#include "modules/system_clock.h"
//Standard C
//ASF
#include <asf.h>
//Custom
#include "modules/config.h"

volatile static int rtc_int = 0;
volatile static uint32_t timer = 0;

static int time_setting;
static int time_remaining;
static int mscounter = 0;

#define CLOCK_HACK_COUNT (7)
const int clock_hack[CLOCK_HACK_COUNT] = {15,16,15,16,15,16,15};
volatile int clock_hack_index = 0;

INTERRUPT_FUNCTION(rtc_irq); 
bool lowtime = false;
void sysclock_init(void)
{
	Disable_global_interrupt();
	
	INTC_register_interrupt(&rtc_irq, AVR32_RTC_IRQ, AVR32_INTC_INT0);

	if (!rtc_init(&AVR32_RTC, RTC_OSC_32KHZ, 0))
	{
		//usart_write_line(&AVR32_USART0, "Error initializing the RTC\r\n");
		while(1);
	}

	// Set top value to 0 to generate an interrupt every tick
	rtc_set_top_value(&AVR32_RTC, 15);
	// Enable the interrupts
	rtc_enable_interrupt(&AVR32_RTC);
	// Enable the RTC
	rtc_enable(&AVR32_RTC);

	Enable_global_interrupt();
}

static void rtc_irq()
{
	rtc_clear_interrupt(&AVR32_RTC);
	rtc_int ++;
	if(rtc_int >= 1)
	{
		LED_Toggle(LED1);
		(&AVR32_RTC)->top = clock_hack[clock_hack_index];
		clock_hack_index++;
		if(clock_hack_index >= CLOCK_HACK_COUNT)
			clock_hack_index = 0;
		rtc_int = 0;
	}
}

int rtcSec()
{
}


void sysclock_start_timer (int time_setting, int sec)
{
	time_remaining = (time_setting - sec) * 1000;
	timer = 0;
}

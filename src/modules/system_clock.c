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

INTERRUPT_FUNCTION(rtc_irq); 

void sysclock_init(void)
{
	Disable_global_interrupt();
	
	INTC_register_interrupt(&rtc_irq, AVR32_RTC_IRQ, AVR32_INTC_INT0);

	if (!rtc_init(&AVR32_RTC, RTC_OSC_32KHZ, RTC_PSEL_32KHZ_1HZ))
	{
		//usart_write_line(&AVR32_USART0, "Error initializing the RTC\r\n");
		while(1);
	}

	// Set top value to 0 to generate an interrupt every seconds
	rtc_set_top_value(&AVR32_RTC, 0);
	// Enable the interrupts
	rtc_enable_interrupt(&AVR32_RTC);
	// Enable the RTC
	rtc_enable(&AVR32_RTC);

	Enable_global_interrupt();
}

static void rtc_irq()
{
	rtc_clear_interrupt(&AVR32_RTC);
	rtc_int = 1;
}

int rtcSec()
{
	if(rtc_int == 1)
	{
		mscounter++;
		if(mscounter == 5)
		{
			LED_Toggle(LED1);
			mscounter = 0;
			return 1;
		}
		rtc_int = 0;
	}
	return 0;
}


void sysclock_start_timer (int time_setting, int sec)
{
	time_remaining = (time_setting - sec) * 1000;
	timer = 0;
}

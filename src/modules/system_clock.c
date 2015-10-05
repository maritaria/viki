/*
 * RTC.c
 *
 * Created: 28-9-2015 9:04:34
 *  Author: Tjalling
 */ 

#include <asf.h>
#include <tc.h>
#include "modules/system_clock.h"

volatile static int rtc_int = 0;
volatile static int TC_int = 0;
volatile static uint32_t timer = 0;

static int time_setting;
static int time_remaining;

void rtc_irq(void);
void tc_irq(void);
void rtcInit(void);
int rtcSec(void);
void tc(int, int);

void rtc_irq(void)
{
	rtc_clear_interrupt(&AVR32_RTC);
	rtc_int = 1;
}

void tc_irq(void)
{
	if(TC_int == 1)
	{	
		tc_read_sr(TC, TC_channel);
		timer++;
		if(timer >= time_remaining)
		{
			timer = 0;
			TC_int = 0;
		}
	}
}

static void tc_init(volatile avr32_tc_t *tc) 
{ 
	// Options for waveform generation. 
	static const tc_waveform_opt_t waveform_opt = 
	{ 
		// Channel selection. 
		.channel  = TC_channel,
		// Software trigger effect on TIOB. 
		.bswtrg   = TC_EVT_EFFECT_NOOP, 
		// External event effect on TIOB. 
		.beevt    = TC_EVT_EFFECT_NOOP, 
		// RC compare effect on TIOB. 
		.bcpc     = TC_EVT_EFFECT_NOOP, 
		// RB compare effect on TIOB.
		.bcpb     = TC_EVT_EFFECT_NOOP, 
		// Software trigger effect on TIOA.
		.aswtrg   = TC_EVT_EFFECT_NOOP, 
		// External event effect on TIOA. 
		.aeevt    = TC_EVT_EFFECT_NOOP, 
		// RC compare effect on TIOA. 
		.acpc     = TC_EVT_EFFECT_NOOP, 
		/* 
		 * RA compare effect on TIOA. 
		 * (other possibilities are none, set and clear). 
		 */ 
		.acpa     = TC_EVT_EFFECT_NOOP, 
		/* 
		 * Waveform selection: Up mode with automatic trigger(reset) 
		 * on RC compare. 
		 */ 
		.wavsel   = TC_WAVEFORM_SEL_UP_MODE_RC_TRIGGER, 
		// External event trigger enable.
		.enetrg   = false, 
		// External event selection. 
		.eevt     = 0, 
		// External event edge selection. 
		.eevtedg  = TC_SEL_NO_EDGE, 
		// Counter disable when RC compare. 
		.cpcdis   = false, 
		// Counter clock stopped with RC compare. 
		.cpcstop  = false, 
		// Burst signal selection. 
		.burst    = false, 
		// Clock inversion. 
		.clki     = false, 
		// Internal source clock 3, connected to fPBA / 8. 
		.tcclks   = TC_CLOCK_SOURCE_TC3 
	}; 
 
	// Options for enabling TC interrupts 
	static const tc_interrupt_t tc_interrupt = 
	{ 
		.etrgs = 0, 
		.ldrbs = 0, 
		.ldras = 0, 
		.cpcs  = 1, // Enable interrupt on RC compare alone 
		.cpbs  = 0, 
		.cpas  = 0, 
		.lovrs = 0, 
		.covfs = 0 
	}; 
	// Initialize the timer/counter. 
	tc_init_waveform(tc, &waveform_opt); 
	/* 
	 * Set the compare triggers. 
	 * We configure it to count every 1 milliseconds. 
	 * We want: (1 / (fPBA / 8)) * RC = 1 ms, hence RC = (fPBA / 8) / 1000 
	 * to get an interrupt every 10 ms. 
	 */ 
	tc_write_rc(tc, TC_channel, (sysclk_get_pba_hz() / 8 / 1000)); 
	// configure the timer interrupt 
	tc_configure_interrupts(tc, TC_channel, &tc_interrupt); 
	// Start the timer/counter. 
	tc_start(tc, TC_channel); 
} 

void rtcInit(void)
{
	#if __GNUC__
	// Initialize interrupt vectors.
	INTC_init_interrupts();
	// Register the RTC interrupt handler to the interrupt controller.
	INTC_register_interrupt(&rtc_irq, AVR32_RTC_IRQ, AVR32_INTC_INT0);
	INTC_register_interrupt(&tc_irq, AVR32_TC_IRQ0, AVR32_INTC_INT0);
	#endif


	Disable_global_interrupt();

	if (!rtc_init(&AVR32_RTC, RTC_OSC_32KHZ, RTC_PSEL_32KHZ_1HZ))
	{
		//usart_write_line(&AVR32_USART0, "Error initializing the RTC\r\n");
		while(1);
	}

	// Set top value to 0 to generate an interrupt every seconds
	rtc_set_top_value(&AVR32_RTC, top_val);
	// Enable the interrupts
	rtc_enable_interrupt(&AVR32_RTC);
	// Enable the RTC
	rtc_enable(&AVR32_RTC);

	cpu_irq_enable();

	tc_init(TC);

	Enable_global_interrupt();
}

int rtcSec()
{
	if(rtc_int == 1)
	{
		return 1;
	}
}


void tc (int time_setting, int sec)
{
	time_remaining = (time_setting - sec) * 1000;
	timer = 0;
	TC_int = 1;
}

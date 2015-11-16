#include "modules/clock.h"
//Standard C
#include <string.h>
//ASF
#include <asf.h>
//Custom
#include "modules/config.h"
#include "modules/datetime.h"

volatile float behind = 0;
static volatile float hardcodedpot = 0;

INTERRUPT_FUNCTION(rtc_irq);
static void rtc_hack(void);

static volatile avr32_adc_t * adc = (volatile avr32_adc_t *)&AVR32_ADC;
static volatile float potvalue = 0;
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
	
	//Potentio meter hack
	gpio_enable_module_pin(ADC_POTENTIOMETER_PIN , ADC_POTENTIOMETER_FUNCTION);
	adc_configure(adc);
	
	//float f;//0,3837498
	char b[] = {0x3E, 0xC4, 0x7A, 0xDC};
	memcpy(&hardcodedpot, &b, sizeof(float));
	
}

void clock_update()
{
	adc_enable(adc, ADC_POTENTIOMETER_CHANNEL);
	/* start conversion */
	adc_start(adc);
	/* get value for sensor */
	uint16_t raw = adc_get_value(adc, ADC_POTENTIOMETER_CHANNEL);//magic = 639
	potvalue = (float)raw / (float)ADC_MAX_VALUE;
	potvalue -= 0.5;
	potvalue *= 4;
	potvalue /= 10000;
	/* Disable channel for sensor */
	adc_disable(adc, ADC_POTENTIOMETER_CHANNEL);
	
}

static void rtc_irq()
{
	rtc_clear_interrupt(&AVR32_RTC);
	rtc_hack();
	datetime_increment_by_millisecond();
	LED_Toggle(LED1);
}

static void rtc_hack()
{
	/*
	//behind += 0.3678297911;
	//0.3 + (potvalue = 0,8758553 / 10)
	//0.3837 + 4.985337E-05
	//0.4985337 / 10000
	float byteValue = 0.3837 + potvalue;
	//behind += byteValue;
	//behind += (0.3837 + 0.00004985337);//1 minuut
	//It takes 5:42 minutes before the system runs 1 millisecond behind
	
	float f;//0,3837498
	char b[] = {0x3E, 0xC4, 0x7A, 0xDC};
	memcpy(&f, &b, sizeof(float));
	//potvalue 38 51 19 A7
	//endvalue 3E C4 7A DC
	*/
	//behind += hardcodedpot;potvalue;
	//behind += 0.3837 + potvalue;
	double delta = 0.3837 + potvalue;
	float delta2 = 0.3837 + potvalue;
	behind += 0.38374985337;
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
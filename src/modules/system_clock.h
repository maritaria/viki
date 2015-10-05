/*
 * RTC.h
 *
 * Created: 28-9-2015 9:12:37
 *  Author: Tjalling
 */ 

#ifndef RTC_H_
#define RTC_H_

#define top_val 0
#define TC_channel	0
#define TC &AVR32_TC

void rtc_irq(void);
void tc_irq(void);
void rtcInit(void);
int rtcSec(void);
void tc(int, int);


#endif /* RTC_H_ */
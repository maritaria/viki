/*
 * Klok.c
 *
 * Created: 28-9-2015 9:45:09
 *  Author: Tjalling
 */ 

#include <asf.h>
#include <tc.h>
#include "modules/system_clock.h"
#include "modules/clock.h"


int uur = 0;
int minuut = 0;
int seconde = 0;

int rtc;

void Klok(void);
void checkTargetTime(int, int, int, int, int, int);
void updateTime(int, int, int);


void Klok()
{
	rtc = rtcSec();
	if(rtc == 1)
	{
		seconde++;
	}
	
	if(seconde == 60){
		minuut++;
		seconde = 0;
		if(minuut == 60)
		{
			uur++;
			minuut = 0;
			if(uur == 24)
			{
				uur = 0;
			}
		}
	}
}

void checkTargetTime(int seconde, int minuut, int uur, int targettime_uur, int targettime_min, int targettime_sec)
{
	if(minuut == targettime_min && uur == targettime_uur && seconde - targettime_sec <= 1)
	{
		tc(seconde, targettime_sec);
	}
}
void updateTime(int sec, int min, int hour)
{
	seconde = sec;
	minuut = min;
	uur = hour;
}
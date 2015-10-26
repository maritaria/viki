#include "modules/datetime.h"
//Standard C
//ASF
#include <asf.h>
//Custom
#include "modules/config.h"
#include "modules/system_clock.h"

int uur = 0;
int minuut = 0;
int seconde = 0;

int rtc;

datetime_t current_time;

void datetime_init(void)
{
	//Initialize datetime_t variable
//	current_time = {0};
}

void datetime_current_time(datetime_t* date)
{
	date->day = current_time.day;
	//ETC...
}

void datetime_increment_by_ms(int elapsed_ms)
{
	//Called from sysclock
	//Increment the current datetime by the given number of milliseconds
}













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
		sysclock_start_timer(seconde, targettime_sec);
	}
}
void updateTime(int sec, int min, int hour)
{
	seconde = sec;
	minuut = min;
	uur = hour;
}
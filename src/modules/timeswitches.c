#include "timeswitches.h"
//Standard C
//ASF
#include <tc.h>
//Custom
#include "modules/datetime.h"
#include "modules/system_clock.h"

void* timeswitches_next_scheduled_item(void);
void timeswitches_prepare_interrupt(void* item);
bool tc_activated;

void timeswitches_init()
{
	//Reset TC settings
}

void timeswitches_rtc_poll(void)
{
	if (tc_activated)
	{
		return;
	}
	//Check if TC has to be activated
	void* item = timeswitches_next_scheduled_item();
	if (item)
	{
		//Activate
		timeswitches_prepare_interrupt(item);
	}
	
}
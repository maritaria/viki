#include "modules/config.h"

#include "modules/timeswitches.h"
#include "modules/joystick.h"

bool config_init(void)
{
	CONFIG.com_enabled = false;
	return true;
}
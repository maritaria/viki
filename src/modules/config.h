#ifndef MODULES__CONFIG_H_
#define MODULES__CONFIG_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/menu.h"
#include "modules/serial.h"
#include "modules/timeswitches.h"

DEFINE_TYPE(enum, menu_enum) {
	splash_screen,
	idle,
	menu,
		alert_list,//STATIC COUNT
			alert_settings,
				alert_edit_start, //DISABLE AFTER FIRST INTERVAL
				alert_edit_interval,
				alert_edit_repeat,
				alert_edit_target,
				alert_edit_behaviour,
				alert_edit_enable,
				alert_edit_clear,
		usb_settings,
			usb_edit_baud,//9600, 56000, 115200
			usb_edit_databits,//7, 8
			usb_edit_parity,//ON EVEN ODD MARK
			usb_edit_enable, //ON OFF RESTART
		power_settings,
			screen_edit_power,//0..4
			screen_edit_hybernate,//ALWAYS ON, HYBERNATE
			screen_edit_inversion,//ENABLED, DISABLED
		help_main,
			help_navigation,
			help_alerts_basic,
			help_alerts_behaviour,
			help_alerts_repeat,
};

#define TIMER_CONFIG_COUNT 4

DEFINE_TYPE(struct, config_t) {
	timeswitch_config_t timers[TIMER_CONFIG_COUNT];
	input_t input;
	bool com_enabled;
};

bool config_init(void);

volatile config_t config_instance;
#define CONFIG (config_instance)


#endif /* MODULES__CONFIG_H_ */
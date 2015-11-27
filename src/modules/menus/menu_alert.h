#ifndef MODULES__MENUS__MENU_ALERT_H_
#define MODULES__MENUS__MENU_ALERT_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"
#include "modules/menu.h"
#include "modules/timeswitches.h"

menu_t* generate_alert_menu(menu_t* parentMenu, timeswitch_config_t* config, const char* menu_title);


#endif /* MODULES__MENUS__MENU_ALERT_H_ */
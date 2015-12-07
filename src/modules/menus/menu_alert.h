#ifndef MODULES__MENUS__MENU_ALERT_H_
#define MODULES__MENUS__MENU_ALERT_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"
#include "modules/menu.h"
#include "modules/timeswitches.h"
#include "modules/config.h"

menu_t* generate_alerts_menu(menu_t* parentMenu, config_t* config);	


#endif /* MODULES__MENUS__MENU_ALERT_H_ */
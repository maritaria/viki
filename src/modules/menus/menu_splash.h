#ifndef MODULES__MENUS__MENU_SPLASH_H_
#define MODULES__MENUS__MENU_SPLASH_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"
#include "modules/menu.h"

char* menu_splash_get_title(menu_t* menu);
void menu_splash_tick(menu_t* menu);

menu_t* generate_splash_menu(menu_t* menu);


#endif /* MODULES__MENUS__MENU_SPLASH_H_ */
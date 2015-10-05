#ifndef MODULES__MENUS__MENU_DEFAULT_H_
#define MODULES__MENUS__MENU_DEFAULT_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"
#include "modules/menu.h"

char* menu_default_get_title(menu_t* menu);
void menu_default_tick(menu_t* menu);

#endif /* MODULES__MENUS__MENU_DEFAULT_H_ */
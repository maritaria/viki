#ifndef MODULES__MENUS__ITEM_SUBMENU_H_
#define MODULES__MENUS__ITEM_SUBMENU_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"
#include "modules/menu.h"

char* item_submenu_get_text(menu_item_t* item, bool selected);
void item_submenu_on_selected(menu_item_t* item);
void item_submenu_on_click(menu_item_t* item);

#endif /* MODULES__MENUS__ITEM_SUBMENU_H_ */
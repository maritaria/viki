#ifndef MODULES__MENUS__ITEM_DEMO_H_
#define MODULES__MENUS__ITEM_DEMO_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"
#include "modules/menu.h"

char* item_demo_get_text(menu_item_t* item, bool selected);
void item_demo_on_selected(menu_item_t* item);
void item_demo_on_click(menu_item_t* item);

menu_item_t* generate_demo_item(menu_t* parentMenu);

#endif /* MODULES__MENUS__ITEM_DEMO_H_ */
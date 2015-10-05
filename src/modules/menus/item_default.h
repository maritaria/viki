#ifndef MODULES__MENUS__ITEM_DEFAULT_H_
#define MODULES__MENUS__ITEM_DEFAULT_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"
#include "modules/menu.h"

char* item_default_get_text(menu_item_t* item, bool selected);
void item_default_on_selected(menu_item_t* item);
void item_default_on_click(menu_item_t* item);

#endif /* MODULES__MENUS__ITEM_DEFAULT_H_ */
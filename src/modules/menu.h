#ifndef MODULES__MENU_H_
#define MODULES__MENU_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"

#define MAXIMUM_ACTIVE_MENUS (6)
#define MENU_VISIBLE_ITEM_COUNT (3)

DEFINE_TYPE(struct, menu_item_t) {
	char* default_text;
	menu_item_t* next_item;//Linked list
	void* user_data;//Context/tag
	
	char* (*get_text)(menu_item_t*, bool);//Allows for scrollable text
	void (*on_selected)(menu_item_t*);//Allows for updating the text when the user selects it (and resetting horizontal scroll)
	void (*on_click)(menu_item_t*);//Called when the user clicks on the item
};

DEFINE_TYPE(struct, menu_t) {
	char* default_title;
	menu_item_t* first_item;//Linked list; first item points to the next one (etc)
	void* user_data;
	
	char* (*get_title)(menu_t*);
	void (*tick)(menu_t*);//Draw & update
	void (*on_load)(menu_t*);//When the menu first opens (used by editors to load initial values)
};

DEFINE_TYPE(struct, menu_state_t) {
	int scroll;//Vertical scroll in the item list (default menu's)
	int selected_index;//Index of selected item (default menu's)
};

/* Menu creation */
menu_t* menu_create(const char* defaultTitle);
menu_item_t* menu_add_item(menu_t* parentMenu, const char* defaultText);
menu_t* menu_add_submenu(menu_t* parentMenu, const char* defaultTitle);

/* Initializes the menu module */
bool menu_init(void);

/* Update tick function, call from infinite loop */
void menu_update(void);

/* Puts a menu on top of the menu stack */
void menu_push(menu_t* menu);
/* Closes the top-most menu */
void menu_pop(void);
/* Closes the top-most menu, except if the menu is the last one on the stack*/
void menu_pop_safe(void);
/* Gets the active menu */
menu_t* menu_peek(void);
/* Gets the number of menus on the stack*/
int menu_count(void);

/* Gets the title of a menu */
char* menu_get_title(menu_t* menu);
/* Gets a menu item from a menu, 0 indexed */
menu_item_t* menu_get_item_at(menu_t* menu, unsigned int index);
/* Gets the last item of a menu, this function walks down the linked list */
menu_item_t* menu_get_last_item(menu_t* menu);
/* Gets the number of items on a menu, this function is expensive */
int menu_get_item_count(menu_t* menu);

#endif /* MODULES__MENU_H_ */
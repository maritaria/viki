#ifndef MODULES__MENU_H_
#define MODULES__MENU_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"

#define MAXIMUM_ACTIVE_MENUS (6)

DEFINE_TYPE(struct, menu_item_t) {
	char* default_text;
	menu_item_t* next_item;
	void* user_data;
	
	char* (*get_text)(menu_item_t*);
	void (*on_item_selected)(menu_item_t*);
};

DEFINE_TYPE(struct, menu_t) {
	char* default_title;
	menu_item_t* first_item;
	void* user_data;
	
	char* (*get_title)(menu_t*);
	void (*update)(menu_t*);
};

/* Menu creation */
menu_t* menu_create(const char* defaultTitle, menu_t* parentMenu);
menu_item_t* menu_add_item(const char* defaultText, menu_t* parentMenu);

/* Initializes the menu module */
bool menu_init(void);

/* Update tick function, call from infinite loop */
void menu_update(void);

/* Puts a menu on top of the menu stack */
void menu_push(menu_t* menu);
/* Closes the top-most menu */
menu_t* menu_pop(void);
/* Gets the active menu */
menu_t* menu_peek(void);

/* Gets the title of a menu */
char* menu_get_title(menu_t* menu);
/* Gets the text of a menu item */
char* menu_item_get_text(menu_item_t* menu);
/* Gets a menu item from a menu, 0 indexed */
menu_item_t* menu_item_at(menu_t* menu, unsigned int index);
/* Gets the last item of a menu, this function walks down the linked list */
menu_item_t* menu_get_last_item(menu_t* menu);
/* Gets the numer of items on a menu, this function is expensive */
int menu_get_item_count(menu_t* menu);

#endif /* MODULES__MENU_H_ */
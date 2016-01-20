#ifndef MODULES__MENUS__EDITOR_INTEGER_H_
#define MODULES__MENUS__EDITOR_INTEGER_H_

//Standard C
//ASF
#include <asf.h>
#include <calendar.h>
//Custom
#include "macros.h"
#include "modules/menu.h"

DEFINE_TYPE(struct, editor_integer_data_t)
{
	int min;
	int max;
	int value;
	void (*on_cancel)(menu_t* menu, editor_integer_data_t* data);
	void (*on_completed)(menu_t* menu, editor_integer_data_t* data);
	void (*on_load)(menu_t*, editor_integer_data_t*);
	void *user_data;
	//const char *question,
};

char* editor_integer_get_title(menu_t* menu);
void editor_integer_tick(menu_t* menu);
void editor_interval_on_load(menu_t* menu);

menu_t* generate_editor_integer(menu_t* parentMenu, const char* defaultTitle, editor_integer_data_t dataTemplate);


#endif /* MODULES__MENUS__EDITOR_INTEGER_H_ */
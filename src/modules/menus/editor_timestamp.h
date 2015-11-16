#ifndef MODULES__MENUS__EDITOR_TIMESTAMP_H_
#define MODULES__MENUS__EDITOR_TIMESTAMP_H_

//Standard C
//ASF
#include <asf.h>
#include <calendar.h>
//Custom
#include "macros.h"
#include "modules/datetime.h"
#include "modules/menu.h"

//	    5    0    5    0.
//	Enter timestamp:    .
//	Date: ____-__-__   X. X = Y/M/D
//	Time: __:__:__ ___ms.
//	>ok  RESET  CANCEL    .

DEFINE_TYPE(enum, editor_timestamp_field) {
	date_year, date_month, date_day,
	time_hour, time_minute, time_second, time_millisecond,
	action_accept, action_cancel, action_reset,
};

DEFINE_TYPE(struct, editor_timestamp_data_t) {
	/* The datetime entered by the user*/
	struct calendar_date user_input;
	/* True if user accepted the input, false if user canceled action*/
	bool user_accepted;
	/* Whether the user is allowed to cancel */
	bool user_can_cancel;
	/* internal use */
	editor_timestamp_field current_field;
	/* internal use */
	int field_offset;
	
	/* The function to be called when the user exits the editor */
	void (*user_finished)(editor_timestamp_data_t*);
};

char* editor_timestamp_get_title(menu_t* menu);
void editor_timestamp_tick(menu_t* menu);

#endif /* MODULES__MENUS__EDITOR_TIMESTAMP_H_ */
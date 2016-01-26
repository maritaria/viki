#include "modules/menus/item_default.h"
//C standard library
#include <string.h>
//ASF
//Modules
#include "modules/display.h"
#include "modules/joystick.h"
#include "modules/menu.h"

void item_default_on_selected(menu_item_t* item);
void item_default_on_click(menu_item_t* item);

volatile int counter = 0;
volatile int shift_offset = 0;
volatile char selected_text_buffer[64] = {0};

char* item_default_get_text(menu_item_t* item, bool selected)
{
	if (!selected)
	{
		return item->default_text;
	}
	memset(selected_text_buffer, ' ', 64);
	int length = min(strlen(item->default_text), 62);
	memcpy(selected_text_buffer, item->default_text, length);
	selected_text_buffer[length] = ' ';
	length++;
	//Should the text rotate?
	if (length > 15)
	{
		//Wait for a bit before starting to rotate
		if (counter++ > 100)
		{
			if(shift_offset++ >= length)
			{
				shift_offset = 0;
				counter = 0;
			}
			else
			{
				counter -= 10;	
			}
		}
	}
	else
	{
		shift_offset = 0;
	}
	//Rotate the title a given amount of bytes
	for(int i = 0; i < shift_offset; i++)
	{
		char first = selected_text_buffer[0];
		memmove(selected_text_buffer, &(selected_text_buffer[1]), length - 1);
		selected_text_buffer[length - 1] = first;
	}
	selected_text_buffer[length] = '\0';
	return selected_text_buffer;
}

void item_default_on_selected(menu_item_t* item)
{
	//Reset the rotation and wait timer
	counter = 0;
	shift_offset = 0;
}

void item_default_on_click(menu_item_t* item)
{
	//If no callback is set; it just shows a blank screen with the following small message for a short while
	int i = 0;
	while(i++ < 100)
	{
		display_clear();
		display_printf(14 + 20,"You selected:\n%s", item->get_text(item, false));
		display_update();
	}
	menu_pop_safe();
}
#ifndef MODULES__DISPLAY_H_
#define MODULES__DISPLAY_H_

//Standard C
//ASF
#include <asf.h>
//Custom
#include "macros.h"

#define DISPLAY_WIDTH (20)
#define DISPLAY_HEIGHT (4)
#define DISPLAY_SIZE (DISPLAY_WIDTH * DISPLAY_HEIGHT)

DEFINE_TYPE(struct, display_settings_t) {
	bool hybernate;
	bool inverted;
};

/* Initializes the display */
bool display_init(void);
/* Updates the display to the buffered data */
void display_update(void);

/* Gets whether the cursor is visible */
void display_set_cursor(bool enabled);
/* Sets whether the cursor is visible */
bool display_get_cursor(void);

/* Sets the position of the cursor in the buffer */
void display_set_pos(unsigned char x, unsigned char y);
/* Gets the position of the cursor in the buffer */
void display_get_pos(unsigned char* x, unsigned char* y);

/* Clears the display and sets the cursor to the top-left corner*/
void display_clear(void);
/* Prints a (constant) string to the current position, supports newlines, tabs and wraps the text automatically */
void display_print(const char* text);
/* Prints a single character to the current position, and advances the position */
void display_printc(char character);
/* Prints a formatted string (with a given maximum length) to the display at the current position*/
void display_printf(size_t maxLength, const char* format, ...);

#endif /* MODULES__DISPLAY_H_ */
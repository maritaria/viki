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

#define DISPLAY_SPACE (' ')
#define DISPLAY_FILL (0x1F)

#define DISPLAY_ARROW_LEFT (0xE1)
#define DISPLAY_ARROW_RIGHT (0xDF)
#define DISPLAY_ARROW_UP (0xDE)
#define DISPLAY_ARROW_DOWN (0xE0)

#define DISPLAY_FULL_ARROW_LEFT (0x10)
#define DISPLAY_FULL_ARROW_RIGHT (0x11)
#define DISPLAY_FULL_ARROW_UP (0x1A)
#define DISPLAY_FULL_ARROW_DOWN (0x1B)

#define DISPLAY_LOAD_1 (0xDA)
#define DISPLAY_LOAD_2 (0xD5)
#define DISPLAY_LOAD_3 (0xD6)
#define DISPLAY_LOAD_4 (0xD7)
#define DISPLAY_LOAD_5 (0xD6)

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
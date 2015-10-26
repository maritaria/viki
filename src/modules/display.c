#include "modules/display.h"
//C standard library
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
//ASF
#include <dip204.h>
#include <board.h>
#include <spi.h>
#include <gpio.h>
//Modules
#include "modules/config.h"

volatile char displayBuffer[DISPLAY_HEIGHT][DISPLAY_WIDTH];
volatile bool cursor_enabled_desired = false;
volatile bool cursor_enabled_real = true;

volatile unsigned char cursor_x_desired;
volatile unsigned char cursor_y_desired;

void display_init_gpio(void);
void display_init_spi(void);
void display_init_device(void);
void display_update_content(void);
void display_update_cursor(void);

bool display_init(void)
{
	display_init_spi();
	display_init_gpio();
	display_init_device();
	return true;
}

void display_init_gpio()
{
	static const gpio_map_t DIP204_SPI_GPIO_MAP =
	{
		{ DIP204_SPI_SCK_PIN,	DIP204_SPI_SCK_FUNCTION },	// SPI Clock.
		{ DIP204_SPI_MISO_PIN,	DIP204_SPI_MISO_FUNCTION },	// MISO.
		{ DIP204_SPI_MOSI_PIN,	DIP204_SPI_MOSI_FUNCTION },	// MOSI.
		{ DIP204_SPI_NPCS_PIN,	DIP204_SPI_NPCS_FUNCTION }	// Chip Select NPCS.
	};
	gpio_enable_module(DIP204_SPI_GPIO_MAP, sizeof(DIP204_SPI_GPIO_MAP) / sizeof(DIP204_SPI_GPIO_MAP[0]));
}

void display_init_spi()
{
	spi_options_t spiOptions =
	{
		.reg = DIP204_SPI_NPCS,
		.baudrate = 1000000,
		.bits = 8,
		.spck_delay = 0,
		.trans_delay = 0,
		.stay_act = 1,
		.spi_mode = 0,
		.modfdis = 1
	};
	spi_initMaster(DIP204_SPI, &spiOptions);
	spi_selectionMode(DIP204_SPI, 0, 0, 0);
	spi_enable(DIP204_SPI);
	spi_setupChipReg(DIP204_SPI, &spiOptions, FOSC0 * 4);
}

void display_init_device()
{
	dip204_init(backlight_IO, true);
	display_clear();
	display_set_cursor(false);
}

void display_update()
{
	display_update_content();
	display_update_cursor();
}

void display_update_content()
{
	for(int y = 0; y < DISPLAY_HEIGHT; y++)
	{
		dip204_set_cursor_position(1, 1);
		char line[DISPLAY_SIZE + 1] = { '\0' };
		memcpy(&line, &displayBuffer, DISPLAY_SIZE);
		dip204_write_string(line);
	}
}

void display_update_cursor()
{
	if (cursor_enabled_desired != cursor_enabled_real)
	{
		if (cursor_enabled_desired)
		{
			dip204_show_cursor();
		}
		else
		{
			//dip204_hide_cursor();
		}
		cursor_enabled_real = cursor_enabled_desired;
	}
	dip204_set_cursor_position(cursor_x_desired + 1, cursor_y_desired + 1);
}

void display_set_cursor(bool enabled)
{
	cursor_enabled_desired = enabled;
}

bool display_get_cursor()
{
	return cursor_enabled_desired;
}

void display_set_pos(unsigned char x, unsigned char y)
{
	cursor_x_desired = x;
	cursor_y_desired = y;
}

void display_get_pos(unsigned char* x, unsigned char* y)
{
	*x = cursor_x_desired;
	*y = cursor_y_desired;
}

void display_clear()
{
	memset(displayBuffer, ' ', DISPLAY_SIZE);
	display_set_pos(0, 0);
}

void display_print(const char* text)
{
	unsigned char currentPos, currentLine;
	display_get_pos(&currentPos, &currentLine);
	unsigned char textIndex = 0;
	bool keepGoing = true;
	while(keepGoing)
	{
		if (currentPos >= DISPLAY_WIDTH)
		{
			currentPos = 0;
			currentLine++;
		}
		if (currentLine >= DISPLAY_HEIGHT)
		{
			currentLine = 0;
		}
		char letter = text[textIndex];
		switch(letter)
		{
			case '\0': 
				keepGoing = false;
			break;
			case '\n':
				for (; currentPos < DISPLAY_WIDTH; currentPos++)
				{
					displayBuffer[currentLine][currentPos] = DISPLAY_SPACE;	
				}
			break;
			case '\t':
				for(;currentPos < ((currentPos / 4) + 1) * 4; currentPos++)
				{
					displayBuffer[currentLine][currentPos] = DISPLAY_SPACE;
				}
			break;
			case '\r':
				currentPos = 0;
			break;
			default:
				displayBuffer[currentLine][currentPos] = text[textIndex];
				currentPos++;
			break;
		}
		textIndex++;
	}
	display_set_pos(currentPos, currentLine);
}

void display_printc(char character)
{
	char text[2] = { character, '\0' };
	display_print(text);
}

void display_printf(size_t maxLength, const char* format, ...)
{
	maxLength++;//Add space for the '\0'
	char* buffer = (char*)malloc(maxLength);
	memset(buffer, '\0', maxLength);
	
	va_list arg;
	va_start(arg, format);
	size_t i = vsnprintf(buffer, maxLength, format, arg);
	va_end(arg);
	
	while(i < maxLength - 1)
	{
		buffer[i] = '\0';
		i++;
	}
	display_print(buffer);
	free(buffer);
}
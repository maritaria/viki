/*
 * Flash_memory.c
 *
 * Created: 11-1-2016 9:55:19
 *  Author: Tjalling
 */ 
#include "flashc.h"


typedef const struct {
	uint8_t  var8;
	uint16_t var16;
	uint8_t  var8_3[3];
	uint32_t var32;
} nvram_data_t;

#if defined (__GNUC__)
__attribute__((__section__(".flash_nvram")))
#endif
static nvram_data_t flash_nvram_data;
#if defined (__ICCAVR32__)
@ "FLASH_NVRAM"
#endif
;

void test_func();
void test_func_twee(nvram_data_t *);

void test_func()
{
	test_func_twee(&flash_nvram_data);
}

void test_func_twee(nvram_data_t *nvram_data)
{
	uint8_t test = 10;
	flashc_memcpy((void	*)&nvram_data->var8, &test, sizeof(test), true);
	test = 23;
	test = nvram_data->var8;
	
}
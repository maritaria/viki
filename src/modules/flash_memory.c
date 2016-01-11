/*
 * Flash_memory.c
 *
 * Created: 11-1-2016 9:55:19
 *  Author: Tjalling
 */ 
#include "flashc.h"
#include "modules/config.h"

typedef const struct {
	timeswitch_config_t switches[TIMER_CONFIG_COUNT];
} nvram_data_t;

#if defined (__GNUC__)
__attribute__((__section__(".userpage")))
#endif
static nvram_data_t flash_nvram_data;
#if defined (__ICCAVR32__)
@ "USERDATA32_C"
#endif
;

void flash_save_next()
{
	flashc_lock_all_regions(false);
	static int i = 0;
	uint8_t test = 10;
	flashc_memcpy((void*)&(flash_nvram_data.switches[i]), &CONFIG.timers[i], sizeof(timeswitch_config_t), true);
	i++;
	if(i >= 4)
		i = 0;
			
	flashc_lock_all_regions(true);	
}
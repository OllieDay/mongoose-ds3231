#ifndef __DS3231_H__
#define __DS3231_H__

#include <stdbool.h>
#include <stdint.h>

struct datetime {
	uint8_t second;
	uint8_t minute;
	uint8_t hour;
	uint8_t weekday;
	uint8_t day;
	uint8_t month;
	uint16_t year;
};

bool ds3231_lost_power(void);
bool ds3231_get_datetime(struct datetime *datetime);
bool ds3231_set_datetime(const struct datetime *datetime);

#endif

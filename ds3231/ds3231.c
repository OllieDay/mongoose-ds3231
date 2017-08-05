#include "ds3231.h"
#include "fw/src/mgos_i2c.h"

#include <stddef.h>

// I2C slave address
#define DS3231_ADDRESS 0x68

// Registers
#define DS3231_TIME    0x00
#define DS3231_STATUS  0x0F

static uint8_t bcd_to_dec(const uint8_t value) {
	return ((value / 16) * 10) + (value % 16);
}

static uint8_t dec_to_bcd(const uint8_t value) {
	return ((value / 10) * 16) + (value % 10);
}

bool ds3231_lost_power(void) {
	return (mgos_i2c_read_reg_b(mgos_i2c_get_global(), DS3231_ADDRESS, DS3231_STATUS) >> 7) == 1;
}

bool ds3231_get_datetime(struct datetime *const datetime) {
	if (datetime == NULL) {
		return false;
	}

	static const uint8_t data = DS3231_TIME;

	if (!mgos_i2c_write(mgos_i2c_get_global(), DS3231_ADDRESS, &data, sizeof data, true)) {
		return false;
	}

	static uint8_t buffer[7];

	if (!mgos_i2c_read(mgos_i2c_get_global(), DS3231_ADDRESS, buffer, sizeof buffer, true)) {
		return false;
	}

	datetime->second = bcd_to_dec(buffer[0] & 0x7F);
	datetime->minute = bcd_to_dec(buffer[1]);
	datetime->hour = bcd_to_dec(buffer[2]);
	datetime->weekday = bcd_to_dec(buffer[3]);
	datetime->day = bcd_to_dec(buffer[4]);
	datetime->month = bcd_to_dec(buffer[5]);
	datetime->year = bcd_to_dec(buffer[6]) + 2000;

	return true;
}

bool ds3231_set_datetime(const struct datetime *const datetime) {
	if (datetime == NULL) {
		return false;
	}

	static uint8_t buffer[8];

	buffer[0] = DS3231_TIME;
	buffer[1] = dec_to_bcd(datetime->second);
	buffer[2] = dec_to_bcd(datetime->minute);
	buffer[3] = dec_to_bcd(datetime->hour);
	buffer[4] = dec_to_bcd(datetime->weekday);
	buffer[5] = dec_to_bcd(datetime->day);
	buffer[6] = dec_to_bcd(datetime->month);
	buffer[7] = dec_to_bcd(datetime->year - 2000);

	return mgos_i2c_write(mgos_i2c_get_global(), DS3231_ADDRESS, &buffer, sizeof buffer, true);
}

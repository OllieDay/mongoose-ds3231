# mongoose-ds3231
Mongoose OS I2C driver for the DS3231 real-time clock.

## Overview
This driver enables control of the DS3231 real-time clock over I2C on Mongoose OS. This only supports time functions and
alarms are not currently implemented.

## Setup
1. Copy the `ds3231` directory into the firmware's `src` directory and add it to the `sources` section of `mos.yml`
2. Enable the Mongoose OS I2C connection by adding `["i2c.enable", true],` in `conf_schema.yaml`
3. Include the header `"ds3231/ds3231.h"` in the appropriate places

## Usage

### Setting the current date and time
```c
// Sunday, June 11, 2017 1:30:00 PM
const struct datetime dt = {
	.second = 0,
	.minute = 30,
	.hour = 13,
	.weekday = 7,
	.day = 11,
	.month = 6,
	.year = 2017
};

ds3231_set_datetime(&dt);
```

### Getting the current date and time
```c
struct datetime dt;

ds3231_get_datetime(&dt);
```

### Checking for power loss
```c
if (ds3231_lost_power()) {
	// Power lost...
}
```

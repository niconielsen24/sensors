#ifndef _SENSOR_UTILS_
#define _SENSOR_UTILS_
#include <sensors/sensors.h>

int chip_count ();

const sensors_chip_name ** get_chips();

const sensors_feature * get_chip_feature(const sensors_chip_name * chip_name, sensors_feature_type type);

#endif
#ifndef BME280_H
#define BME280_H

#include "esp_err.h"

#define BME280_ADDR 0x76

esp_err_t bme280_read_id();

#endif
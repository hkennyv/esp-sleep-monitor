#ifndef BME280_H
#define BME280_H

#include "esp_err.h"

#define BME280_ADDR 0x76

// BME280 REGISTERS
#define BME280_REG_ID 0xD0
#define BME280_REG_RESET 0xE0
#define BME280_REG_CTRL_HUM 0xF2
#define BME280_REG_STATUS 0xF3
#define BME280_REG_CONFIG 0xF5
#define BME280_REG_PRESS 0xF7
#define BME280_REG_TEMP 0xFA
#define BME280_REG_HUM 0xFD

esp_err_t bme280_init();
esp_err_t bme280_read_id();
esp_err_t bme280_read_temp();

#endif
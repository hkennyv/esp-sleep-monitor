#ifndef CCS811_H
#define CCS811_H

#include "esp_err.h"

#define CCS811_ADDR 0x5A

esp_err_t ccs811_read_id();

#endif
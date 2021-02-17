
/* Hello World Example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"

#include "driver/gpio.h"
#include "bme280.h"
#include "ccs811.h"
#include "gpio.h"
#include "i2c.h"

void init();

void app_main(void)
{
    // initialize peripherals
    init();

    for (int i = 10; i >= 0; i--)
    {
        printf("Restarting in %d seconds...\n", i);
        bme280_read_id();
        ccs811_read_id();
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(LED, i % 2);
    }

    printf("Restarting now.\n");
    esp_restart();
}

void init()
{
    gpio_config_init();
    i2c_init();
}
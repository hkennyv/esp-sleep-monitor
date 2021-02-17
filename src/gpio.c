#include "gpio.h"
#include "driver/gpio.h"

void gpio_config_init()
{
    gpio_config_t config;

    // set as output mode
    config.mode = GPIO_MODE_OUTPUT;

    // bit mask of pins that you want to select
    config.pin_bit_mask = GPIO_OUTPUT_PIN_SEL;

    // disable pull-down mode and pull-up mode
    config.pull_down_en = 0;
    config.pull_up_en = 0;

    // configure GPIO
    gpio_config(&config);

    // turn on blue LED on init success
    gpio_set_level(LED, 1);
}
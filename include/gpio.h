#ifndef GPIO_H
#define GPIO_H

// GPIO2 is connected to the BLUE LED
#define LED 2

// bitmask of output gpios
#define GPIO_OUTPUT_PIN_SEL (1ULL << LED)

// initializes the GPIOs as inputs/outputs
void gpio_config_init();

#endif
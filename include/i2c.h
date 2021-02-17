#ifndef I2C_H
#define I2C_H

#include "driver/i2c.h"
#include "esp_err.h"

typedef uint8_t i2c_addr_t;

// I2C HW configuration
// see docs/esp32-hiletgo-dev-pinout.jpg for more details
#define I2C_NUM I2C_NUM_1 // I2C port
#define I2C_SDA 21
#define I2C_SCL 22

// BME280 has max clock frequency of 10Mhz
// CCS811 has max clock frequency of 400khz
// 80Mhz / 200 = 400khz
#define I2C_MASTER_FREQ_HZ I2C_APB_CLK_FREQ / 200
#define I2C_MASTER_RX_BUF_DISABLE 0 // I2C master doesn't need buffer
#define I2C_MASTER_TX_BUF_DISABLE 0 // I2C master doesn't need buffer
#define I2C_INTERRUPT_FLAGS 0

#define I2C_ACK_CHECK_EN 1  // I2C master will check ack from slave
#define I2C_ACK_CHECK_DIS 1 // I2C master will not check ack from slave
#define I2C_ACK_VAL 0       // I2C ACK value
#define I2C_NACK_VAL 1      // I2C NACK value

// buffer configuration
#define I2C_BUFFER_LEN 256

// must be called before using any of the other provided functions
esp_err_t i2c_init();

// a generic i2c write function
esp_err_t i2c_write(i2c_port_t i2c_num, i2c_addr_t i2c_dev_addr, i2c_addr_t i2c_addr, uint8_t *data_wr, size_t size);

// a generic i2c read function
esp_err_t i2c_read(i2c_port_t i2c_num, i2c_addr_t i2c_dev_addr, i2c_addr_t i2c_addr, uint8_t *data_rd, size_t size);

#endif
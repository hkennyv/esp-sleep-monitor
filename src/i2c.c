#include <stdio.h>

#include "esp_log.h"
#include "driver/i2c.h"
#include "i2c.h"

esp_err_t i2c_init()
{
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_SDA,
        .scl_io_num = I2C_SCL,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ};

    i2c_param_config(I2C_NUM, &conf);
    printf("I2C init\n");

    return i2c_driver_install(I2C_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, I2C_INTERRUPT_FLAGS);
}

esp_err_t i2c_write(i2c_port_t i2c_num, i2c_addr_t i2c_dev_addr, i2c_addr_t i2c_addr, uint8_t *data_wr, size_t size)
{
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (i2c_addr << 1) | I2C_MASTER_WRITE, I2C_ACK_CHECK_EN);
    i2c_master_write(cmd, data_wr, size, I2C_ACK_CHECK_EN);
    i2c_master_stop(cmd);
    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}

esp_err_t i2c_read(i2c_port_t i2c_num, i2c_addr_t i2c_dev_addr, i2c_addr_t i2c_addr, uint8_t *data_rd, size_t size)
{
    if (size == 0)
    {
        return ESP_OK;
    }
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    /*
     * START
     * WRITE DEVICE WRITE
     * WRITE DEVICE REGISTER
     */
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (i2c_dev_addr << 1) | I2C_MASTER_WRITE, I2C_ACK_CHECK_EN);
    i2c_master_write_byte(cmd, i2c_addr, I2C_ACK_CHECK_EN);

    /*
     * START
     * WRITE DEVICE READ
     * READ size - 1 bytes, send ACKs
     * READ last byte, send NACK
     * STOP
     */
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (i2c_dev_addr << 1) | I2C_MASTER_READ, I2C_ACK_CHECK_EN);
    if (size > 1)
    {
        i2c_master_read(cmd, data_rd, size - 1, I2C_ACK_VAL);
    }
    i2c_master_read_byte(cmd, data_rd + size - 1, I2C_NACK_VAL);
    i2c_master_stop(cmd);

    esp_err_t ret = i2c_master_cmd_begin(i2c_num, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    return ret;
}
#include "driver/i2c.h"
#include "esp_err.h"

#include "bme280.h"
#include "i2c.h"

#if 1
esp_err_t bme280_read_id()
{
    uint8_t data[1] = {0};
    uint8_t data_size = 1;

    uint8_t reg_addr = 0xD0;

    esp_err_t ret = i2c_read(I2C_NUM, BME280_ADDR, reg_addr, data, data_size);

    if (ret == ESP_OK)
    {
        printf("bme280 hardware id: 0x%x\n", data[0]);
    }
    else
    {
        const char *err_name = esp_err_to_name(ret);

        printf("error in i2c. code: [0x%x] %s\n", ret, err_name);
    }
    return ret;
}
#endif

#if 0
esp_err_t bme280_read_id()
{
    /*
     * Register 0xD0 "id"
     * 
     * contains the chip identificatio number chip_id[7:0], which is 0x60
     * this number can be read as soon as the device finished the
     * power-on-reset
     */
    uint8_t data = 0;
    uint8_t reg_addr = 0xD0;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();

    i2c_master_start(cmd);                                                               // START
    i2c_master_write_byte(cmd, (BME280_ADDR << 1) | I2C_MASTER_WRITE, I2C_ACK_CHECK_EN); // WRITE
    i2c_master_write_byte(cmd, reg_addr, I2C_ACK_CHECK_EN);                              // reg_addr

    i2c_master_start(cmd);                                                              // START
    i2c_master_write_byte(cmd, (BME280_ADDR << 1) | I2C_MASTER_READ, I2C_ACK_CHECK_EN); // READ
    i2c_master_read_byte(cmd, &data, I2C_NACK_VAL);                                     // data byte
    i2c_master_stop(cmd);                                                               // STOP

    esp_err_t ret = i2c_master_cmd_begin(I2C_NUM, cmd, 5000 / portTICK_RATE_MS);

    if (ret == ESP_OK)
    {
        printf("bme280 hardware id: 0x%x\n", data);
    }
    else
    {
        const char *err_name = esp_err_to_name(ret);

        printf("error in i2c. code: [0x%x] %s\n", ret, err_name);
    }
    i2c_cmd_link_delete(cmd);
    return ret;
}
#endif
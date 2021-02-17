#include "driver/i2c.h"
#include "esp_err.h"

#include "bme280.h"
#include "i2c.h"

// TODO
esp_err_t bme280_init()
{
    // SET NORMAL mode
    // SET t_standby = 0.5ms
    // SET presure x16, temperature x2, humidity x1
    // SET IIR filter coeff 16

    return ESP_OK;
}

esp_err_t bme280_read_id()
{
    uint8_t data[1] = {0};
    size_t data_size = 1;

    i2c_addr_t reg_addr = 0xD0;

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

esp_err_t bme280_read_temp()
{
    uint8_t data[3] = {0};
    size_t data_size = 3;

    i2c_addr_t reg_addr = BME280_REG_TEMP;

    esp_err_t ret = i2c_read(I2C_NUM, BME280_ADDR, reg_addr, data, data_size);

    if (ret == ESP_OK)
    {
        uint16_t temp = (data[0] << 8) | (data[1] << 0);
        printf("bme280 temp: %d\n", temp);
    }
    else
    {
        const char *err_name = esp_err_to_name(ret);

        printf("error in i2c. code: [0x%x] %s\n", ret, err_name);
    }
    return ret;
}
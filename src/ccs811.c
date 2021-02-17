#include "driver/i2c.h"
#include "esp_err.h"

#include "ccs811.h"
#include "i2c.h"

esp_err_t ccs811_read_id()
{
    uint8_t data[1] = {0};
    uint8_t data_size = 1;

    uint8_t reg_addr = 0x20;

    esp_err_t ret = i2c_read(I2C_NUM, CCS811_ADDR, reg_addr, data, data_size);

    if (ret == ESP_OK)
    {
        printf("ccs811 hardware id: 0x%x\n", data[0]);
    }
    else
    {
        const char *err_name = esp_err_to_name(ret);

        printf("error in i2c. code: [0x%x] %s\n", ret, err_name);
    }
    return ret;
}

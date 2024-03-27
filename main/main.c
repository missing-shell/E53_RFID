#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"

#include "sdkconfig.h"
#include "esp_log.h"

#define RC522_HOST SPI2_HOST
#define PIN_NUM_MISO 2
#define PIN_NUM_MOSI 7
#define PIN_NUM_CLK 6
#define PIN_NUM_CS 10

static const char TAG[] = "main";

void app_main(void)
{
    esp_err_t ret;
    ESP_LOGI(TAG, "Initializing bus SPI%d...", RC522_HOST + 1);
    spi_bus_config_t buscfg = {
        .miso_io_num = PIN_NUM_MISO,
        .mosi_io_num = PIN_NUM_MOSI,
        .sclk_io_num = PIN_NUM_CLK,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = 32,
    };
    // Initialize the SPI bus
    ret = spi_bus_initialize(RC522_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);

    while (1)
    {
        ESP_LOGI(TAG, "Initializing  ...");
        vTaskDelay(1);
    }
}

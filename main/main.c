#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "sdkconfig.h"
#include "esp_log.h"
#include "rc522.h"

#define RC522_HOST SPI2_HOST
#define PIN_NUM_SDA (23)
#define PIN_NUM_SCK (19)
#define PIN_NUM_MOSI (18)
#define PIN_NUM_MISO (20)
#define PIN_NUM_RST (22)

static const char TAG[] = "RC522_EXAMPLE";

static void setup_3v3_output(uint8_t gpio_num)
{
    gpio_config_t ioconfig = {
        .pin_bit_mask = (1ULL << gpio_num),
        .mode = GPIO_MODE_OUTPUT};
    gpio_config(&ioconfig);

    // 设置GPIO为高电平
    gpio_set_level(gpio_num, 1);
}

static rc522_handle_t scanner;
/**
 * @brief 处理RC522模块的事件。
 *
 * 此函数为RC522 RFID模块扫描到标签时的事件处理函数。它会根据事件类型执行相应的操作。
 *
 * @param arg 传递给事件处理函数的参数，通常用于指向调用者提供的上下文信息。
 * @param base 事件的基础类型，用于识别事件来源。
 * @param event_id 事件的ID，用于识别具体的事件。
 * @param event_data 事件相关的数据，具体取决于事件类型。
 */
static void rc522_handler(void *arg, esp_event_base_t base, int32_t event_id, void *event_data)
{
    // 将event_data强制转换为rc522_event_data_t类型，以便访问其中的成员。
    rc522_event_data_t *data = (rc522_event_data_t *)event_data;

    switch (event_id)
    {
    // 当扫描到标签时处理的逻辑
    case RC522_EVENT_TAG_SCANNED:
    {
        // 将data->ptr转换为rc522_tag_t类型，以便访问标签信息。
        rc522_tag_t *tag = (rc522_tag_t *)data->ptr;
        // 打印标签的序列号信息
        ESP_LOGI(TAG, "Tag scanned (sn: %" PRIu64 ")", tag->serial_number);
        // 打印标签的序列号信息为十六进制
        ESP_LOGI(TAG, "Tag scanned (sn: %02llx)", tag->serial_number);
    }
    break;

        // 处理未知事件
    default:
    {
        ESP_LOGW(TAG, "Unknown event id: %ld", event_id);
    }
    break;
    }

    ESP_LOGI(TAG, "----------------------------");
}
/**
 * 初始化RC522 RFID模块。
 *
 * @param out_rc522 指向RC522句柄的指针，函数会将创建的RC522实例的地址存储到此处。
 * @return 返回操作的结果状态码。如果操作成功，返回ESP_OK；否则返回错误码。
 */
static esp_err_t rc522_initialize()
{
    rc522_config_t config = {

        .spi.host = RC522_HOST,
        .spi.miso_gpio = PIN_NUM_MISO,
        .spi.mosi_gpio = PIN_NUM_MOSI,
        .spi.sck_gpio = PIN_NUM_SCK,
        .spi.sda_gpio = PIN_NUM_SDA,

    };

    // 调用rc522_create并处理错误
    esp_err_t ret = rc522_create(&config, &scanner);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to create RC522 scanner handle: %s", esp_err_to_name(ret));
        return ret;
    }

    // 如果创建成功，继续注册事件处理器
    ret = rc522_register_events(scanner, RC522_EVENT_ANY, rc522_handler, NULL);
    if (ret != ESP_OK)
    {
        ESP_LOGE(TAG, "Failed to register events for RC522 scanner: %s", esp_err_to_name(ret));
    }

    // 启动扫描器
    rc522_start(scanner);
    rc522_enable_write_mode(scanner, 2);
    return ESP_OK;
}

void app_main()
{

    // 设置GPIO3为3.3V输出-RST引脚
    setup_3v3_output(PIN_NUM_RST);

    esp_err_t ret = rc522_initialize();
    if (ret != ESP_OK)
    {
        // 初始化失败，退出程序或其他适当处理
        ESP_LOGE(TAG, "Failed to init rc522");
    }

    // 在程序结束或不需要使用RC522时，确保正确释放资源
    // rc522_destroy(scanner);
}

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "wifi_manager.h"
#include "command_server.h"

static const char *TAG = "ESP32_BOT";

static void on_wifi_connected(void)
{
    ESP_LOGI(TAG, "WiFi connected! Ready for command server.");
}

static void on_wifi_disconnected(void)
{
    ESP_LOGW(TAG, "WiFi disconnected!");
}

void app_main(void)
{
    ESP_LOGI(TAG, "ESP32_BOT starting...");

    const char *ssid = "Nathan5G";
    const char *pass = "Nathan123@@##";

    wifi_manager_init(ssid, pass, on_wifi_connected, on_wifi_disconnected);

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }

    command_server_start();
}

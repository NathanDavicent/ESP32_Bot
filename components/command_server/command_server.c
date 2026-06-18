#include "command_server.h"
#include "esp_log.h"
#include "lwip/sockets.h"
#include "string.h"

static const char *TAG = "command_server";

#define SERVER_PORT 5050
#define RX_BUF_SIZE 256

void command_server_task(void *pvParameters) {
    command_server_start();
    vTaskDelete(NULL);
}

void command_server_start(void)
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);

    server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (server_fd < 0) {
        ESP_LOGE(TAG, "Failed to create socket");
        return;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        ESP_LOGE(TAG, "Socket bind failed");
        close(server_fd);
        return;
    }

    if (listen(server_fd, 1) < 0) {
        ESP_LOGE(TAG, "Socket listen failed");
        close(server_fd);
        return;
    }

    ESP_LOGI(TAG, "Command server listening on port %d", SERVER_PORT);

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd < 0) {
            ESP_LOGE(TAG, "Accept failed");
            continue;
        }

        ESP_LOGI(TAG, "Client connected");

        char rx_buffer[RX_BUF_SIZE];

        while (1) {
            int len = recv(client_fd, rx_buffer, RX_BUF_SIZE - 1, 0);
            if (len <= 0) {
                ESP_LOGI(TAG, "Client disconnected");
                break;
            }

            rx_buffer[len] = 0;
            ESP_LOGI(TAG, "Received: %s", rx_buffer);

            // Echo back (for debugging)
            send(client_fd, "OK\n", 3, 0);
        }

        close(client_fd);
    }

    close(server_fd);

}

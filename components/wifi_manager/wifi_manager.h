#pragma once

#include "esp_err.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef void (*wifi_on_connected_cb_t)(void);
typedef void (*wifi_on_disconnected_cb_t)(void);

esp_err_t wifi_manager_init(const char *ssid,
                            const char *password,
                            wifi_on_connected_cb_t on_connected,
                            wifi_on_disconnected_cb_t on_disconnected);

#ifdef __cplusplus
}
#endif

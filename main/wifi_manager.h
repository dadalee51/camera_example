#pragma once

#include "esp_err.h"
#include "esp_event.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t wifi_init_sta(void);
void wifi_disconnect(void);
bool wifi_is_connected(void);
esp_err_t wifi_wait_for_connection(uint32_t timeout_ms);

#ifdef __cplusplus
}
#endif
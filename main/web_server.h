#pragma once

#include "esp_err.h"
#include "esp_http_server.h"

#ifdef __cplusplus
extern "C" {
#endif

esp_err_t start_webserver(void);
void stop_webserver(void);
esp_err_t broadcast_frame(uint8_t *frame_data, size_t frame_len);

#ifdef __cplusplus
}
#endif
idf_component_register(SRCS take_picture.c wifi_manager.c web_server.c
                        PRIV_INCLUDE_DIRS .
                        PRIV_REQUIRES nvs_flash esp_psram esp_wifi esp_netif esp_event esp_http_server esp_https_server esp-tls
                        EMBED_FILES index.html servercert.pem prvtkey.pem) 

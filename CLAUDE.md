# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Development Commands

This is an ESP-IDF project implementing an HTTPS camera streaming server for ESP32-S3 with WebSocket support.

### Essential Commands
```bash
# Configure WiFi credentials (REQUIRED)
idf.py menuconfig
# Navigate to: Component config → Example Configuration
# Set WiFi SSID and Password

# Build the project
idf.py build

# Flash and monitor (most common development command)
idf.py -p /dev/ttyUSB0 flash monitor

# Clean build
idf.py clean

# Full clean (removes entire build directory)
idf.py fullclean

# Set target chip (important for this camera project)
idf.py set-target esp32s3    # Currently configured target

# Development workflow
idf.py -p /dev/ttyUSB0 clean flash monitor

# Check memory usage
idf.py size
```

### Port Configuration
- Replace `/dev/ttyUSB0` with the appropriate serial port for your system
- On Windows: typically `COM3`, `COM4`, etc.
- On macOS: typically `/dev/cu.usbserial-*`

## Project Architecture

### Core Structure
- **main/take_picture.c**: Main application coordinating camera, WiFi, and web server
- **main/wifi_manager.c/h**: WiFi connection management
- **main/web_server.c/h**: HTTPS server with WebSocket streaming support
- **main/index.html**: Web client interface for viewing camera stream
- **main/servercert.pem/prvtkey.pem**: Self-signed SSL certificates for HTTPS
- **main/CMakeLists.txt**: Component build configuration with embedded files
- **main/idf_component.yml**: Component dependencies

### Streaming Architecture
**Video Streaming Pipeline:**
1. Camera captures JPEG frames at 30 FPS (33ms intervals)
2. Frames are broadcast to all connected WebSocket clients
3. Web browser receives binary WebSocket frames and displays them
4. HTTPS ensures secure connection for modern browsers

**Network Stack:**
- WiFi Station Mode → IP connectivity
- HTTPS Server (port 443) → SSL/TLS encryption
- WebSocket over HTTPS → Real-time binary frame streaming
- MJPEG format → Direct browser compatibility

### Camera Implementation
- Supports multiple board configurations (WROVER-KIT, ESP32CAM AiThinker, ESP32-S3 variants)
- Currently configured for `BOARD_ESP32S3_GOOUUU` (line 14 in take_picture.c)
- Uses JPEG format with QVGA frame size for optimal streaming performance
- PSRAM enabled for frame buffer storage
- 30 FPS streaming rate (adjustable via vTaskDelay in camera_streaming_task)

### Hardware Configuration
Pin mappings are defined per board type using preprocessor directives. To change board:
1. Modify the `#define BOARD_*` selection in take_picture.c:14
2. Rebuild the project

### Dependencies
- **espressif/esp32-camera**: Camera driver
- **espressif/esp_tls**: TLS/SSL support for HTTPS
- **esp_wifi**: WiFi connectivity
- **esp_http_server**: HTTP server with WebSocket support
- **esp_https_server**: HTTPS server functionality
- **nvs_flash**: Non-volatile storage for WiFi credentials

### Key Configuration Notes
- PSRAM enabled and required for camera frame buffers
- CPU frequency set to 240MHz for optimal performance
- WebSocket support enabled via CONFIG_HTTPD_WS_SUPPORT
- Self-signed SSL certificates generated for HTTPS
- Increased task stack sizes for networking operations

### Usage Instructions
1. Configure WiFi credentials via `idf.py menuconfig`
2. Build and flash the project
3. Monitor serial output to get the ESP32's IP address
4. Connect to `https://[ESP32_IP_ADDRESS]` in a web browser
5. Accept the self-signed certificate warning
6. Click "Connect" to start streaming

### Web Interface Features
- Real-time MJPEG video streaming
- Connection status indicators  
- Frame rate and data usage statistics
- Automatic reconnection handling
- Responsive design for mobile and desktop

### Troubleshooting
- Ensure WiFi credentials are correctly configured
- Check serial monitor for IP address and connection status
- Accept browser certificate warnings for self-signed SSL
- Verify ESP32 and browser are on the same network
- Monitor memory usage if experiencing stability issues
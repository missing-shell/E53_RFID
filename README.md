| Supported Targets | ESP32 | ESP32-C2 | ESP32-C3 | ESP32-C6 | ESP32-H2 | ESP32-S2 | ESP32-S3 |
| ----------------- | ----- | -------- | -------- | -------- | -------- | -------- | -------- |

## MFRC522

- 更多详细信息参照[MFRC522.md](docs/MFRC522/MFRC522.md)

### SPI通信

#### Connections

MFRC522 引脚连接:
|      | ESP32c6 |
| ---- | --------|
| Host | SPI2    |
| VCC  | 3.3V    |
| GND  | GND     |
| MOSI | 5       |
| MISO | 22      |
| SDA  | 21      |
| SCK  | 4       |  

### Notes

If you meet timeout issues, please check your connections.

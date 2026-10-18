// Práctica 1 · Datos de la plataforma (núcleo Arduino-ESP32 3.x)
#include <Arduino.h>
#include "esp_mac.h"
void setup() {
  Serial.begin(115200);
  delay(1500); // tiempo para abrir el monitor serie
  uint8_t mac[6];
  esp_read_mac(mac, ESP_MAC_WIFI_STA);

  uint16_t rev = ESP.getChipRevision(); // formato MXX en el núcleo 3.x: 301 = v3.1
  Serial.printf("Chip : %s v%u.%u, %u nucleo(s)\n", ESP.getChipModel(),
rev / 100, rev % 100, (unsigned)ESP.getChipCores());
  Serial.printf("CPU : %lu MHz\n", (unsigned long)ESP.getCpuFreqMHz());
  Serial.printf("Flash : %lu bytes\n", (unsigned long)ESP.getFlashChipSize());
  Serial.printf("Heap : %lu total, %lu libre, bloque max. %lu\n",
                (unsigned long)ESP.getHeapSize(), (unsigned long)ESP.getFreeHeap(),
                (unsigned long)ESP.getMaxAllocHeap());
  Serial.printf("PSRAM : %lu bytes\n", (unsigned long)ESP.getPsramSize());
  Serial.printf("Firmware : %lu bytes (particion OTA siguiente: %lu)\n",
              (unsigned long)ESP.getSketchSize(), (unsigned long)ESP.getFreeSketchSpace());
  Serial.printf("Nucleo / IDF : %s / %s\n", ESP.getCoreVersion(), ESP.getSdkVersion());
  Serial.printf("MAC Wi-Fi (STA): %02X:%02X:%02X:%02X:%02X:%02X\n",
                mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}
void loop() {}


"/Users/g0xk3r/Library/Arduino15/packages/esp32/tools/esp-x32/2601/bin/xtensa-esp32-elf-size" -A "/Users/g0xk3r/Library/Caches/arduino/sketches/7F69F89BED3555566C5ADD4AD5B1ABFA/sketch_oct17a.ino.elf"
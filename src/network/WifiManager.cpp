#include "WifiManager.h"
#include "../secrets.h"

void WifiManager::begin() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("[WiFi] 연결 중");
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
    delay(300);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n[WiFi] 연결됨: " + WiFi.localIP().toString());
  } else {
    Serial.println("\n[WiFi] 연결 실패 - 백그라운드에서 재시도 예정");
  }
}

void WifiManager::loop() {
  if (WiFi.status() != WL_CONNECTED && millis() - lastAttempt > retryInterval) {
    lastAttempt = millis();
    Serial.println("[WiFi] 재연결 시도...");
    WiFi.reconnect();
  }
}

bool WifiManager::isConnected() {
  return WiFi.status() == WL_CONNECTED;
}

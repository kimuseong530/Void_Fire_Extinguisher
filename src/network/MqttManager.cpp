#include "MqttManager.h"
#include "../secrets.h"
#include "../config.h"

void MqttManager::begin() {
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void MqttManager::reconnect() {
  if (millis() - lastAttempt < 3000) return;
  lastAttempt = millis();

  Serial.println("[MQTT] 연결 시도...");
  if (client.connect(MQTT_CLIENT_ID)) {
    Serial.println("[MQTT] 연결됨");
  } else {
    Serial.print("[MQTT] 연결 실패, rc=");
    Serial.println(client.state());
  }
}

void MqttManager::loop() {
  if (!client.connected()) {
    reconnect();
  } else {
    client.loop();
  }
}

void MqttManager::publish(const char* topic, const String& payload) {
  if (client.connected()) {
    client.publish(topic, payload.c_str());
  }
}

bool MqttManager::isConnected() {
  return client.connected();
}

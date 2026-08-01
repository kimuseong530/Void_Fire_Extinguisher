#pragma once
#include <PubSubClient.h>
#include <WiFi.h>

class MqttManager {
public:
  void begin();
  void loop();
  void publish(const char* topic, const String& payload);
  bool isConnected();

private:
  WiFiClient espClient;
  PubSubClient client{espClient};
  void reconnect();
  unsigned long lastAttempt = 0;
};

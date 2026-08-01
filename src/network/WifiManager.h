#pragma once
#include <WiFi.h>

class WifiManager {
public:
  void begin();
  void loop();
  bool isConnected();

private:
  unsigned long lastAttempt = 0;
  const unsigned long retryInterval = 5000;
};

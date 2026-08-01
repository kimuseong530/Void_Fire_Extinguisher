#include "NetworkTask.h"
#include "../state/SharedState.h"
#include "../network/WifiManager.h"
#include "../network/MqttManager.h"
#include "../payload/PayloadBuilder.h"
#include "../config.h"

void NetworkTask(void* pvParameters) {
  WifiManager wifi;
  MqttManager mqtt;
  wifi.begin();
  mqtt.begin();

  InputState inputState = {};
  ImuState imuState = {};

  const TickType_t xFrequency = pdMS_TO_TICKS(PUBLISH_INTERVAL_MS);   // 10Hz
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    wifi.loop();
    mqtt.loop();

    xQueuePeek(inputStateQueue, &inputState, 0);
    xQueuePeek(imuStateQueue, &imuState, 0);

    String payload = PayloadBuilder::build(inputState, imuState);
    mqtt.publish(MQTT_TOPIC, payload);

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

#include "ImuTask.h"
#include "../state/SharedState.h"
#include "../sensors/ImuManager.h"

void ImuTask(void* pvParameters) {
  ImuManager imu;
  if (!imu.begin()) {
    Serial.println("[ImuTask] MPU6050 초기화 실패 - 배선 확인 필요");
  }

  const TickType_t xFrequency = pdMS_TO_TICKS(20);   // 50Hz
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    ImuData data = imu.read();
    ImuState state = { data.ax, data.ay, data.az, data.gx, data.gy, data.gz };
    xQueueOverwrite(imuStateQueue, &state);

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

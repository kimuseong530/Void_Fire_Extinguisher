#include <Arduino.h>
#include "config.h"
#include "state/SharedState.h"
#include "tasks/InputTask.h"
#include "tasks/ImuTask.h"
#include "tasks/NetworkTask.h"

void setup() {
  Serial.begin(115200);
  delay(300);

  initSharedState();

  // xTaskCreatePinnedToCore(함수, 이름, 스택크기(byte), 파라미터, 우선순위, 핸들, 코어)
  xTaskCreatePinnedToCore(InputTask,   "InputTask",   TASK_STACK_INPUT,   nullptr, 2, nullptr, 1);
  xTaskCreatePinnedToCore(ImuTask,     "ImuTask",     TASK_STACK_IMU,     nullptr, 1, nullptr, 1);
  xTaskCreatePinnedToCore(NetworkTask, "NetworkTask", TASK_STACK_NETWORK, nullptr, 2, nullptr, 0);

  Serial.println("[main] 태스크 3개 생성 완료");
}

void loop() {
  // 모든 작업은 FreeRTOS 태스크가 담당하므로 기본 loopTask는 자기 자신을 삭제
  vTaskDelete(NULL);
}

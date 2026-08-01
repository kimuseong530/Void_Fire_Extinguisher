#include "SharedState.h"

QueueHandle_t inputStateQueue = nullptr;
QueueHandle_t imuStateQueue = nullptr;

void initSharedState() {
  inputStateQueue = xQueueCreate(1, sizeof(InputState));
  imuStateQueue = xQueueCreate(1, sizeof(ImuState));

  if (inputStateQueue == nullptr || imuStateQueue == nullptr) {
    Serial.println("[SharedState] 큐 생성 실패 - 메모리 부족 가능성");
  }
}

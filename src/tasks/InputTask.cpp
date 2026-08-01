#include "InputTask.h"
#include "../state/SharedState.h"
#include "../input/InputManager.h"
#include "../input/SwitchManager.h"
#include "../input/LeverManager.h"

void InputTask(void* pvParameters) {
  InputManager keypad;
  SwitchManager switches;
  LeverManager lever;

  keypad.begin();
  switches.begin();
  lever.begin();

  const TickType_t xFrequency = pdMS_TO_TICKS(20);   // 50Hz
  TickType_t xLastWakeTime = xTaskGetTickCount();

  for (;;) {
    keypad.update();
    switches.update();
    lever.update();

    InputState state = {
      keypad.isUp(), keypad.isDown(), keypad.isLeft(), keypad.isRight(), keypad.isAux(),
      switches.isPinPulled(), switches.isGripped(), lever.isPressed()
    };
    xQueueOverwrite(inputStateQueue, &state);

    vTaskDelayUntil(&xLastWakeTime, xFrequency);
  }
}

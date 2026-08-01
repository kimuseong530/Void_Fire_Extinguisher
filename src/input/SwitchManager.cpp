#include "SwitchManager.h"
#include "../config.h"

void SwitchManager::begin() {
  safetyPin.attach(PIN_SAFETY_PIN, INPUT_PULLUP);
  safetyPin.interval(DEBOUNCE_MS);

  nozzleGrip.attach(PIN_NOZZLE_GRIP, INPUT_PULLUP);
  nozzleGrip.interval(DEBOUNCE_MS);
}

void SwitchManager::update() {
  safetyPin.update();
  nozzleGrip.update();
}

int SwitchManager::isPinPulled() {
  return safetyPin.read() == LOW ? 1 : 0;
}

int SwitchManager::isGripped() {
  return nozzleGrip.read() == LOW ? 1 : 0;
}

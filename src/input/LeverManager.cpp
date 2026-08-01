#include "LeverManager.h"
#include "../config.h"

void LeverManager::begin() {
  lever.attach(PIN_LEVER, INPUT_PULLUP);
  lever.interval(DEBOUNCE_MS);
}

void LeverManager::update() {
  lever.update();
}

int LeverManager::isPressed() {
  return lever.read() == LOW ? 1 : 0;
}

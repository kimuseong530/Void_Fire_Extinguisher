#include "InputManager.h"
#include "../config.h"

void InputManager::begin() {
  // ADC1 채널(GPIO34)은 input-only 핀이라 pinMode 설정 불필요
}

InputManager::Key InputManager::readKey(int adcValue) {
  if (adcValue > KEY_THRESH_NONE) return KEY_NONE;
  if (adcValue < KEY_THRESH_RIGHT) return KEY_RIGHT;
  if (adcValue < KEY_THRESH_UP)    return KEY_UP;
  if (adcValue < KEY_THRESH_DOWN)  return KEY_DOWN;
  if (adcValue < KEY_THRESH_LEFT)  return KEY_LEFT;
  if (adcValue < KEY_THRESH_AUX)   return KEY_AUX;
  return KEY_NONE;
}

void InputManager::update() {
  int raw = analogRead(PIN_KEYPAD_ANALOG);
  currentKey = readKey(raw);
}

int InputManager::isUp()    { return currentKey == KEY_UP ? 1 : 0; }
int InputManager::isDown()  { return currentKey == KEY_DOWN ? 1 : 0; }
int InputManager::isLeft()  { return currentKey == KEY_LEFT ? 1 : 0; }
int InputManager::isRight() { return currentKey == KEY_RIGHT ? 1 : 0; }
int InputManager::isAux()   { return currentKey == KEY_AUX ? 1 : 0; }

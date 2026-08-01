#pragma once
#include <Arduino.h>

class InputManager {
public:
  void begin();
  void update();

  int isUp();
  int isDown();
  int isLeft();
  int isRight();
  int isAux();

private:
  enum Key { KEY_NONE, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_AUX };
  Key currentKey = KEY_NONE;
  Key readKey(int adcValue);
};

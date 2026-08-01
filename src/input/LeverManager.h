#pragma once
#include <Bounce2.h>

class LeverManager {
public:
  void begin();
  void update();
  int isPressed();

private:
  Bounce lever;
};

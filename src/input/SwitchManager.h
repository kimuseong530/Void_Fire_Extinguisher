#pragma once
#include <Bounce2.h>

class SwitchManager {
public:
  void begin();
  void update();

  int isPinPulled();
  int isGripped();

private:
  Bounce safetyPin;
  Bounce nozzleGrip;
};

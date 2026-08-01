#pragma once
#include <Arduino.h>
#include "../state/SharedState.h"

class PayloadBuilder {
public:
  static String build(const InputState& input, const ImuState& imu);
};

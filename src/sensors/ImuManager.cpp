#include "ImuManager.h"
#include <Wire.h>
#include "../config.h"

bool ImuManager::begin() {
  Wire.begin(PIN_MPU_SDA, PIN_MPU_SCL);
  return mpu.begin();
}

ImuData ImuManager::read() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  return {
    a.acceleration.x, a.acceleration.y, a.acceleration.z,
    g.gyro.x, g.gyro.y, g.gyro.z
  };
}

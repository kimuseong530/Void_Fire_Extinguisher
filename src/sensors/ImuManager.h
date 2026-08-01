#pragma once
#include <Adafruit_MPU6050.h>

struct ImuData {
  float ax, ay, az;   // m/s^2, raw
  float gx, gy, gz;   // rad/s, raw
};

class ImuManager {
public:
  bool begin();
  ImuData read();

private:
  Adafruit_MPU6050 mpu;
};

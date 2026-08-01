#include "PayloadBuilder.h"
#include <ArduinoJson.h>

String PayloadBuilder::build(const InputState& input, const ImuState& imu) {
  StaticJsonDocument<256> doc;

  doc["up"] = input.up;
  doc["down"] = input.down;
  doc["left"] = input.left;
  doc["right"] = input.right;
  doc["aux"] = input.aux;
  doc["pin"] = input.pin;
  doc["grip"] = input.grip;
  doc["spray"] = input.spray;

  doc["ax"] = imu.ax;
  doc["ay"] = imu.ay;
  doc["az"] = imu.az;
  doc["gx"] = imu.gx;
  doc["gy"] = imu.gy;
  doc["gz"] = imu.gz;

  String output;
  serializeJson(doc, output);
  return output;
}

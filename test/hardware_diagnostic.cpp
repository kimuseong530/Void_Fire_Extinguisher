// ============================================================
// 하드웨어 진단 테스트 (키패드 제외 버전)
//
// 목적: 안전핀 스위치, 노즐그립 스위치, 분사 레버, MPU6050이
//       각각 정상 동작하는지 시리얼 모니터로 한눈에 확인.
//       키패드는 제외 (별도 keypad_test.cpp로 확인)
// ============================================================

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Bounce2.h>

#define PIN_SAFETY_PIN 25
#define PIN_NOZZLE_GRIP 26
#define PIN_LEVER 27
#define PIN_MPU_SDA 21
#define PIN_MPU_SCL 22
#define DEBOUNCE_MS 25

Adafruit_MPU6050 mpu;
bool mpuOk = false;

Bounce safetyPin;
Bounce nozzleGrip;
Bounce lever;

unsigned long lastPrint = 0;
const unsigned long PRINT_INTERVAL_MS = 300;

void setup() {
  Serial.begin(115200);
  delay(500);

  safetyPin.attach(PIN_SAFETY_PIN, INPUT_PULLUP);
  safetyPin.interval(DEBOUNCE_MS);
  nozzleGrip.attach(PIN_NOZZLE_GRIP, INPUT_PULLUP);
  nozzleGrip.interval(DEBOUNCE_MS);
  lever.attach(PIN_LEVER, INPUT_PULLUP);
  lever.interval(DEBOUNCE_MS);

  Wire.begin(PIN_MPU_SDA, PIN_MPU_SCL);
  mpuOk = mpu.begin();

  Serial.println();
  Serial.println("========================================");
  Serial.println(" 하드웨어 진단 테스트 (키패드 제외)");
  Serial.println("========================================");
  if (!mpuOk) {
    Serial.println("[경고] MPU6050을 찾지 못했습니다 - VCC/GND/SDA/SCL 배선 확인");
  } else {
    Serial.println("[확인] MPU6050 정상 인식됨");
  }
  Serial.println("스위치/레버를 눌러보면서 아래 값이 바뀌는지 확인하세요.");
  Serial.println();
}

void loop() {
  safetyPin.update();
  nozzleGrip.update();
  lever.update();

  if (millis() - lastPrint < PRINT_INTERVAL_MS) return;
  lastPrint = millis();

  bool pinPulled = (safetyPin.read() == LOW);
  bool grip      = (nozzleGrip.read() == LOW);
  bool spray     = (lever.read() == LOW);

  float ax = 0, ay = 0, az = 0, gx = 0, gy = 0, gz = 0;
  if (mpuOk) {
    sensors_event_t a, g, temp;
    mpu.getEvent(&a, &g, &temp);
    ax = a.acceleration.x; ay = a.acceleration.y; az = a.acceleration.z;
    gx = g.gyro.x;         gy = g.gyro.y;         gz = g.gyro.z;
  }

  Serial.println("----------------------------------------");
  Serial.printf("[안전핀]    %s\n", pinPulled ? "누름" : "안눌림");
  Serial.printf("[노즐그립]  %s\n", grip ? "누름" : "안눌림");
  Serial.printf("[분사레버]  %s\n", spray ? "누름" : "안눌림");
  if (mpuOk) {
    Serial.printf("[MPU6050]   가속도(%.2f, %.2f, %.2f)  자이로(%.2f, %.2f, %.2f)\n",
                  ax, ay, az, gx, gy, gz);
  } else {
    Serial.println("[MPU6050]   -- 미인식 --");
  }
}
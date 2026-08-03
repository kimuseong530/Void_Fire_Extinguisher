// ============================================================
// 하드웨어 진단 테스트 펌웨어
//
// 목적: 키패드, 안전핀 스위치, 노즐그립 스위치, 분사 레버, MPU6050이
//       각각 배선대로 정상 동작하는지 시리얼 모니터로 한눈에 확인.
//
// 사용법:
//   1. 이 파일 내용을 복사해서 src/main.cpp 내용을 "임시로" 이걸로 교체
//      (원래 main.cpp는 다른 이름으로 백업해두세요, 예: main.cpp.bak)
//   2. Build → Upload
//   3. Serial Monitor(115200bps) 열기
//   4. 키패드 버튼, 안전핀, 노즐그립, 레버를 하나씩 눌러보며
//      아래 출력 값이 바뀌는지 확인
//   5. 확인 끝나면 원래 main.cpp로 복구
//
// 참고: 이 테스트는 WiFi/MQTT 없이 동작하며, config.h의 핀 정의와
//       동일한 값을 이 파일 안에 직접 넣어뒀습니다.
// ============================================================

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Bounce2.h>

// ── 핀 설정 (본 프로젝트 config.h와 동일) ──────────────
#define PIN_KEYPAD_ANALOG 34
#define PIN_SAFETY_PIN 25
#define PIN_NOZZLE_GRIP 26
#define PIN_LEVER 27
#define PIN_MPU_SDA 21
#define PIN_MPU_SCL 22
#define DEBOUNCE_MS 25

// ── 키패드 임계값 (플레이스홀더) ─────────────────────
const int KEY_THRESH_NONE  = 4000;
const int KEY_THRESH_RIGHT = 300;
const int KEY_THRESH_UP    = 900;
const int KEY_THRESH_DOWN  = 1700;
const int KEY_THRESH_LEFT  = 2600;
const int KEY_THRESH_AUX   = 3500;

Adafruit_MPU6050 mpu;
bool mpuOk = false;

Bounce safetyPin;
Bounce nozzleGrip;
Bounce lever;

unsigned long lastPrint = 0;
const unsigned long PRINT_INTERVAL_MS = 300;

const char* keyName(int raw) {
  if (raw > KEY_THRESH_NONE)  return "-";
  if (raw < KEY_THRESH_RIGHT) return "RIGHT";
  if (raw < KEY_THRESH_UP)    return "UP";
  if (raw < KEY_THRESH_DOWN)  return "DOWN";
  if (raw < KEY_THRESH_LEFT)  return "LEFT";
  if (raw < KEY_THRESH_AUX)   return "AUX";
  return "-";
}

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
  Serial.println(" 소화기 컨트롤러 하드웨어 진단 테스트");
  Serial.println("========================================");
  if (!mpuOk) {
    Serial.println("[경고] MPU6050을 찾지 못했습니다 - VCC/GND/SDA/SCL 배선 확인");
  } else {
    Serial.println("[확인] MPU6050 정상 인식됨");
  }
  Serial.println("버튼/레버를 눌러보면서 아래 값이 바뀌는지 확인하세요.");
  Serial.println();
}

void loop() {
  safetyPin.update();
  nozzleGrip.update();
  lever.update();

  if (millis() - lastPrint < PRINT_INTERVAL_MS) return;
  lastPrint = millis();

  int raw = analogRead(PIN_KEYPAD_ANALOG);
  const char* key = keyName(raw);

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
  Serial.printf("[키패드]    RAW=%4d   -> %s\n", raw, key);
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
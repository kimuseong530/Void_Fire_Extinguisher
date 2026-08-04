// ============================================================
// [단독 테스트] 키패드 (YwRobot 아날로그 조이스틱형 키패드)
//
// 목적: 키패드 신호선(GPIO34)의 raw ADC 값과, 그 값이 어떤 버튼으로
//       해석되는지 확인. 이 값으로 config.h의 KEY_THRESH_* 실측도 가능.
//
// 배선: 키패드 VCC → 3.3V, GND → GND, 신호선 → GPIO34
// ============================================================

#include <Arduino.h>

#define PIN_KEYPAD_ANALOG 34

// 3.3V 구동 기준 임계값 (플레이스홀더 - 실측 후 교체)
const int KEY_THRESH_NONE  = 4000;
const int KEY_THRESH_RIGHT = 300;
const int KEY_THRESH_UP    = 900;
const int KEY_THRESH_DOWN  = 1700;
const int KEY_THRESH_LEFT  = 2600;
const int KEY_THRESH_AUX   = 3500;

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
  Serial.println();
  Serial.println("========================================");
  Serial.println(" 키패드(조이스틱) 단독 테스트");
  Serial.println(" 버튼을 눌러보며 RAW 값과 판정 결과를 확인하세요");
  Serial.println("========================================");
}

void loop() {
  int raw = analogRead(PIN_KEYPAD_ANALOG);
  Serial.printf("RAW=%4d   -> %s\n", raw, keyName(raw));
  delay(200);
}
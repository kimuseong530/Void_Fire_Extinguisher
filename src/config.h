#pragma once

// ── MQTT ────────────────────────────────────
#define MQTT_TOPIC "Nova/Extinguisher"
#define MQTT_CLIENT_ID "ESP32-Extinguisher"
#define PUBLISH_INTERVAL_MS 100   // 10Hz

// ── 키패드 (YwRobot, 아날로그 저항분배 방식) ──
// ADC1 채널만 WiFi와 함께 안정적으로 쓸 수 있음 → GPIO34 고정
#define PIN_KEYPAD_ANALOG 34

// ── 택트스위치 / 레버 ───────────────────────
#define PIN_SAFETY_PIN 25     // 안전핀
#define PIN_NOZZLE_GRIP 26    // 노즐 그립
#define PIN_LEVER 27          // SS-5GL2 분사 레버

// ── MPU6050 (I2C, ESP32 기본 핀) ────────────
#define PIN_MPU_SDA 21
#define PIN_MPU_SCL 22

// ── 디바운스 ─────────────────────────────────
#define DEBOUNCE_MS 25

// ── 키패드 아날로그 임계값 (플레이스홀더) ─────
// ⚠️ 3.3V 구동 기준 실측 후 반드시 교체할 것
#define KEY_THRESH_NONE   4000
#define KEY_THRESH_RIGHT  300
#define KEY_THRESH_UP     900
#define KEY_THRESH_DOWN   1700
#define KEY_THRESH_LEFT   2600
#define KEY_THRESH_AUX    3500

// ── FreeRTOS 태스크 설정 ─────────────────────
#define TASK_STACK_INPUT   2048
#define TASK_STACK_IMU     2048
#define TASK_STACK_NETWORK 4096

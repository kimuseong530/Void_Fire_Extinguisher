# fire-extinguisher-controller

화재 탈출 시뮬레이션 시스템 — 소화기 컨트롤러 펌웨어 (ESP32 + FreeRTOS + MQTT)

## 시작하기

1. VS Code + PlatformIO IDE 확장 설치
2. 이 저장소를 clone 후 폴더 열기
3. `src/secrets.h.example`을 복사해서 `src/secrets.h`로 저장하고, 실제 WiFi SSID/비밀번호, MQTT 브로커 IP로 교체
   (`secrets.h`는 `.gitignore`에 등록되어 있어 커밋되지 않습니다)
4. Build → Upload → Serial Monitor 순서로 진행

## 아키텍처

FreeRTOS 태스크 3개로 구성:

| 태스크 | 담당 | 주기 | 코어 |
|---|---|---|---|
| InputTask | 키패드/스위치/레버 폴링 | 20ms | 1 |
| ImuTask | MPU6050 읽기 | 20ms | 1 |
| NetworkTask | WiFi/MQTT 유지, publish | 100ms | 0 |

태스크 간 데이터는 길이 1 큐(`xQueueOverwrite`/`xQueuePeek`)로 공유합니다. (`src/state/SharedState.h`)

## 배선

| 부품 | ESP32 핀 |
|---|---|
| 키패드 신호선 | GPIO 34 (VCC는 3.3V) |
| 안전핀 스위치 | GPIO 25 |
| 노즐그립 스위치 | GPIO 26 |
| SS-5GL2 레버 | GPIO 27 |
| MPU6050 SDA | GPIO 21 (VCC는 3.3V) |
| MPU6050 SCL | GPIO 22 |

## MQTT 통신 규격

- 토픽: `Nova/Extinguisher`
- 주기: 10Hz (100ms)
- QoS: 0

```json
{"up":0,"down":0,"left":0,"right":1,"aux":0,"pin":0,"grip":1,"spray":1,
 "ax":-1.20,"ay":9.65,"az":2.10,"gx":0.03,"gy":-0.08,"gz":0.15}
```

## 남은 작업

- [ ] `config.h`의 `KEY_THRESH_*` 값을 3.3V 기준 실측값으로 교체
- [ ] SS-5GL2 COM/NO 단자 실측 후 배선 확정
- [ ] Mosquitto 브로커 설정 및 `secrets.h`의 `MQTT_SERVER` 확인

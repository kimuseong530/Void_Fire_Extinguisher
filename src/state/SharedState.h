#pragma once
#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>

// InputTask가 채우고 NetworkTask가 읽음
struct InputState {
  int up, down, left, right, aux;
  int pin, grip, spray;
};

// ImuTask가 채우고 NetworkTask가 읽음
struct ImuState {
  float ax, ay, az;
  float gx, gy, gz;
};

// 길이 1 큐 — 항상 "가장 최근 값"만 유지
extern QueueHandle_t inputStateQueue;
extern QueueHandle_t imuStateQueue;

void initSharedState();

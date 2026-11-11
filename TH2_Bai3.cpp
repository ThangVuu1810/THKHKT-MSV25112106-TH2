#include <Arduino.h>
#include <WiFi.h>
#include "esp_pm.h"
#include "esp_sleep.h"

#define LED 26

int cnt = 0;

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  delay(1000);
}

void loop() {
  cnt++;
  Serial.printf(">loop:%d\n", cnt);

  // Active
  WiFi.mode(WIFI_STA);
  WiFi.begin("WIFI_TEST", "12345678");
  for (int i = 0; i < 6; i++) {
    digitalWrite(LED, HIGH);
    delay(250);
    digitalWrite(LED, LOW);
    delay(250);
  }

  // Modem-sleep
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
  for (int i = 0; i < 3; i++) {
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }

  // Light-sleep
  digitalWrite(LED, LOW);
  Serial.flush();
  esp_sleep_enable_timer_wakeup(3000000ULL);
  esp_light_sleep_start();
  Serial.printf(">wake_light_cnt:%d\n", cnt);

  // Deep-sleep
  digitalWrite(LED, LOW);
  Serial.flush();
  esp_sleep_enable_timer_wakeup(4000000ULL);
  esp_deep_sleep_start();
}

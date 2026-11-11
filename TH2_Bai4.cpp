#include <Arduino.h>

#define LED_PIN 26
#define BUTTON_PIN GPIO_NUM_25

RTC_DATA_ATTR int soLanThuc = 0;
int demThuong = 0;

void inNguyenNhan() {
  esp_sleep_wakeup_cause_t reason = esp_sleep_get_wakeup_cause();
  if (reason == ESP_SLEEP_WAKEUP_EXT0) {
    Serial.println(">> Thuc day boi: NUT NHAN D25 (ext0)");
  } else if (reason == ESP_SLEEP_WAKEUP_TIMER) {
    Serial.println(">> Thuc day boi: TIMER DINH KY");
  } else {
    Serial.printf(">> Khoi dong lan dau / ly do khac: %d\n", reason);
  }
}

void setup() {
  Serial.begin(115200);
  delay(500);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);

  soLanThuc++;
  demThuong++;

  Serial.println("\n-------------------------------------------");
  Serial.printf("So lan thuc (RTC Memory): %d\n", soLanThuc);
  Serial.printf("Dem thuong  (RAM thuong):  %d\n", demThuong);
  inNguyenNhan();

  Serial.println("Chay task trong 3s...");
  delay(3000);

  Serial.println("Vao Deep Sleep (ngu 5s hoac bam nut D25)...");
  digitalWrite(LED_PIN, LOW);

  esp_sleep_enable_timer_wakeup(5ULL * 1000000ULL);
  esp_sleep_enable_ext0_wakeup(BUTTON_PIN, 0);

  esp_deep_sleep_start();
}

void loop() {
}

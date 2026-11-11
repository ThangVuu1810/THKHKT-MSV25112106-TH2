#include <Arduino.h>

#define LED 26

hw_timer_t* timer = NULL;
volatile unsigned long lastHw = 0;
volatile long jHw = 0;

unsigned long lastMs = 0;
long jMs = 0;

void IRAM_ATTR onTimer() {
  unsigned long t = micros();
  if (lastHw > 0) {
    jHw = (t - lastHw) - 100000;
  }
  lastHw = t;
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);


  #if ESP_ARDUINO_VERSION_MAJOR >= 3
    timer = timerBegin(1000000); 
    timerAttachInterrupt(timer, &onTimer);
    timerAlarm(timer, 100000, true, 0); 
  #else
    timer = timerBegin(0, 80, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 100000, true);
    timerAlarmEnable(timer);
  #endif

  lastMs = micros();
}

void loop() {
  unsigned long now = micros();

  if (now - lastMs >= 100000) {
    jMs = (now - lastMs) - 100000;
    lastMs = now;
  }

  delay(random(10, 30));

  Serial.printf(">j_ms:%ld\n", abs(jMs));
  Serial.printf(">j_hw:%ld\n", abs(jHw));
  delay(100);
}

#include <Arduino.h>

#define LED1 26        
#define ADC_PIN 34     
#define PWR_POT_PIN 27 
#define BTN_PIN 25     

unsigned long lanTruocLed = 0;
unsigned long lanTruocAdc = 0;
unsigned long lanTruocHeart = 0;
bool ledState = false;

void setup() {
  Serial.begin(115200);

  pinMode(PWR_POT_PIN, OUTPUT);
  digitalWrite(PWR_POT_PIN, HIGH);

  pinMode(LED1, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);
}

void loop() {
  unsigned long now = millis();

  if (now - lanTruocLed >= 500) {
    lanTruocLed = now;
    ledState = !ledState;
    digitalWrite(LED1, ledState ? HIGH : LOW);
  }

  if (now - lanTruocAdc >= 2000) {
    lanTruocAdc = now;
    int val = analogRead(ADC_PIN);
    Serial.printf(">bienTro:%d\n", val);
  }

  if (now - lanTruocHeart >= 5000) {
    lanTruocHeart = now;
    Serial.println(">heartbeat:1");
  }
}

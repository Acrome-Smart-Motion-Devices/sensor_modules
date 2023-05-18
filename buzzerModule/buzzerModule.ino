#include <Wire.h>

int buzzerEnable = 0;

#define I2C_SLAVE_ADDRESS   (0x07)
#define BUZZER_PIN          (1)

void setup() {
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
  pinMode(BUZZER_PIN, OUTPUT);
}


void loop() {
  if (buzzerEnable == 1) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    buzzerEnable = 0;
  }
  digitalWrite(BUZZER_PIN, LOW);
}


void requestEvent()
{
  buzzerEnable = 1;
}

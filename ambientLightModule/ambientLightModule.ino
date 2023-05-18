#include <Wire.h>

#define I2C_SLAVE_ADDRESS   (0x05)  

#define AMBIENT_LIGHT_PIN   (A2)

union dataParser {
  uint8_t u8[2];
  uint16_t u16;
} parser;

void setup() {
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
  pinMode(AMBIENT_LIGHT_PIN, INPUT);
}


void loop() {
  parser.u16 = analogRead(AMBIENT_LIGHT_PIN);
  delay(1);
}

void requestEvent() {
  Wire.write(parser.u8[0]);
  Wire.write(parser.u8[1]);
}

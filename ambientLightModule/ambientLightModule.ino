#include <Wire.h>

#define I2C_SLAVE_ADDRESS   (0x05)  

#define AMBIENT_LIGHT_PIN   (A2)

union dataParser {
  uint8_t u8[4];
  float   lux;
} parser;

void setup() {
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
  pinMode(AMBIENT_LIGHT_PIN, INPUT);
}


void loop() {

  // ( (V) / 7.4K ohm ) * 4*10^6 = LUX
  //    V * 540,54 = LUX
  
  parser.lux = analogRead(AMBIENT_LIGHT_PIN) * 540,54;
  delay(1);
}

void requestEvent() {
  Wire.write(parser.u8[0]);
  Wire.write(parser.u8[1]);
  Wire.write(parser.u8[2]);
  Wire.write(parser.u8[3]);
}

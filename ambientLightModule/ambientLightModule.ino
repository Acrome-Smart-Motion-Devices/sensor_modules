#include <Wire.h>

#define ID_OFFSET     6
uint8_t i2cSlaveAdress = 0;

//ID selector
void setupID(){
  pinMode(0, INPUT);
  pinMode(1, INPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);

  int i;
  for(i=4;i>=0;i--) if(digitalRead(i)==1) break;
  if(i == -1) i2cSlaveAdress = 0;

  i2cSlaveAdress = i + ID_OFFSET;
}

#define AMBIENT_LIGHT_PIN   (A2)

union dataParser {
  uint8_t u8[4];
  float   lux;
} parser;

void setup() {
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
  }
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

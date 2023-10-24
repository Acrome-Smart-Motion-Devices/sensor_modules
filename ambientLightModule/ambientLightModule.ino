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
  if(i == -1) i = 0;

  i2cSlaveAdress = i + ID_OFFSET;
}

#define AMBIENT_LIGHT_PIN   (A0)

union dataParser {
  uint8_t   u8[2];
  uint16_t  lux;
} parser;

void setup() {
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
  }
  Wire.onRequest(requestEvent);
}

void loop() {
  //    A * 36*10^5 = LUX
  //    V / R = A
  //    Analog / 1024 * 5 = V
  // 7.4K ohm
  
  //parser.lux = analogRead(AMBIENT_LIGHT_PIN)* 5 / 1024 * 540,54;
  //parser.lux = analogRead(AMBIENT_LIGHT_PIN);
  
  parser.lux =(uint16_t)(analogRead(AMBIENT_LIGHT_PIN) * 2.34375);
  delay(5);
}

void requestEvent() {
  Wire.write(parser.u8[0]);
  Wire.write(parser.u8[1]);
}

#include <Wire.h>
#include <avr/wdt.h>

#define ID_OFFSET     6
uint8_t i2cSlaveAdress = 0;

#define Sensor_ArrySize 16  //** Sensor_ArrySize must be the power of the 2
unsigned int Sensor1Arry[Sensor_ArrySize],Sensor1Sum,Sensor1AVG,Sensor1NewData;
unsigned char Sensor1Indis;

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
  wdt_enable(WDTO_250MS);
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
  Sensor1NewData = analogRead(AMBIENT_LIGHT_PIN);

  // filtering // moving avarage //
  Sensor1Sum = Sensor1Sum + Sensor1NewData - Sensor1Arry[Sensor1Indis];
  Sensor1AVG = Sensor1Sum / Sensor_ArrySize;
  Sensor1Arry[Sensor1Indis] = Sensor1NewData;
  Sensor1Indis ++;
  Sensor1Indis &= (Sensor_ArrySize - 1);
  
  
  parser.lux =(uint16_t)(Sensor1AVG * 2.34375);
  delay(5);
}

void requestEvent() {
  Wire.write(parser.u8[0]);
  Wire.write(parser.u8[1]);
  wdt_reset();
}

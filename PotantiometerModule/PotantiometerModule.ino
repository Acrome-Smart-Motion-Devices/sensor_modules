#include <Wire.h>
#include <avr/wdt.h>

#define ID_OFFSET   36
uint8_t i2cSlaveAdress = 0;

#define Sensor_ArrySize 16  //** Sensor_ArrySize 2 nin katı olmalı
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

#define POTANTIOMETER_PIN   (A0)
uint8_t potantiometer = 0;

void setup() {
  wdt_enable(WDTO_250MS);
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
  }
  Wire.onRequest(requestEvent);
}
void loop() {
  Sensor1NewData = analogRead(POTANTIOMETER_PIN);

  // filtering // moving avarage //
  Sensor1Sum = Sensor1Sum + Sensor1NewData - Sensor1Arry[Sensor1Indis];
  Sensor1AVG = Sensor1Sum / Sensor_ArrySize;
  Sensor1Arry[Sensor1Indis] = Sensor1NewData;
  Sensor1Indis ++;
  Sensor1Indis &= (Sensor_ArrySize - 1);
  
  potantiometer = map(Sensor1AVG,0,1024,0,255);
}

void requestEvent() {
  Wire.write(potantiometer);
  wdt_reset();
}

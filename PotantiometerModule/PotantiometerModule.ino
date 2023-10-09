#include <Wire.h>

#define ID_OFFSET   36
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

#define POTANTIOMETER_PIN   (A0)
uint8_t potantiometer = 0;

void setup() {
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
  }
  Wire.onRequest(requestEvent);
}
void loop() {
  potantiometer = analogRead(POTANTIOMETER_PIN);
}

void requestEvent() {
    Wire.write(potantiometer);
}

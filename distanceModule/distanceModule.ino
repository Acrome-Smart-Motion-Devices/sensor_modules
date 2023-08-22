#include <Wire.h>
#include <NewPing.h>

#define ID_OFFSET   21
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

#define TRIGGER_PIN         (3)
#define ECHO_PIN            (4)
#define MAX_DIST            (200)


union DATA { 
  uint8_t u8[2];
  uint16_t u16;
} dataField;


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DIST);

void setup() {
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
  }
  Wire.onRequest(requestEvent);
}
void loop() {
  uint16_t distance = sonar.ping_cm();
  if (distance >= 200) distance = 200;
  dataField.u16 = distance;
  
}

void requestEvent() {
  Wire.write(dataField.u8[0]);
  Wire.write(dataField.u8[1]);
}

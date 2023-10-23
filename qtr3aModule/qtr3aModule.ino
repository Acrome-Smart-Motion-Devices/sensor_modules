#include <Wire.h>

#define ID_OFFSET   26
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
#define QTR_L   (A0)
#define QTR_M   (A2)
#define QTR_R   (A1)

uint8_t data = 0;

void setup()
{

  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
    Wire.onRequest(requestEvent);
  }
}


void loop()
{
  if (analogRead(QTR_L) > 500){
    data |= (1 << 0);
  }
  else{
    data &= ~(1 << 0);
  }
  
  if (analogRead(QTR_M) > 500){
    data |= (1 << 1);
  }
  else{
    data &= ~(1 << 1);
  }
  
  if (analogRead(QTR_R) > 500){
    data |= (1 << 2);
  }
  else{
    data &= ~(1 << 2);
  }  
}


void requestEvent() {
  Wire.write(data);
}

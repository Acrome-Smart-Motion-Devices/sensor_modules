#include <Wire.h>
#include <Servo.h>

#define ID_OFFSET   31
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



Servo servo;

uint8_t receivedData = 0;   //isaretli sayi almali.  motorun donme yonune gore kontrol et test et.


void setup()
{
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
    Wire.onReceive(receiveEvent);
  }
  
  servo.attach(5);
}

void loop()
{  
  servo.write(receivedData);
}

void receiveEvent(int byteCount)
{ 
    if (byteCount > 0) {
    receivedData = Wire.read();
    }
}

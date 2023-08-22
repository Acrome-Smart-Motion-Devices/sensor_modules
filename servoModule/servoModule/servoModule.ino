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
  if(i == -1) i2cSlaveAdress = 0;

  i2cSlaveAdress = i + ID_OFFSET;
}

#define I2C_MASTER_ADRESS (0x00)
#define servoPin            1

Servo servo;

int8_t val = 0;


void setup()
{
  servo.attach(servoPin);

  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
  }
  Wire.onReceive(receiveEvent);
}

void loop()
{
  Wire.requestFrom(I2C_MASTER_ADRESS, 1);
  while(Wire.available())val = Wire.read();
  
  servo.write(val);

  delay(1);
}

#include <Wire.h>
#include <Servo.h>

#define I2C_SLAVE_ADDRESS (0x20)  //32
#define I2C_MASTER_ADRESS (0x00)
#define servoPin            1

Servo servo;

int8_t val = 0;


void setup()
{
  servo.attach(servoPin);
  Wire.begin(I2C_SLAVE_ADDRESS);
}


void loop()
{
  Wire.requestFrom(I2C_MASTER_ADRESS, 1);
  while(Wire.available())val = Wire.read();
  
  servo.write(val);

  delay(1);
}

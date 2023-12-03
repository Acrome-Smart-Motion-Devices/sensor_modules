#include <Wire.h>

#define ID_OFFSET   16
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

#define JOYSTICK_X        (A0)
#define JOYSTICK_Y        (A1)
#define JOYSTICK_BUTTON   (5)

uint8_t button = 0;
typedef union parser {
  uint8_t   u8[4]; //int w 4 bytes
  int     value;
} parser;

parser x;
parser y;

void setup()
{
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
    Wire.onRequest(requestEvent);
  }
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(JOYSTICK_BUTTON, INPUT_PULLUP);
}


void loop()
{
  x.value = map(analogRead(JOYSTICK_X), 0, 1023, -100, 100);    //mapping 0-1023 to -100 100
  y.value = map(analogRead(JOYSTICK_Y), 0, 1023, -100, 100);
  button = digitalRead(JOYSTICK_BUTTON);  
  delay(1);
}


void requestEvent()
{
  Wire.write(x.u8[0]);
  Wire.write(x.u8[1]);
  Wire.write(x.u8[2]);
  Wire.write(x.u8[3]);
  Wire.write(y.u8[0]);
  Wire.write(y.u8[1]);
  Wire.write(y.u8[2]);
  Wire.write(y.u8[3]);
  Wire.write(button ^ (0x01));
}

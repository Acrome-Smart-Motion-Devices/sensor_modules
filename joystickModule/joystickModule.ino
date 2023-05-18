#include <Wire.h>

#define I2C_SLAVE_ADDRESS 0x9

#define JOYSTICK_X        (A2)
#define JOYSTICK_Y        (A3)
#define JOYSTICK_BUTTON   (1)

uint8_t button = 0;
typedef union parser {
  uint8_t u8[2];
  uint16_t u16;
} parser;

parser x;
parser y;

void setup()
{
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(JOYSTICK_BUTTON, INPUT_PULLUP);
}


void loop()
{
  x.u16 = analogRead(JOYSTICK_X);
  y.u16 = analogRead(JOYSTICK_Y);
  button = digitalRead(JOYSTICK_BUTTON);
  delay(1);
}


void requestEvent()
{
  Wire.write(x.u8[0]);
  Wire.write(x.u8[1]);
  Wire.write(y.u8[0]);
  Wire.write(y.u8[1]);
  Wire.write(button ^ (0x01));
}

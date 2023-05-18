#include <Wire.h>

#define I2C_SLAVE_ADDRESS 0x08  //this slave address
#define buttonPin  3

void setup() {
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
  pinMode(buttonPin, INPUT);
}

void loop() {

}


void requestEvent() {
  int a = digitalRead(buttonPin)^(0x01);
  Wire.write(a);
}

/* ATtiny Pin 1 =   (RESET) N/U                      
ATtiny Pin 2    =   ADC3
ATtiny Pin 3    =   ADC2                          
ATtiny Pin 4    =   GND
ATtiny Pin 5    =   I2C SDA on DS1621  & Mosi     
ATtiny Pin 6    =   Mıso
ATtiny Pin 7    =   I2C SCK on DS1621  & ADC1       
ATtiny Pin 8    =   VCC (2.7-5.5V)
 */


#define I2C_SLAVE_ADDRESS 0x08  //this slave address
#include <TinyWireS.h>
#define buttonPin  3

void setup() {
  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onRequest(requestEvent);
  pinMode(buttonPin, INPUT);
}

void loop() {
}

void requestEvent() {
  TinyWireS.write(digitalRead(buttonPin)^(0x01));
}

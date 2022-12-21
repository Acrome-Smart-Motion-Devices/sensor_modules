/* ATtiny Pin 1 =   (RESET) N/U                      
ATtiny Pin 2    =   ADC3
ATtiny Pin 3    =   ADC2                          
ATtiny Pin 4    =   GND
ATtiny Pin 5    =   I2C SDA on DS1621  & Mosi     
ATtiny Pin 6    =   Mıso
ATtiny Pin 7    =   I2C SCK on DS1621  & ADC1       
ATtiny Pin 8    =   VCC (2.7-5.5V)
 */
uint16_t lightvalue = 0;

#define I2C_SLAVE_ADDRESS 0x05  //this slave address
#include <TinyWireS.h>
#define lightsensor A3
union SensorData { 
  uint8_t sensor8[2];
  uint16_t sensor16;
} uniondata;
void setup() {
  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onRequest(requestEvent);
  pinMode(lightsensor, INPUT);
}
void loop() {
  uniondata.sensor16 = analogRead(lightsensor);
   }
void requestEvent() {
   
  TinyWireS.write(uniondata.sensor8[0]);
  TinyWireS.write(uniondata.sensor8[1]);  
 

 
    
}
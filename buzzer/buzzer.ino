/* ATtiny Pin 1 =   (RESET) N/U                      
ATtiny Pin 2    =   ADC3
ATtiny Pin 3    =   ADC2                          
ATtiny Pin 4    =   GND
ATtiny Pin 5    =   I2C SDA on DS1621  & Mosi     
ATtiny Pin 6    =   Mıso
ATtiny Pin 7    =   I2C SCK on DS1621  & ADC1       
ATtiny Pin 8    =   VCC (2.7-5.5V)
 */

int buzzer_value=0;
#define I2C_SLAVE_ADDRESS 0x07   //this slave address 
#include <TinyWireS.h> 
#define buzzerpin  1
uint32_t time=0;
void setup() {
TinyWireS.begin(I2C_SLAVE_ADDRESS);
TinyWireS.onRequest(requestEvent);
pinMode(buzzerpin,OUTPUT);
}
void loop() {

}
void requestEvent()
{
  while (time<=1000){
analogWrite(buzzerpin, 300);
time+=1;
  }
 time=0;
 analogWrite(buzzerpin, 0);
   }
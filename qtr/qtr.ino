/* ATtiny Pin 1 =   (RESET) N/U                      
ATtiny Pin 2    =   ADC3
ATtiny Pin 3    =   ADC2                          
ATtiny Pin 4    =   GND
ATtiny Pin 5    =   I2C SDA on DS1621  & Mosi     
ATtiny Pin 6    =   Mıso
ATtiny Pin 7    =   I2C SCK on DS1621  & ADC1       
ATtiny Pin 8    =   VCC (2.7-5.5V)
 */

#define I2C_SLAVE_ADDRESS (0x0A)  //this slave address
#include <TinyWireS.h>
#define OUTPUT_SIZE (0x03)    // Size in terms of bytes, default 3 bytes
#define left 1
#define mid 3
#define right 4


int8_t data;
void setup() {
  pinMode(left, INPUT);
  pinMode(right, INPUT);
  pinMode(mid, INPUT);

  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onRequest(requestEvent);
  
  delay(3);

}

void loop() {
data=((digitalRead(left))<<0)|((digitalRead(mid))<<1)|((digitalRead(right))<<2);
//data=((digitalRead(left)));
}

void requestEvent(){
TinyWireS.write(data);
  //for(int i = 0; i < OUTPUT_SIZE; i++){
   // TinyWireS.write(data);
   // }  
  
  
}

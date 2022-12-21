/* ATtiny Pin 1 =   (RESET) N/U                      
ATtiny Pin 2    =   ADC3
ATtiny Pin 3    =   ADC2                          
ATtiny Pin 4    =   GND
ATtiny Pin 5    =   I2C SDA on DS1621  & Mosi     
ATtiny Pin 6    =   Mıso
ATtiny Pin 7    =   I2C SCK on DS1621  & ADC1       
ATtiny Pin 8    =   VCC (2.7-5.5V)
 */
int buton =0;
#define I2C_SLAVE_ADDRESS 0x9   //this slave address 
#include <TinyWireS.h> 
#define joyxpin  A2
#define joyypin  A3
#define joybutpin  1

union SensorData_x { 
  uint8_t sensor8[2];
  uint16_t sensor16;
} xaxis;

union SensorData_y { 
  uint8_t sensor8[2];
  uint16_t sensor16;
} yaxis;



void setup()
{
  TinyWireS.begin(I2C_SLAVE_ADDRESS);
  TinyWireS.onRequest(requestEvent);
  pinMode(joyxpin, INPUT);
  pinMode(joyypin, INPUT);
  pinMode(joybutpin, INPUT_PULLUP);
  }
void loop() 
{
  xaxis.sensor16 = analogRead(joyxpin);
  yaxis.sensor16= analogRead(joyypin);
  buton = digitalRead(joybutpin);
 }

void requestEvent()
{
  TinyWireS.write(xaxis.sensor8[0]);
  TinyWireS.write(xaxis.sensor8[1]);
  TinyWireS.write(yaxis.sensor8[0]);
  TinyWireS.write(yaxis.sensor8[1]);
  TinyWireS.write(buton);
 }
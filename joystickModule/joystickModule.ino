#include <Wire.h>
#include <avr/wdt.h>

#define ID_OFFSET   16
uint8_t i2cSlaveAdress = 0;

#define Sensor_ArrySize 16  //** Sensor_ArrySize 2 nin katı olmalı
unsigned int Sensor1Arry[Sensor_ArrySize],Sensor1Sum,Sensor1AVG,Sensor1NewData;
unsigned char Sensor1Indis;
unsigned int Sensor2Arry[Sensor_ArrySize],Sensor2Sum,Sensor2AVG,Sensor2NewData;
unsigned char Sensor2Indis;

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
  int32_t     value;
} parser;

parser x;
parser y;

void setup()
{
  wdt_enable(WDTO_250MS);
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
  Sensor1NewData = analogRead(JOYSTICK_X);
  Sensor2NewData = analogRead(JOYSTICK_Y);

  // filtering // moving avarage //
  Sensor1Sum = Sensor1Sum + Sensor1NewData - Sensor1Arry[Sensor1Indis];
  Sensor1AVG = Sensor1Sum / Sensor_ArrySize;
  Sensor1Arry[Sensor1Indis] = Sensor1NewData;
  Sensor1Indis ++;
  Sensor1Indis &= (Sensor_ArrySize - 1);  

  Sensor2Sum = Sensor2Sum + Sensor2NewData - Sensor2Arry[Sensor2Indis];
  Sensor2AVG = Sensor2Sum / Sensor_ArrySize;
  Sensor2Arry[Sensor2Indis] = Sensor2NewData;
  Sensor2Indis ++;
  Sensor2Indis &= (Sensor_ArrySize - 1);


  x.value = map(Sensor1AVG, 0, 1023, -100, 100);    //mapping 0-1023 to -100 100
  y.value = map(Sensor2AVG, 0, 1023, 100, -100);
  int button_count = 0;
  for (int i = 0; i < 3; i++) {
    if (digitalRead(JOYSTICK_BUTTON) == HIGH) {
      button_count++;
    }
  }
  if (button_count >=2) {
      button = 0x01;
  }
  else{
    button = 0x00;
  }
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
  wdt_reset();

}

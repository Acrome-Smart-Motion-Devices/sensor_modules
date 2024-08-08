#include <Wire.h>
#include <avr/wdt.h>

#define ID_OFFSET   26
uint8_t i2cSlaveAdress = 0;

#define Sensor_ArrySize 16  //** Sensor_ArrySize must be the power of the 2
unsigned int Sensor1Arry[Sensor_ArrySize],Sensor1Sum,Sensor1AVG,Sensor1NewData;
unsigned char Sensor1Indis;
unsigned int  Sensor2Arry[Sensor_ArrySize],Sensor2Sum,Sensor2AVG,Sensor2NewData;
unsigned char Sensor2Indis;
unsigned int  Sensor3Arry[Sensor_ArrySize],Sensor3Sum,Sensor3AVG,Sensor3NewData;
unsigned char Sensor3Indis;

uint8_t sensor1_filtered;
uint8_t sensor2_filtered;
uint8_t sensor3_filtered;

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
#define QTR_L   (A0)
#define QTR_M   (A2)
#define QTR_R   (A1)

uint8_t data = 0;

void setup()
{
  wdt_enable(WDTO_250MS);
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
    Wire.onRequest(requestEvent);
  }
}


void loop()
{
  Sensor1NewData = analogRead(QTR_L);
  Sensor2NewData = analogRead(QTR_M);
  Sensor3NewData = analogRead(QTR_R);


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

  Sensor3Sum = Sensor3Sum + Sensor3NewData - Sensor3Arry[Sensor3Indis];
  Sensor3AVG = Sensor3Sum / Sensor_ArrySize;
  Sensor3Arry[Sensor3Indis] = Sensor3NewData;
  Sensor3Indis ++;
  Sensor3Indis &= (Sensor_ArrySize - 1);

  sensor1_filtered = map(Sensor1AVG,0,1024,0,255);
  sensor2_filtered = map(Sensor2AVG,0,1024,0,255);
  sensor3_filtered = map(Sensor3AVG,0,1024,0,255);
}


void requestEvent() {
  Wire.write(sensor1_filtered);
  Wire.write(sensor2_filtered);
  Wire.write(sensor3_filtered);
  wdt_reset(); //watchdog timer reset
}

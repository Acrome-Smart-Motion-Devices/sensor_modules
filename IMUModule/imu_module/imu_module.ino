#include <SoftwareWire.h>
#include <Wire.h>
#include <avr/wdt.h>

#define ID_OFFSET   46
#define Sensor_ArrySize 128  //** Sensor_ArrySize 2 nin katı olmalı
uint8_t i2cSlaveAdress = 0;


float  Sensor1Arry[Sensor_ArrySize],Sensor1Sum,Sensor1AVG,Sensor1NewData;
unsigned char Sensor1Indis;

float  Sensor2Arry[Sensor_ArrySize],Sensor2Sum,Sensor2AVG,Sensor2NewData;
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

typedef struct {
  float roll;
  float pitch;
}tIMU __attribute__((packed));

volatile tIMU IMU = {0};
SoftwareWire wire(6,5);

#define MPU6050_ADDRESS 0x68  // MPU-6050'nin I2C adresi
float AccX, AccY, AccZ;
float accAngleX, accAngleY;

void setup() {
  wdt_enable(WDTO_250MS);
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
    Wire.onRequest(requestEvent);
  }

  wire.setTimeout(10);
  wire.begin();
  delay(3);
  wire.beginTransmission(MPU6050_ADDRESS);
  wire.write(0x6B);
  wire.write(0x00);
  wire.endTransmission(true);

  delay(20);
}

void loop() {
  wire.beginTransmission(MPU6050_ADDRESS);
  wire.write(0x3B);
  wire.endTransmission(false);
  wire.requestFrom(MPU6050_ADDRESS, 6, true);

  AccX = (wire.read() << 8 | wire.read()) / 16384.0; // X-axis value
  AccY = (wire.read() << 8 | wire.read()) / 16384.0; // Y-axis value
  AccZ = (wire.read() << 8 | wire.read()) / 16384.0; // Z-axis value

  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; // AccErrorX ~(0.58)
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58; // AccErrorY ~(-1.58)

  Sensor1NewData = accAngleX;
  Sensor2NewData = accAngleY;

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
  
  // 
  IMU.roll = Sensor1AVG;
  IMU.pitch = Sensor2AVG;
}


void requestEvent()
{
  for (uint8_t i = 0; i < sizeof(tIMU); i++) {
    Wire.write(*(((uint8_t*) &IMU) + i));
    wdt_reset();
  }
}

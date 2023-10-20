#include <SoftwareWire.h>
#include <Wire.h>

#define ID_OFFSET   46
uint8_t i2cSlaveAdress = 0;

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
  Serial.begin(9600);
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
  
  
  
  // Verileri oku
  wire.beginTransmission(MPU6050_ADDRESS);
  wire.write(0x3B);
  wire.endTransmission(false);
  wire.requestFrom(MPU6050_ADDRESS, 6, true);

  AccX = (wire.read() << 8 | wire.read()) / 16384.0; // X-axis value
  AccY = (wire.read() << 8 | wire.read()) / 16384.0; // Y-axis value
  AccZ = (wire.read() << 8 | wire.read()) / 16384.0; // Z-axis value

  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - 0.58; // AccErrorX ~(0.58)
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) + 1.58; // AccErrorY ~(-1.58)


  // 
  IMU.roll = accAngleX;
  IMU.pitch = accAngleY;

  delay(10);
}


void requestEvent()
{
  for (uint8_t i = 0; i < sizeof(tIMU); i++) {
    Wire.write(*(((uint8_t*) &IMU) + i));
  }
}

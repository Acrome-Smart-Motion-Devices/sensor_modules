#include <Wire.h>

#define ID_OFFSET       41
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

int LED_R_PIN = 9;
int LED_G_PIN = 6;
int LED_B_PIN = 5;

uint32_t receivedData = 0;

typedef struct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}RGBColor;

RGBColor color;


void setup() {
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
    Wire.onReceive(receiveEvent);
  }
  
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
}

void loop() {
    analogWrite(LED_R_PIN, color.red);
    analogWrite(LED_G_PIN, color.green);
    analogWrite(LED_B_PIN, color.blue);
}

void receiveEvent(int byteCount) {
  if (byteCount >= 3) {
    color.red = Wire.read();    // İlk byte'ı al
    color.green = Wire.read();  // İkinci byte'ı al
    color.blue = Wire.read();   // Üçüncü byte'ı al
    // İstediğiniz işlemleri gerçekleştirin
  }
}

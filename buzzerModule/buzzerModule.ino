#include <Wire.h>

#define ID_OFFSET   11
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
#define BUZZER_PIN          (5)

int buzzerEnable = 0;

void setup() {
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
  }
  Wire.onRequest(requestEvent);
  pinMode(BUZZER_PIN, OUTPUT);
}


void loop() {
//  if (buzzerEnable == 1) {
//    digitalWrite(BUZZER_PIN, HIGH);
//    delay(1000);
//    buzzerEnable = 0;
//  }
//  digitalWrite(BUZZER_PIN, LOW);


  digitalWrite(BUZZER_PIN,HIGH);
  delay(500);
  digitalWrite(BUZZER_PIN,HIGH);
  delay(500);
}


void requestEvent(){
  buzzerEnable = Wire.read();  
}

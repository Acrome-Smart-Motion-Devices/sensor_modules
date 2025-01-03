#include <Wire.h>
#include <avr/wdt.h>
#define ID_OFFSET   1
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
#define buttonPin  5
uint8_t button = 0;

void setup() {
  wdt_enable(WDTO_250MS);
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
    Wire.onRequest(requestEvent);
  }
  pinMode(buttonPin, INPUT);
}

void loop() {
  int button_count = 0;
  for (int i = 0; i < 3; i++) {
    if (digitalRead(buttonPin) == HIGH) {
      button_count++;
    }
  }
  if (button_count >= 2) {
      button = 0x00;
  }
  else{
    button = 0x01;
  }
}


void requestEvent() {
  Wire.write(button);
  wdt_reset();
}

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
  for(i=4;i>=0;i--){
    if(digitalRead(i)==1) break;
  }
  if(i == -1)i = 0;
  i2cSlaveAdress = i + ID_OFFSET;
}
#define BUZZER_PIN          (5)


enum Note {
  NO_NOTE = 0,
  NOTE_C4 = 262,
  NOTE_CS4 = 277,
  NOTE_D4 = 294,
  NOTE_DS4 = 311,
  NOTE_E4 = 330,
  NOTE_F4 = 349,
  NOTE_FS4 = 370,
  NOTE_G4 = 392,
  NOTE_GS4 = 415,
  NOTE_A4 = 440,
  NOTE_AS4 = 466,
  NOTE_B4 = 494,
  NOTE_C5 = 523,
  NOTE_CS5 = 554,
  NOTE_D5 = 587,
  NOTE_DS5 = 622,
  NOTE_E5 = 659,
  NOTE_F5 = 698,
  NOTE_FS5 = 740,
  NOTE_G5 = 784,
  NOTE_GS5 = 831,
  NOTE_A5 = 880,
  NOTE_AS5 = 932,
  NOTE_B5 = 988,
  NOTE_C6 = 1047,
  NOTE_CS6 = 1109,
  NOTE_D6 = 1175,
  NOTE_DS6 = 1245,
  NOTE_E6 = 1319,
  NOTE_F6 = 1397,
  NOTE_FS6 = 1480,
  NOTE_G6 = 1568,
  NOTE_GS6 = 1661,
  NOTE_A6 = 1760,
  NOTE_AS6 = 1865,
  NOTE_B6 = 1976,
  NOTE_C7 = 2093,
  NOTE_CS7 = 2217,
  NOTE_D7 = 2349,
  NOTE_DS7 = 2489,
  NOTE_E7 = 2637,
  NOTE_F7 = 2794,
  NOTE_FS7 = 2960,
  NOTE_G7 = 3136,
  NOTE_GS7 = 3322,
  NOTE_A7 = 3520,
  NOTE_AS7 = 3729,
  NOTE_B7 = 3951,
  NOTE_C8 = 4186
};
//size = 50;

typedef union parser {
  uint8_t   u8[4]; //int w 4 bytes
  int       value;
} parser;

parser buzzerFrequency;

void setup() {
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
    Wire.onReceive(receiveEvent);
  }
  
  pinMode(BUZZER_PIN, OUTPUT);
}


void loop() {
  if(buzzerFrequency.value == NO_NOTE){
    noTone(BUZZER_PIN);
  }
  else{
      tone(BUZZER_PIN, buzzerFrequency.value);
  }
}


void receiveEvent(int byteCount){
  if (byteCount >= 4) {
    buzzerFrequency.u8[0] = Wire.read();    // İlk byte'ı al
    buzzerFrequency.u8[1] = Wire.read();
    buzzerFrequency.u8[2] = Wire.read();
    buzzerFrequency.u8[3] = Wire.read();
}
}

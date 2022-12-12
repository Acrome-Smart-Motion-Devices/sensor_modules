#include <TinyWireS.h>

#define TOGGLE_LED  (1U)      // Put 1 if you wish to toggle a led at pin 0
#if TOGGLE_LED
uint8_t ledState = 0x00;
#endif

void setup() {
  
  #if TOGGLE_LED
  pinMode(0, OUTPUT);
  #endif 
}

void loop() {
  
  #if TOGGLE_LED
  digitalWrite(0, ledState ^= 0x01);
  delay(100);
  #endif
}

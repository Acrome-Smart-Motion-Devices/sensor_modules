#include <TinyWireS.h>


#define SLV_ADDR    (0x05)    // Put your desired slave address to here
#define OUTPUT_SIZE (0x02)    // Size in terms of bytes, default 2 bytess

#define TOGGLE_LED  (1U)      // Put 1 if you wish to toggle a led at pin 0
#if TOGGLE_LED
uint8_t ledState = 0x00;
#endif

union sensDataConverter{      // Union for data manipulation
  uint8_t u8[4];              // and type conversion
  int8_t i8[4];
  uint16_t u16[2];
  int16_t i16[2];
  uint32_t u32;
  int32_t i32;
  float f32;
}sdc;

void setup() {
  
  #if TOGGLE_LED
  pinMode(0, OUTPUT);
  #endif 

  pinMode(3, INPUT);
  TinyWireS.begin(SLV_ADDR);
  TinyWireS.onRequest(requestEvent);
  delay(3);
}

void loop() {
  
  #if TOGGLE_LED
  digitalWrite(0, ledState ^= 0x01);
  #endif
  
  sdc.u32  = analogRead(3);
  TinyWireS_stop_check();
}

void requestEvent(){

  for(int i = 0; i < OUTPUT_SIZE; i++){
    TinyWireS.write(sdc.u8[i]);
    }  
  
  
}

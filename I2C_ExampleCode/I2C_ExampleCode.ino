#include <TinyWireS.h>


#define SLV_ADDR    (0x05)    // Put your desired slave address to here
#define OUTPUT_SIZE (0x02)    // Size in terms of bytes, default 2 bytes

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

  pinMode(3, INPUT);
  TinyWireS.begin(SLV_ADDR);
  TinyWireS.onRequest(requestEvent);
  delay(3);
}

void loop() {
  
  sdc.u32  = analogRead(3);
  TinyWireS_stop_check();
}

void requestEvent(){

  for(int i = 0; i < OUTPUT_SIZE; i++){
    TinyWireS.write(sdc.u8[i]);
    }  
  
  
}

#include <Wire.h>
#include <NewPing.h>

#define TRIGGER_PIN         (3)
#define ECHO_PIN            (4)
#define MAX_DIST            (200)
#define I2C_SLAVE_ADDRESS   (0x06)

union DATA { 
  uint8_t u8[2];
  uint16_t u16;
} dataField;


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DIST);

void setup() {
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
}
void loop() {
  uint16_t distance = sonar.ping_cm();
  if (distance >= 200) distance = 200;
  dataField.u16 = distance;
  
}

void requestEvent() {
  Wire.write(dataField.u8[0]);
  Wire.write(dataField.u8[1]);
}

#include <NewPing.h>

#define MODULE_TYPE   21

#define TRIGGER_PIN         (5)
#define ECHO_PIN            (6)
#define MAX_DIST            (200)


union DATA { 
  uint8_t u8[2];
  uint16_t u16;
} dataField;


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DIST);

void setup() {
  pinMode(11, OUTPUT);
}
void loop() {
  uint16_t distance = sonar.ping_cm();
  if (distance >= 200) distance = 200;
  dataField.u16 = distance;

  uint8_t pwm_val = map(int(distance), 0, 200, 0, 255);
  
  analogWrite(11, pwm_val);
}

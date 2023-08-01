#include <Wire.h>

#define I2C_SLAVE_ADDRESS (0x0A)  

#define QTR_L   (1)
#define QTR_M   (3)
#define QTR_R   (4)


uint8_t data = 0;

void setup()
{
  pinMode(QTR_L, INPUT);
  pinMode(QTR_M, INPUT);
  pinMode(QTR_R, INPUT);

  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onRequest(requestEvent);
}


void loop()
{
  data = ((digitalRead(QTR_L)) << 0) | ((digitalRead(QTR_M)) << 1) | ((digitalRead(QTR_R)) << 2);
}


void requestEvent() {
  Wire.write(data);
}


//bu zaten tek byte da yollanmis. Buna ne yapilacakti

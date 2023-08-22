#include <Wire.h>

#define ID_OFFSET   26
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
  if(i == -1) i2cSlaveAdress = 0;

  i2cSlaveAdress = i + ID_OFFSET;
}
#define QTR_L   (1)
#define QTR_M   (3)
#define QTR_R   (4)


uint8_t data = 0;

void setup()
{
  pinMode(QTR_L, INPUT);
  pinMode(QTR_M, INPUT);
  pinMode(QTR_R, INPUT);

  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
  }
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

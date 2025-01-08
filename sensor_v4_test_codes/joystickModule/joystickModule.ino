
#define MODULE_TYPE   16

#define Sensor_ArrySize 8  //** Sensor_ArrySize must be the power of the 2
unsigned int Sensor1Arry[Sensor_ArrySize],Sensor1Sum,Sensor1AVG,Sensor1NewData;
unsigned char Sensor1Indis;
unsigned int Sensor2Arry[Sensor_ArrySize],Sensor2Sum,Sensor2AVG,Sensor2NewData;
unsigned char Sensor2Indis;


#define JOYSTICK_X        (A0)
#define JOYSTICK_Y        (A1)
#define JOYSTICK_BUTTON   (10)

uint8_t button = 0;
typedef union parser {
  uint8_t   u8[4]; //int w 4 bytes
  int32_t     value;
} parser;

parser x;
parser y;

uint8_t joystick_index;


void setup()
{
  pinMode(JOYSTICK_X, INPUT);
  pinMode(JOYSTICK_Y, INPUT);
  pinMode(JOYSTICK_BUTTON, INPUT_PULLUP);
  
  // for testing
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
}


void loop()
{  
  Sensor1NewData = analogRead(JOYSTICK_X);
  Sensor2NewData = analogRead(JOYSTICK_Y);

  // filtering // moving avarage //
  Sensor1Sum = Sensor1Sum + Sensor1NewData - Sensor1Arry[Sensor1Indis];
  Sensor1AVG = Sensor1Sum / Sensor_ArrySize;
  Sensor1Arry[Sensor1Indis] = Sensor1NewData;
  Sensor1Indis ++;
  Sensor1Indis &= (Sensor_ArrySize - 1);  

  Sensor2Sum = Sensor2Sum + Sensor2NewData - Sensor2Arry[Sensor2Indis];
  Sensor2AVG = Sensor2Sum / Sensor_ArrySize;
  Sensor2Arry[Sensor2Indis] = Sensor2NewData;
  Sensor2Indis ++;
  Sensor2Indis &= (Sensor_ArrySize - 1);



  uint8_t pwmVAL_x = map(Sensor1AVG, 0, 1023, 0, 255);
  uint8_t pwmVAL_y = map(Sensor1AVG, 0, 1023, 0, 255);
  
  x.value = map(Sensor1AVG, 0, 1023, -100, 100);    //mapping 0-1023 to -100 100
  y.value = map(Sensor2AVG, 0, 1023, 100, -100);
  int button_count = 0;
  for (int i = 0; i < 3; i++) {
    if (digitalRead(JOYSTICK_BUTTON) == HIGH) {
      button_count++;
    }
  }
  if (button_count >=2) {
      button = 0x01;
  }
  else{
    button = 0x00;
  }

  digitalWrite(12, button);
  
  if(++joystick_index < 200){
    analogWrite(11, pwmVAL_x);
  }
  else if(joystick_index >= 200){
    analogWrite(11, pwmVAL_x);
  }
  if(joystick_index > 400) joystick_index = 0;
}

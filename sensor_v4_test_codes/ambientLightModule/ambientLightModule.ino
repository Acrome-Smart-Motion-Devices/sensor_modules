#define MODULE_TYPE     6

#define Sensor_ArrySize 16  //** Sensor_ArrySize must be the power of the 2
unsigned int Sensor1Arry[Sensor_ArrySize],Sensor1Sum,Sensor1AVG,Sensor1NewData;
unsigned char Sensor1Indis;


#define AMBIENT_LIGHT_PIN   (A0)
#define BUZZER_PIN          (10)

union dataParser {
  uint8_t   u8[2];
  uint16_t  lux;
} parser;

void setup() {

  pinMode(BUZZER_PIN, OUTPUT);

  // for testing
  pinMode(11, OUTPUT);

}

void loop() {
  //    A * 36*10^5 = LUX
  //    V / R = A
  //    Analog / 1024 * 5 = V
  // 7.4K ohm
  
  //parser.lux = analogRead(AMBIENT_LIGHT_PIN)* 5 / 1024 * 540,54;
  //parser.lux = analogRead(AMBIENT_LIGHT_PIN);
  Sensor1NewData = analogRead(AMBIENT_LIGHT_PIN);

  // filtering // moving avarage //
  Sensor1Sum = Sensor1Sum + Sensor1NewData - Sensor1Arry[Sensor1Indis];
  Sensor1AVG = Sensor1Sum / Sensor_ArrySize;
  Sensor1Arry[Sensor1Indis] = Sensor1NewData;
  Sensor1Indis ++;
  Sensor1Indis &= (Sensor_ArrySize - 1);
  
  
  parser.lux =(uint16_t)(Sensor1AVG * 2.34375);


  tone(BUZZER_PIN, parser.lux);
  //delay(500);

  uint8_t pwm = map(int(parser.lux), 0, 3000, 0, 255);
  //analogWrite(11,pwm);
}


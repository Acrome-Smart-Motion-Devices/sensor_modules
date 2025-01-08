

#define MODULE_TYPE   36

#define Sensor_ArrySize 16  //** Sensor_ArrySize must be the power of the 2
unsigned int Sensor1Arry[Sensor_ArrySize],Sensor1Sum,Sensor1AVG,Sensor1NewData;
unsigned char Sensor1Indis;


#define POTANTIOMETER_PIN   (A0)
uint8_t potantiometer = 0;

void setup() {
  pinMode(11, OUTPUT);
}
void loop() {
  Sensor1NewData = analogRead(POTANTIOMETER_PIN);

  // filtering // moving avarage //
  Sensor1Sum = Sensor1Sum + Sensor1NewData - Sensor1Arry[Sensor1Indis];
  Sensor1AVG = Sensor1Sum / Sensor_ArrySize;
  Sensor1Arry[Sensor1Indis] = Sensor1NewData;
  Sensor1Indis ++;
  Sensor1Indis &= (Sensor_ArrySize - 1);
  
  potantiometer = map(Sensor1AVG,0,1024,0,255);

  analogWrite(11, potantiometer);
}


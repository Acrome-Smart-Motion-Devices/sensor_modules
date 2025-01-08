

#define MODULE_TYPE   26


#define Sensor_ArrySize 16  //** Sensor_ArrySize must be the power of the 2
unsigned int Sensor1Arry[Sensor_ArrySize],Sensor1Sum,Sensor1AVG,Sensor1NewData;
unsigned char Sensor1Indis;
unsigned int  Sensor2Arry[Sensor_ArrySize],Sensor2Sum,Sensor2AVG,Sensor2NewData;
unsigned char Sensor2Indis;
unsigned int  Sensor3Arry[Sensor_ArrySize],Sensor3Sum,Sensor3AVG,Sensor3NewData;
unsigned char Sensor3Indis;
unsigned int  Sensor4Arry[Sensor_ArrySize],Sensor4Sum,Sensor4AVG,Sensor4NewData;
unsigned char Sensor4Indis;
unsigned int  Sensor5Arry[Sensor_ArrySize],Sensor5Sum,Sensor5AVG,Sensor5NewData;
unsigned char Sensor5Indis;

uint8_t sensor1_filtered;
uint8_t sensor2_filtered;
uint8_t sensor3_filtered;
uint8_t sensor4_filtered;
uint8_t sensor5_filtered;

uint16_t qtr_count = 0;

#define QTR_0   (A6)
#define QTR_1   (A7)
#define QTR_2   (A0)
#define QTR_3   (A1)
#define QTR_4   (A3)

uint8_t data = 0;

void setup()
{
  pinMode(11, OUTPUT);
}


void loop()
{
  Sensor1NewData = analogRead(QTR_0);
  Sensor2NewData = analogRead(QTR_1);
  Sensor3NewData = analogRead(QTR_2);
  Sensor4NewData = analogRead(QTR_3);
  Sensor5NewData = analogRead(QTR_4);


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

  Sensor3Sum = Sensor3Sum + Sensor3NewData - Sensor3Arry[Sensor3Indis];
  Sensor3AVG = Sensor3Sum / Sensor_ArrySize;
  Sensor3Arry[Sensor3Indis] = Sensor3NewData;
  Sensor3Indis ++;
  Sensor3Indis &= (Sensor_ArrySize - 1);

  Sensor4Sum = Sensor4Sum + Sensor4NewData - Sensor4Arry[Sensor4Indis];
  Sensor4AVG = Sensor4Sum / Sensor_ArrySize;
  Sensor4Arry[Sensor4Indis] = Sensor4NewData;
  Sensor4Indis ++;
  Sensor4Indis &= (Sensor_ArrySize - 1);

  Sensor5Sum = Sensor5Sum + Sensor5NewData - Sensor5Arry[Sensor5Indis];
  Sensor5AVG = Sensor5Sum / Sensor_ArrySize;
  Sensor5Arry[Sensor5Indis] = Sensor5NewData;
  Sensor5Indis ++;
  Sensor5Indis &= (Sensor_ArrySize - 1);

  sensor1_filtered = map(Sensor1AVG,0,1024,0,255);
  sensor2_filtered = map(Sensor2AVG,0,1024,0,255);
  sensor3_filtered = map(Sensor3AVG,0,1024,0,255);
  sensor4_filtered = map(Sensor4AVG,0,1024,0,255);
  sensor5_filtered = map(Sensor5AVG,0,1024,0,255);

  qtr_count++;
  uint16_t index = qtr_count / 100;
  if (qtr_count >= 500) qtr_count = 0;

  

  switch (qtr_count){
    case 0:
      analogWrite(11, sensor1_filtered);
      break;
    case 2:
      analogWrite(11, sensor2_filtered);
      break;
    case 3:
      analogWrite(11, sensor3_filtered);
      break;
    case 4:
      analogWrite(11, sensor4_filtered);
      break;
    case 5:
      analogWrite(11, sensor5_filtered);
      break;
    default:
      break;
  }
}

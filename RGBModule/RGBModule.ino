#include <Wire.h>

#define ID_OFFSET       41
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
  if(i == -1) i = 0;

  i2cSlaveAdress = i + ID_OFFSET;
}

#define BUZZER_PIN          (1)

int LED_R_PIN = 9;
int LED_G_PIN = 6;
int LED_B_PIN = 5;

uint8_t receivedData = 0;

typedef struct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}RGBColor;

RGBColor color;

typedef enum{
    NOCOLOR = 0,
    RED,
    GREEN,
    BLUE,
    WHITE,
    YELLOW,
    CYAN,
    MAGENTA,
    ORANGE,
    PURPLE,
    PINK,
    AMBER,
    TEAL,
    INDIGO
}tColors;

RGBColor colors[] = {
    {0, 0, 0},         // No Color
    {255, 0, 0},       // Red (Kırmızı)
    {0, 255, 0},       // Green (Yeşil)
    {0, 0, 255},       // Blue (Mavi)
    {255, 255, 255},   // White (Beyaz)
    {255, 255, 0},     // Yellow (Sarı)
    {0, 255, 255},     // Cyan (Turkuaz/Mavi Yeşil)
    {255, 0, 255},     // Magenta (Pembe)
    {255, 165, 0},     // Orange (Turuncu)
    {128, 0, 128},     // Purple (Mor)
    {255, 192, 203},   // Pink (Pembe Tonları)     10
    {255, 191, 0},     // Amber (Kehribar Rengi)
    {0, 128, 128},     // Teal (Teal Rengi)
    {75, 0, 130}       // Indigo (Çivit Rengi)
};

RGBColor numberToRGBColor(uint8_t number);

void setup() {
  setupID();
  if(i2cSlaveAdress != 0){
    Wire.begin(i2cSlaveAdress);
    Wire.onReceive(receiveEvent);
  }
  
  pinMode(LED_R_PIN, OUTPUT);
  pinMode(LED_G_PIN, OUTPUT);
  pinMode(LED_B_PIN, OUTPUT);
}

void loop() {
    color = numberToRGBColor(receivedData);
    analogWrite(LED_R_PIN, color.red);
    analogWrite(LED_G_PIN, color.green);
    analogWrite(LED_B_PIN, color.blue);
}


void receiveEvent(int byteCount)
{ 
    if (byteCount > 0) {
    receivedData = Wire.read();
    }
}

RGBColor numberToRGBColor(uint8_t number) {
    if (number >= 0 && number <= 13) {
        return colors[number];
    } else {
        RGBColor invalidColor = {0, 0, 0}; // Error check
        return invalidColor;
    }
}

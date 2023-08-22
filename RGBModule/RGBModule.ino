#include <Wire.h>

#define I2C_SLAVE_ADDRESS   (0x07)
#define BUZZER_PIN          (1)

int LED_R_PIN = 0;
int LED_G_PIN = 0;
int LED_B_PIN = 0;

uint8_t receivedData;

typedef struct{
    int red;
    int green;
    int blue;
}RGBColor;
RGBColor color;

typedef enum{
    RED = 0,
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
    {255, 0, 0},       // Red (Kırmızı)
    {0, 255, 0},       // Green (Yeşil)
    {0, 0, 255},       // Blue (Mavi)
    {255, 255, 255},   // White (Beyaz)
    {255, 255, 0},     // Yellow (Sarı)
    {0, 255, 255},     // Cyan (Turkuaz/Mavi Yeşil)
    {255, 0, 255},     // Magenta (Pembe)
    {255, 165, 0},     // Orange (Turuncu)
    {128, 0, 128},     // Purple (Mor)
    {255, 192, 203},   // Pink (Pembe Tonları)
    {255, 191, 0},     // Amber (Kehribar Rengi)
    {0, 128, 128},     // Teal (Teal Rengi)
    {75, 0, 130}       // Indigo (Çivit Rengi)
};

void setup() {
  Wire.begin(I2C_SLAVE_ADDRESS);
  Wire.onRecevie(receiveEvent);
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
    if (number >= 0 && number <= 12) {
        return colors[number];
    } else {
        RGBColor invalidColor = {0, 0, 0}; // Error check
        return invalidColor;
    }
}
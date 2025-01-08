
#define MODULE_TYPE       41

#define LED0_R      (A3)
#define LED0_G      (A1)
#define LED0_B      (A0)
#define LED1_R      (6)
#define LED1_G      (9)
#define LED1_B      (5)
#define BUTTON_0    (1)
#define BUTTON_1    (10)




int LED_R_PIN = 9;
int LED_G_PIN = 6;
int LED_B_PIN = 5;


typedef struct{
    uint8_t red;
    uint8_t green;
    uint8_t blue;
}RGBColor;

RGBColor color[2];

uint8_t color_set[3] = {0, 0, 255};

void setup() {

  pinMode(LED0_R, OUTPUT);
  pinMode(LED0_G, OUTPUT);
  pinMode(LED0_B, OUTPUT);
  pinMode(LED1_R, OUTPUT);
  pinMode(LED1_G, OUTPUT);
  pinMode(LED1_B, OUTPUT);
  pinMode(BUTTON_0, INPUT);
  pinMode(BUTTON_1, INPUT);

}

void loop() {

  if(digitalRead(BUTTON_0)==HIGH){
    setColor(LED0_R, LED0_G, LED0_B, 0);
    delay(500);
  }

  if(digitalRead(BUTTON_1)==HIGH){
    setColor(LED1_R, LED1_G, LED1_B, 1);
    delay(500);
  }
}


void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t counter_index){
  static uint8_t counter[2] = {0,0};

  if(++counter[counter_index] >= 3) counter[counter_index] = 0;
  
  analogWrite(r, color_set[counter[counter_index]]);
  analogWrite(g, color_set[(counter[counter_index] + 1) % 3]);
  analogWrite(b, color_set[(counter[counter_index] + 2) % 3]); 
}

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN 6
#define BTN 2
#define MAX_STATE_CNT 6

Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pinMode(BTN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BTN), isr, RISING);

  Serial.begin(9600);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}
int state = 0;
int flag = 0;
unsigned long prev_millis = 0;

void isr()
{ /*
    if (state < MAX_STATE_CNT)
    {
     state++;
    }
    else if (state + 1 > MAX_STATE_CNT)
    {
     state = 0;
    }
    Serial.println(state);
    strip.show();

    if (state == 0)  colorWipe(strip.Color(255, 255, 255), 50); // White
    else if (state == 1) colorWipe(strip.Color(255, 255, 0), 50); // violet
    else if (state == 2) colorWipe(strip.Color(255, 0, 255), 50); // lemon
    else if (state == 3) colorWipe(strip.Color(0, 255, 0), 50); // Blue
    else if (state == 4) colorWipe(strip.Color(255, 0, 0), 50); // Red
    else if (state == 5) colorWipe(strip.Color(0, 255, 255), 50); // skyblue
    else if (state == 6) colorWipe(strip.Color(0, 0, 255), 50); // Green
  */
}

void loop() {
  unsigned long curr_millis = millis();
  Serial.println(digitalRead(BTN));
  if (curr_millis - prev_millis >= 50)
  {
    prev_millis = curr_millis;
    int BTN_value = digitalRead(BTN);

    if (flag == 0 && BTN_value == 1)
    {
      flag = 1;
    }
    else if (flag == 1 && BTN_value == 0)
    {
      flag = 0;

      if (state < MAX_STATE_CNT)
      {
        state++;
      }
      else if (state + 1 > MAX_STATE_CNT)
      {
        state = 0;
      }

      //Serial.println(state);
      strip.show();

      if (state == 0)  colorWipe(strip.Color(255, 255, 255), 50); // White
      else if (state == 1) colorWipe(strip.Color(255, 255, 0), 50); // violet
      else if (state == 2) colorWipe(strip.Color(255, 0, 255), 50); // lemon
      else if (state == 3) colorWipe(strip.Color(0, 255, 0), 50); // Blue
      else if (state == 4) colorWipe(strip.Color(255, 0, 0), 50); // Red
      else if (state == 5) colorWipe(strip.Color(0, 255, 255), 50); // skyblue
      else if (state == 6) colorWipe(strip.Color(0, 0, 255), 50); // Green
    }
  }
}






























// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for (uint16_t i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

void rainbow(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i + j) & 255));
    }
    strip.show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
  uint16_t i, j;

  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip.numPixels(); i++) {
      if (state == 4) {
        strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
      }
      strip.show();
      delay(wait);
    }
  }
}

//Theatre-style crawling lights.
void theaterChase(uint32_t c, uint8_t wait) {
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(uint8_t wait) {
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, Wheel( (i + j) % 255)); //turn every third pixel on
      }
      strip.show();

      delay(wait);

      for (uint16_t i = 0; i < strip.numPixels(); i = i + 3) {
        strip.setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

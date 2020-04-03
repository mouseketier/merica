#include <avr/pgmspace.h>  // Needed to store stuff in Flash using PROGMEM
#include <FastLED.h>       // Fastled library to control the LEDs
// How many leds are connected?
#define NUM_LEDS 375
// Define the Data Pin
#define DATA_PIN 2  // Connected to the data pin of the first LED strip
// Define the array of leds
CRGB leds[NUM_LEDS];
// Define Colors
#define Red       0xFF0000
#define White     0xFFFFFF
#define Blue      0x0000FF
#define Green     0x00FF00
#define Black     0x000000
#define Yellow    0xFFFF00
int Counter = 0; // added to use as the flag counter
uint32_t flag_USA[15][25] = {
  {  White, Blue, White, Blue, White, Blue, White, Blue, White, Blue, White, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, }, // row 1
  {  White, White, White, White, White, White, White, White, White, White, White, White, White, White, Blue, White, Blue, White, Blue, White, Blue, White, Blue, White, Blue, },  // row 2
  {  White, Blue, White, Blue, White, Blue, White, Blue, White, Blue, White, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, }, // row 3
  {  White, White, White, White, White, White, White, White, White, White, White, White, White, White, Blue, White, Blue, White, Blue, White, Blue, White, Blue, White, Blue,  },  // row 4
  {  White, Blue, White, Blue, White, Blue, White, Blue, White, Blue, White, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, }, // row 5
  {  White, White, White, White, White, White, White, White, White, White, White, White, White, White, Blue, White, Blue, White, Blue, White, Blue, White, Blue, White, Blue,  },  // row 6
  {  White, Blue, White, Blue, White, Blue, White, Blue, White, Blue, White, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, }, // row 7
  {  White, White, White, White, White, White, White, White, White, White, White, White, White, White, Blue, White, Blue, White, Blue, White, Blue, White, Blue, White, Blue,  },  // row 8
  {  White, Blue, White, Blue, White, Blue, White, Blue, White, Blue, White, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, }, // row 9
  {  White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, },  // row 10
  {  Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, }, // row 11
  {  White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, },  // row 12
  {  Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, }, // row 13
  {  White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, },  // row 14
  {  Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, } // row 15
};
uint32_t flag_PR [15][25] = {
  {  Blue, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, }, // row 1
  {  Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Blue, Blue, }, // row 2
  {  Blue, Blue, Blue, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, }, // row 3
  {  White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, Blue, Blue, Blue, Blue,  },  // row 4
  {  Blue, Blue, Blue, Blue, Blue, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White,  },  // row 5
  {  White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, Blue, Blue, Blue, Blue, Blue, Blue, }, // row 6
  {  Blue, Blue, Blue, White, Blue, Blue, Blue, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, }, // row 7
  {  Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Blue, Blue, Blue, White, White, White, Blue, Blue, }, // row 8
  {  Blue, Blue, Blue, White, Blue, Blue, Blue, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, },  // row 9
  {  White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, Blue, Blue, Blue, Blue, Blue, Blue,  },  // row 10
  {  Blue, Blue, Blue, Blue, Blue, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White,  }, // row 11
  {  White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, White, Blue, Blue, Blue, Blue, }, // row 12
  {  Blue, Blue, Blue, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, }, // row 13
  {  Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Blue, Blue, }, // row 14
  {  Blue, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, Red, } // row 15
};
uint32_t flag_MERICA [15][25] = {
  {  Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, }, // row 1
  {  Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, }, // row 2b
  {  Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Red, Black, Black, Red, Black, Black, Black, Black, Black, Black, Black, Black, Black, }, // row 3
  {  Black, Black, Black, Black, Black, Black, Black, Black, Red, Red, Red, Red, Red, Red, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black,  },  // row 4b
  {  Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Red, Black, Black, Red, Black, Black, Black, Black, Black, Black, Black, Black, Black,  },  // row 5
  {  Black, Black, Black, Black, Black, Black, Black, Black, Red, Red, Red, Red, Red, Red, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, }, // row 6b
  {  Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Red, Black, Black, Red, Black, Black, Black, Black, Black, Black, Black, Black, Black, }, // row 7
  {  Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, }, // row 8b
  {  Red, Black, Black, Black, Red, Black, White, White, White, Black, Blue, Blue, Blue, Black, Red, Red, Red, Black, White, White, White, Black, Black, Blue, Black, },  // row 9
  {  Blue, Black, Blue, Black, Black, Black, White, Black, Black, Red, Black, Black, Blue, Black, Blue, Black, Black, Black, White, Black, Red, Red, Black, Red, Red,  },  // row 10b
  {  Red, Black, Red, Black, Red, Black, White, White, Black, Black, Blue, Blue, Blue, Black, Black, Red, Black, Black, White, Black, Black, Black, Blue, Blue, Blue,  }, // row 11
  {  Blue, Black, Blue, Black, Black, Black, White, Black, Black, Red, Black, Black, Black, Blue, Blue, Black, Black, Black, White, Black, Red, Black, Black, Black, Red, }, // row 12b
  {  Red, Black, Black, Black, Red, Black, White, White, White, Black, Blue, Black, Blue, Black, Red, Red, Red, Black, White, White, White, Black, Blue, Black, Blue, }, // row 13
  {  Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, }, // row 14b
  {  Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, Black, } // row 15
};
void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS); // Init of the Fastled library
  FastLED.setBrightness(15);
}
void loop() {
  if (Counter > 2) {
    Counter = 1;  // reset counter
  }

  // Light Up
  for (int row = 0; row < 15; row++) {
    for (int col = 0; col < 25; col++) {
      setFlagColor(Counter); // call function to pick the correct flag
      delay(100);     // 0.1 second slow down
      FastLED.show(); // Light up one at a time
    }
  }
  delay(5000);   // 5 seconds
  // All LEDs OFF
  for (int i = NUM_LEDS - 1 ; i >= 0; i-- ) {
    byte leds = 0;
    FastLED.show();
    delay(1);
  }
  Counter++; // increase counter
}
void setFlagColor(int flagID) {
  switch (flagID) {
    case 0:
      leds[ (row * 15) + col ] = flag_USA[row][col];
      break;
    case 1:
      leds[ (row * 15) + col ] = flag_PR[row][col];
      break;
    case 2:
      leds[ (row * 15) + col ] = flag_MERICA[row][col];
      break;
  }
}

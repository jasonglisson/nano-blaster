#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>
#include <DFPlayerMini_Fast.h>

#define BUTTON_PIN 2
#define PIXEL_PIN 6  // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 16  // Number of NeoPixels

SoftwareSerial mySerial(10, 11); // RX, TX
DFPlayerMini_Fast myDFPlayer;

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

boolean oldState = HIGH;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  strip.begin(); // Initialize NeoPixel strip object (REQUIRED)
  strip.show();  // Initialize all pixels to 'off'
  Serial.begin(115200);
  mySerial.begin(9600);
 
  myDFPlayer.begin(mySerial);
}

void blaster() {
  myDFPlayer.volume(20); //set volume low
  myDFPlayer.play(1); //play mp3 file with leading identifier "0001"
  while(0); //halt
}

void loop() {
  // Get current button state.
  boolean newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if((newState == LOW) && (oldState == HIGH)) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if(newState == LOW) {      // Yes, still low
      colorWipe(strip.Color(255,   0,   0), 7);    // Red
      colorWipe(strip.Color(  0,   0,   0), 2);    // Black/off
      blaster();      
    }
  }

  // Set the last-read button state to the old state.
  oldState = newState;
}


void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}

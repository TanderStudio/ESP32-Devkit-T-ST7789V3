#include <Arduino.h>
#include "TFT_eSPI.h"

#define BL 4
#define IO2 2

TFT_eSPI tft = TFT_eSPI();  // Invoke custom library 

uint16_t colors[] = {
  TFT_CYAN, TFT_MAGENTA, TFT_YELLOW, TFT_BLACK, TFT_RED,
  TFT_GREEN, TFT_BLUE,TFT_WHITE,TFT_ORANGE,TFT_PINK   // colors
};
      
int BL_brightness = 100;  // set the brightness level 0 - 255

void setup() {
      
Serial.begin(115200);
Serial.println("SETUP");
      
pinMode(BL, OUTPUT);
pinMode(IO2, OUTPUT);
      

analogWrite(BL, BL_brightness);  // Set the TFT backlight Brightness
digitalWrite(IO2, HIGH);      // Set the LED on the GPIO2 as HIGH to turn on the LED
      

tft.init();  // initialize the library
tft.setSwapBytes(true);  

tft.fillScreen(TFT_ORANGE); //set the background

      }
      
void loop() {

tft.setRotation(1); // change the rotation for the TFT

int segmentWidth = 32;   
   
int numColors = sizeof(colors) / sizeof(colors[0]);  // Get the number of colors

     for (int i = 0; i < numColors; i++) {   // Loop through each color and display it in a vertical segment

    tft.fillRect(i * segmentWidth, 0, segmentWidth, 172, colors[i]);  // Draw the segment with the current color   

  }
 

delay(1000);
Serial.println("Hello World");
      
}
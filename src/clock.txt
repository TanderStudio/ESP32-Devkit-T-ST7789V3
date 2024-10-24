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

int hours = 8;
      
int minutes = 11;

int seconds = 3;

bool set=true;

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


  if (set==true){ //to set the background once
     for (int i = 0; i < numColors; i++) {   // Loop through each color and display it in a vertical segment

    tft.fillRect(i * segmentWidth, 0, segmentWidth, 172, colors[i]);  // Draw the segment with the current color

    tft.fillRoundRect(7,40,300,84,10,TFT_BLACK); // Draw the background for the clock
      
    }
    set=false;
  }
 
tft.setTextColor(TFT_WHITE, TFT_BLACK);
tft.setTextSize(6);

char timeString[9];
  sprintf(timeString, "%02d:%02d:%02d", hours, minutes, seconds);

  // Get the width and height of the text
  int textWidth = tft.textWidth(timeString);   // Get the pixel width of the text
  int textHeight = tft.fontHeight();           // Get the height of the current font

  // Print the width and height to the serial monitor
  Serial.printf("Text width: %d, Text height: %d\n", textWidth, textHeight);

  // set the clock cursor at the center of the screen
  tft.setCursor((320 - textWidth) / 2, (172 - textHeight) / 2);  // Center the text on the display

  tft.printf("%02d:%02d:%02d\n", hours, minutes, seconds); // print the clock on the TFT

// Clock Function  
seconds++;
if (seconds > 59) {
        seconds = 0;
        minutes++;
        if (minutes > 59) {
            minutes = 0;
            hours++;
            if (hours > 23) {
                hours = 0;
            }
        }
}

delay(1000);
Serial.println("Hello World");
      
}
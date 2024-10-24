# ESP32-Devkit-T-ST7789V3

![Devkit-T-ST7789V3 V1 Pinout](https://github.com/user-attachments/assets/cdf7b3b3-8784-41a8-bac1-a2678b3ee0ec)



## About
This ESP32 Devkit board comes with a built-in 1.47-inch IPS TFT display, featuring an ST7798V3 driver and a 172x328 pixel resolution. It also includes an LDO regulator with a working voltage range from 6V to 3.3V, making it ideal for compact and versatile projects. This board utilizes the `ESP32 module` from [ESPRESSIF](https://www.espressif.com).

This repository provides information for the Devkit and includes basic code setup and examples for the display.

***For more detail please refer to ESP32 and LCD TFT Display datasheet***
<details> 
<summary>Related Document Link</summary>

+ [ESP32 WROOM 32 Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf) PDF
+ [ESP32-DevkitC V4](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/hw-reference/esp32/get-started-devkitc.html)
+ [ESP32-Series Datasheet](https://www.espressif.com/sites/default/files/documentation/esp32_datasheet_en.pdf) PDF
+ [Espressif product](https://products.espressif.com/#/product-selector?names=)

</details>



## Datasheet
<details>
  <summary> Features, Board Size, Board Select, TFT</summary>

   ### Description

Features: 
  +	ESP32-WROOM-32D or ESP32-WROOM-32U Module
  +	USB Protection Diode
  + USB Type-C
  + Max +6V Input (from 5V pin)
  +	32 Pin
  +	1.47-inch IPS TFT display (172x328 pixel)
  +	UART CH340K
  +	3.3V Logic Level
  +	Built In LED (GPIO2)
  
  Board Size:
  +	Width: 25.4 mm x Length: 47.11 mm
  
  Compatible Board Select (for platform.io): 
  +	uPesy ESP32 Wroom DevKit
  +	Denky32 (WROOM32)
  
  LCD TFT Display Resolution:
  +	172x320 px
  +	19.45 mm x 37.00 mm

#### TFT 

Pinout for the display
| LCD TFT DISPLAY | GPIO |
| ----------- | -- |
| `MOSI`      | 23 |
| `SCK`       | 18 |
| `CS`        | 16 |
| `DC`        | 5  |
| `RST`       | 17 |
| `BackLight` | 4  |


</details>

# CODE

<details>
  
  <summary> Details </summary>

To start, this Devkit board utilizes the same ESP32 as other Devkits. Specifically, it employs either the `ESP32-WROOM-32D` or `ESP32-WROOM-32U` module from `ESPRESSIF`, which can be identified on the module itself. Additionally, this board is compatible with other libraries, as long as they do not interfere with pins already in use on the Devkit.

If you are using `platform.io`, select the `uPesy ESP32 Wroom DevKit` or `Denky32 (WROOM32)` as the target `board`.


  ## Built in LED
  <details>
  This code snippet is for controlling the LED on the Devkit, which is connected to `GPIO 2`. You can use this LED in the same way as any standard LED.

#### Simple LED PWM

  ```
#include <Arduino.h>

//define the pin for the LED
#define BuiltInLED 2
    
    
int brightness = 0; // how bright the LED is
int fadeAmount = 5; // how many points to fade the LED by
    
void setup() {
    
Serial.begin(9600);
    
pinMode(BuiltInLED, OUTPUT); // Set the LED pin as an output
    
Serial.println("Hello World");

}
    
void loop() {
    
  brightness = brightness + fadeAmount; // Change the brightness
    if (brightness <= 0 || brightness >= 255) {
      fadeAmount = -fadeAmount; // Reverse the fade direction
      }
        
  analogWrite(BuiltInLED, brightness); // Set the brightness
  delay(20); // Delay for smoother fading (adjust as needed)
    
    }
```

#### Advanced LED PWM
    
You can also use this type of [Advanced PWM](https://randomnerdtutorials.com/esp32-pwm-arduino-ide/) to control the LED
```
    // the number of the LED pin
    const int ledPin = 2;  // 2 corresponds to GPIO2
    
    // setting PWM properties
    const int freq = 5000;
    const int ledChannel = 0;
    const int resolution = 8;
     
    void setup(){
      // configure LED PWM functionalitites
      ledcSetup(ledChannel, freq, resolution);
      
      // attach the channel to the GPIO to be controlled
      ledcAttachPin(ledPin, ledChannel);
    }
     
    void loop(){
      // increase the LED brightness
      for(int dutyCycle = 0; dutyCycle <= 255; dutyCycle++){   
        // changing the LED brightness with PWM
        ledcWrite(ledChannel, dutyCycle);
        delay(15);
      }
    
      // decrease the LED brightness
      for(int dutyCycle = 255; dutyCycle >= 0; dutyCycle--){
        // changing the LED brightness with PWM
        ledcWrite(ledChannel, dutyCycle);   
        delay(15);
      }
    }
```

</details>

## TFT

<details>

To begin, you can choose any display library compatible with the ESP32 Devkit and TFT display. I recommend using either [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI?tab=readme-ov-file) by Bodmer or [LovyanGFX](https://github.com/lovyan03/LovyanGFX) by lovyan03.

to controll the `Backlight` i recommend to do it separately from the library

| LCD TFT DISPLAY | GPIO |
| ----------- | -- |
| `MOSI`      | 23 |
| `SCK`       | 28 |
| `CS`        | 16 |
| `DC`        | 5  |
| `RST`       | 17 |
| `BackLight` | 4  |

Using the TFT library you need to set up the pin first either in the user setup or on the main code.

  ### Bodmer TFT_eSPI

  
  If u using the Bodmer Library, then add the library first into your project, after that, set the user Setup.
  
  ### User_Setup

<details>
  
  To use the TFT display, you need to set the `User_Setup.h` first.

  To access it, on the `VS-Code` you can find it on the EXPLORER bar on the side of your screen. On your Project file, inside the .pio - libdeps - TFT_eSPI - User_Setup.h
  
![Screenshot 2024-09-17 001626](https://github.com/user-attachments/assets/6ef12419-e8ca-4e18-837c-49beca4b04df)

To implement the necessary configurations, insert the following code into the `User_Setup.h` .

you can choose the `USER_SETUP_ID` either `135` or `203` 

Next, set the pins according to your devkit configuration and define the TFT width and height (172 and 320) as shown in the example below.

```
// ST7789 135 x 240 display with no chip select line
#define USER_SETUP_ID 135
            
#define ST7789_DRIVER     // Configure all registers

#define TFT_WIDTH  172
#define TFT_HEIGHT 320
            
#define CGRAM_OFFSET      // Library will add offsets required
            
//#define TFT_RGB_ORDER TFT_RGB  // Colour order Red-Green-Blue
//#define TFT_RGB_ORDER TFT_BGR  // Colour order Blue-Green-Red
            
//#define TFT_INVERSION_ON
//#define TFT_INVERSION_OFF
            
            
// Generic ESP32 setup
//#define TFT_MISO 19
#define TFT_MOSI 23
#define TFT_SCLK 18
#define TFT_CS    5 // Not connected
#define TFT_DC    17
#define TFT_RST   16  // Connect reset to ensure display initialises
    

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
//#define LOAD_FONT8N // Font 8. Alternative to Font 8 above, slightly narrower, so 3 digits fit a 160 pixel TFT
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts
            
#define SMOOTH_FONT
            
            
// #define SPI_FREQUENCY  27000000
#define SPI_FREQUENCY  40000000
            
#define SPI_READ_FREQUENCY  20000000
            
#define SPI_TOUCH_FREQUENCY  2500000
            
// #define SUPPORT_TRANSACTIONS
```



</details>
    
  ### Example

<details>


<summary> Colour Test </summary>
   
  After completing the setup for the code, you can use the simple example below to test your board. For more functionality, you can refer to the examples inside the library or explore the Bodmer [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI?tab=readme-ov-file) library.

```
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
```



</details>

<details>

<summary> Simple Clock Display </summary>

Here i provide some simple code for displaying a clock, using the [TFT_eSPI](https://github.com/Bodmer/TFT_eSPI?tab=readme-ov-file) library

```
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
```
  
</details>
 </details> 





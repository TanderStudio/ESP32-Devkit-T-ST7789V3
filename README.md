# ESP32-Devkit-T-ST7789V3

![Devkit-T-ST7789V3 V1 Pinout White BG resize](https://github.com/user-attachments/assets/e2c77a3a-1b03-4acb-9fcd-7598d502f37b)


## About
Development board for ESP32 and LCD TFT Display. This kit offers a range of LCD TFT Display options, including ST7789, ST7789V, ST7789V3, GC9A01, and more, providing developers with flexibility to choose the display and all pin that best suits their project needs. Alongside this display versatility, the kit features four input pulldown buttons for user interactions and an additional input for voltage readings. This board utilizes the `ESP32 module` from [ESPRESSIF](https://www.espressif.com).

This repository provides the basic data for the Devkit and includes basic code setup and examples for each display.

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
  + Max +6V Input 
  +	32 Pin
  +	TFT LCD ST7789V3
  +	UART CH340K
  +	3.3V Logic Level
  +	Built In LED (GPIO2)
  
  Board Size:
  +	Width: 46.04 mm x Length: 51.26 mm (With Antenna: 57.51 mm)
  
  Compatible Board Select (for platform.io): 
  +	uPesy ESP32 Wroom DevKit
  +	Denky32 (WROOM32)
  
  LCD TFT Display Resolution:
  +	172x320 px

  ### BOARD DIMENSION

  ![Screenshot 2024-01-31 190518](https://github.com/TanderStudio/ESP32-Devkit-TFT/assets/157987904/d486ddf6-295e-46d6-9c67-f18a85f52e3e)
  

#### TFT 

Pinout for the display
| LCD TFT DISPLAY | GPIO |
| ----------- | -- |
| `MOSI`      | 23 |
| `SCK`       | 28 |
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

The `pin` configuration for the display for this board remains the same across various displays.

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
  <details>
  
  If u using the Bodmer Library, then add the library first into your project, after that, set the user Setup.
  
  ### User_Setup

<details>
  
  To use the TFT display, you need to set the `User_Setup.h` first.

  To access it, on the `VS-Code` you can find it on the EXPLORER bar on the side of your screen. On your Project file, inside the .pio - libdeps - TFT_eSPI - User_Setup.h
  
![Screenshot 2024-09-17 001626](https://github.com/user-attachments/assets/6ef12419-e8ca-4e18-837c-49beca4b04df)

To implement the necessary configurations, insert the following code into the `User_Setup.h` .

you can choose the `USER_SETUP_ID` either `135` or `203` 

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
  

 </details> 
</details>




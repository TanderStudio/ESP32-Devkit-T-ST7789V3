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
   </details>
Features: 
  +	ESP32-WROOM-32D or ESP32-WROOM-32U Module
  +	USB Protection Diode
  + USB Type-C
  + Max +6V Input 
  +	40 Pin
  +	LC TFT ST7789V3
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
  
</details>

#### TFT 
</details>
Each display have the same pin
| LCD TFT DISPLAY | GPIO |
| ----------- | -- |
| `MOSI`      | 23 |
| `SCK`       | 28 |
| `CS`        | 16 |
| `DC`        | 5  |
| `RST`       | 17 |
| `BackLight` | 4  |


</details>
</details>
# CODE
<details>
  <summary> Details </summary>

To start, this Devkit board utilizes the same ESP32 as other Devkits. Specifically, it employs either the `ESP32-WROOM-32D` or `ESP32-WROOM-32U` module drom `ESPRESSIF`, which can be identified on the module itself. Additionally, this board is compatible with other libraries, as long as they do not interfere with pins already in use on the Devkit.

If you are using `platform.io`, select the `uPesy ESP32 Wroom DevKit` or `Denky32 (WROOM32)` as the target `board`.
  
## Devkit
  ### Built in LED
  
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
You can also use this type of [Advanced PWM]([https://randomnerdtutorials.com/esp32-pwm-arduino-ide/](https://randomnerdtutorials.com/esp32-pwm-arduino-ide/)) to control the LED
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

Using the TFT library you need to set up the pin first either in the user setup or on the main code



</details>
  
</details>

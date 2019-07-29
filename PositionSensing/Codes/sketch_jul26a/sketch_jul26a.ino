// I2C device class (I2Cdev) demonstration Arduino sketch for ADS1115 class
// Example of reading two differential inputs of the ADS1115 and showing the value in mV
// 2016-03-22 by Eadf (https://github.com/eadf)
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//     2016-03-22 - initial release
//
//     2019-4-30
// JFM modified for re-initialising and output of multiple PGA resolutions for 
// comparison of readings. Also when debug is active serial receiving 's' 
// outputs register values. 



/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================


Wiring the ADS1115 Module to an Arduino UNO

ADS1115 -->  UNO
  VDD        5V
  GND        GND
  SCL        A5 (or SCL)
  SDA        A4 (or SDA)
  ALRT       2


*/

#include "ADS1115.h"

ADS1115 adc0(ADS1115_DEFAULT_ADDRESS);

// Wire ADS1115 ALERT/RDY pin to Arduino pin 2
const int alertReadyPin = 2;

void init_ads1115() {
  Serial.println("Testing device connections...");
    Serial.println(adc0.testConnection() ? "ADS1115 connection successful" : "ADS1115 connection failed");
    
    adc0.initialize(); // initialize ADS1115 16 bit A/D chip

    // We're going to do single shot sampling
    adc0.setMode(ADS1115_MODE_SINGLESHOT);
    
    // Slow things down so that we can see that the "poll for conversion" code works
    adc0.setRate(ADS1115_RATE_8);
      
    // Set the gain (PGA) +/- 6.144v
    // Note that any analog input must be higher than –0.3V and less than VDD +0.3
    adc0.setGain(ADS1115_PGA_6P144);
    // ALERT/RDY pin will indicate when conversion is ready
    
    pinMode(alertReadyPin,INPUT_PULLUP);
    adc0.setConversionReadyPinMode();

    // To get output from this method, you'll need to turn on the 
    //#define ADS1115_SERIAL_DEBUG // in the ADS1115.h file
    #ifdef ADS1115_SERIAL_DEBUG
    adc0.showConfigRegister();
    Serial.print("HighThreshold="); Serial.println(adc0.getHighThreshold(),BIN);
    Serial.print("LowThreshold="); Serial.println(adc0.getLowThreshold(),BIN);
    #endif
}

void setup() {    
    //I2Cdev::begin();  // join I2C bus
    Wire.begin();
    Serial.begin(115200); // initialize serial communication 
    
    init_ads1115();
}

/** Poll the assigned pin for conversion status 
 */
void pollAlertReadyPin() {
  for (uint32_t i = 0; i<100000; i++)
    if (!digitalRead(alertReadyPin)) return;
   Serial.println("Failed to wait for AlertReadyPin, it's stuck high!");
   // If gets stuck do -something = init.
   init_ads1115();
}

void loop() {

    adc0.setMultiplexer(ADS1115_MUX_P1_NG);
       
    adc0.setGain(ADS1115_PGA_6P144);        
    adc0.triggerConversion();
    pollAlertReadyPin();
    alertReadyPin="high";
    Serial.print("A1: "); Serial.print(adc0.getMilliVolts(false),3); Serial.print("mV\t");
    Serial.println(" PGA: 6144 mv acc: 187.5uV");
    
    adc0.setGain(ADS1115_PGA_4P096);
    adc0.triggerConversion();
    pollAlertReadyPin();
    Serial.print("A1: "); Serial.print(adc0.getMilliVolts(false),3); Serial.print("mV\t");
    Serial.println(" PGA: 4096 mv acc: 125uV");

    adc0.setGain(ADS1115_PGA_2P048);
    adc0.triggerConversion();
    pollAlertReadyPin();
    Serial.print("A1: "); Serial.print(adc0.getMilliVolts(false),3); Serial.print("mV\t");
    Serial.println(" PGA: 2048 mv acc: 62.5uV");

    adc0.setGain(ADS1115_PGA_1P024);
    adc0.triggerConversion();
    pollAlertReadyPin();
    Serial.print("A1: "); Serial.print(adc0.getMilliVolts(false),3); Serial.print("mV\t");
    Serial.println(" PGA: 1024 mv acc: 31.25uV");

    adc0.setGain(ADS1115_PGA_0P512);
    adc0.triggerConversion();
    pollAlertReadyPin();
    Serial.print("A1: "); Serial.print(adc0.getMilliVolts(false),3); Serial.print("mV\t");
    Serial.println(" PGA:  512 mv acc: 15.625uV");

    adc0.setGain(ADS1115_PGA_0P256);
    adc0.triggerConversion();
    pollAlertReadyPin();
    Serial.print("A1: "); Serial.print(adc0.getMilliVolts(false),3); Serial.print("mV\t");
    Serial.println(" PGA:  256 mv acc: 7.8125uV");

    Serial.print("Alert/RDY "); Serial.println(digitalRead(alertReadyPin));
    Serial.println();

    if (Serial.available()) {
        char chr = Serial.read();
        //Serial.print("Serial received"); Serial.print(chr);Serial.println("<<");
        switch (chr) {
           case 's' :  adc0.showConfigRegister(); break;
           //default: Serial.println(">>");Serial.print(chr);Serial.println("<<");
        }
    }
    
    delay(50);
}
  

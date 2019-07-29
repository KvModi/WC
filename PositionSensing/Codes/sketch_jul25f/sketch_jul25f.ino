#include <Wire.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads;
const int numReadings = 10;

int readings[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total = 0;                  // the running total
int average = 0;                // the average

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  Serial.println("Hello!");
  Wire.begin();
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");
  ads.begin();
}
void loop() {
  //  analogReadResolution(12);
  //Serial.println(analogRead(A0));
  total = total - readings[readIndex];
  // read from the sensor:
  readings[readIndex] = ads.readADC_SingleEnded(0);
  // add the reading to the total:
  total = total + readings[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;

  // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // calculate the average:
  average = total / numReadings;
  // send it to the computer as ASCII digits
  Serial.println(ads.readADC_SingleEnded(0)*100);
  //delay(1);
  delay(10);
}

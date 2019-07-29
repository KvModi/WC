#include "Arduino.h"
#include "Wire.h"
#define I2Caddress 0x48
const int numReadings = 50;
unsigned int readings[numReadings] = {0};
int readIndex = 0;
int total = 0;                  // the running total
int average = 0;                // the average

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  // Join the I2C bus as a master (call this only once)
  Wire.begin();
 for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
  Serial.println("Setup completed.");

}

void loop() {
  // put your main code here, to run repeatedly:

  // Step 1: Point to Config register - set to continuous conversion
  Wire.beginTransmission(I2Caddress);

  // Point to Config Register
  Wire.write(0b00000001);

  // Write the MSB + LSB of Config Register
  // MSB: Bits 15:8
  // Bit  15    0=No effect, 1=Begin Single Conversion (in power down mode)
  // Bits 14:12   How to configure A0 to A3 (comparator or single ended)
  // Bits 11:9  Programmable Gain 000=6.144v 001=4.096v 010=2.048v .... 111=0.256v
  // Bits 8     0=Continuous conversion mode, 1=Power down single shot
  Wire.write(0b01000010);

  // LSB: Bits 7:0
  // Bits 7:5 Data Rate (Samples per second) 000=8, 001=16, 010=32, 011=64,
  //      100=128, 101=250, 110=475, 111=860
  // Bit  4   Comparator Mode 0=Traditional, 1=Window
  // Bit  3   Comparator Polarity 0=low, 1=high
  // Bit  2   Latching 0=No, 1=Yes
  // Bits 1:0 Comparator # before Alert pin goes high
  //      00=1, 01=2, 10=4, 11=Disable this feature
  Wire.write(0b10000010);

  // Send the above bytes as an I2C WRITE to the module
  Wire.endTransmission();

  // ====================================

  // Step 2: Set the pointer to the conversion register
  Wire.beginTransmission(I2Caddress);

  //Point to Conversion register (read only , where we get our results from)
  Wire.write(0b00000000);

  // Send the above byte(s) as a WRITE
  Wire.endTransmission();

  // =======================================

  // Step 3: Request the 2 converted bytes (MSB plus LSB)
  Wire.requestFrom(I2Caddress, 2);

  // Read two bytes and convert to full 16-bit int
  uint16_t convertedValue;

  // Read the the first byte (MSB) and shift it 8 places to the left then read
  // the second byte (LSB) into the last byte of this integer
  convertedValue = (Wire.read() << 8 | Wire.read());
  readings[readIndex] = convertedValue;
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
   //average = average*(100.0/4095.0);
//Serial.print("6000");
 // Serial.print("500");
  Serial.println(average);
  delay(5); 
  

  
}

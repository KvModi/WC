#include <Wire.h>
#include <Adafruit_ADS1015.h>
/*
   Install the Adafruit_ADS1115 library. Download the zip file from net,
   go to sketch, include library, add .zip library
*/

/*
   Have to download teensy software too.
*/
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
int16_t val0[10], val1[10], val2[10], val3[10];
int16_t max0, max1, max2, max3;
int maxCounter = 0;
const int numReadings = 50;
int16_t readings1[numReadings], readings2[numReadings],readings3[numReadings], readings4[numReadings];
int16_t total1,total2,total3,total4  = 0;                  // the running total
int16_t average1, average2, average3, average4 = 0;                // the average
int readIndex = 0;              // the index of the current reading
void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hello!");
  Wire.begin();
  Serial.println("Getting single-ended readings from AIN0..3");
  Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
//   ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
//   ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
//   ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
    ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
    // initialize all the readings to 0:
for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings1[thisReading] = 0;
    readings2[thisReading] = 0;
    readings3[thisReading] = 0;
    readings4[thisReading] = 0;
  }
  ads.begin();
}

void loop(void)
{
  int16_t adc0, adc1, adc2, adc3;
  int selectiveAmplifier=10;
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  adc2 = ads.readADC_SingleEnded(2);
  adc3 = ads.readADC_SingleEnded(3);
  
// subtract the last reading:
total1 = total1 - readings1[readIndex];
  total2 = total2 - readings2[readIndex];
  total3 = total3 - readings3[readIndex];
  total4 = total4 - readings4[readIndex];
 
// read from the sensor:
  readings1[readIndex] = adc0;
  readings2[readIndex] = adc1;
  readings3[readIndex] = adc2;
  readings4[readIndex] = adc3;

   // add the reading to the total
  total1 = total1 + readings1[readIndex];
  total2 = total2 + readings2[readIndex];
  total3 = total3 + readings3[readIndex];
  total4 = total4 + readings4[readIndex];
  // advance to the next position in the array:
  readIndex = readIndex + 1;
   // if we're at the end of the array...
  if (readIndex >= numReadings) {
    // ...wrap around to the beginning:
    readIndex = 0;
  }

  // Saving past 10 values and then trying to amplify the difference
  // keeping the value at 0 the oldest and 9 the latest
  for (int i = 0; i < 9; i++) {
    val0[i] = val0[i + 1];
    val1[i] = val1[i + 1];
    val2[i] = val2[i + 1];
    val3[i] = val3[i + 1];

  }
  // saving the current value
  val0[9] = adc0;
  val1[9] = adc1;
  val2[9] = adc2;
  val3[9] = adc3;
  
  
  
//  int val=(abs(val0[9] - val0[0]) > 200) && (abs(val1[9] - val1[0]) > 200) && (abs(val2[9] - val2[0]) > 200) && (abs(val3[9] - val3[0]) > 200);
//  //Serial.println(val);
//  //Serial.print("\t");
//  if(val)
//  {
//    selectiveAmplifier=18;
//  //  adc0 = adc0 + adc0 * 20;
//  //   adc1 = adc1 + adc1 * 20;
//  //   adc2 = adc2 + adc2 * 20;
//  //    adc3 = adc3 + adc3 * 20;
//  }
//  else
//  {
//    selectiveAmplifier=10;
//  }
for (int i = 0; i < 10; i++)
  {
    max0 = max0 < val0[i] ? max0 : val0[i];
    max1 = max1 < val1[i] ? max1 : val1[i];
    max2 = max2 < val2[i] ? max2 : val2[i];
    max3 = max3 < val3[i] ? max3 : val3[i];

  }

  // calculate the average:
  average1 = total1 / numReadings;
  average2 = total2 / numReadings;
  average3 = total3 / numReadings;
  average4 = total4 / numReadings;
  // send it to the computer as ASCII digits
  //average = average*(100.0/4095.0);

  //// Average data
//  Serial.print(average1*100);
//  Serial.print("\t");
//  Serial.print(average2*100);
//  Serial.print("\t");
//  Serial.print(average3*100);
//  Serial.print("\t");
//  Serial.print(average4*100);

//  Actual data
  Serial.print(adc0);
  Serial.print("\t"); Serial.print(adc1);
  Serial.print("\t"); Serial.print(adc2);
  Serial.print("\t"); Serial.print(adc3);
// Serial.println(" ");

  //Least point out of 10 live data
  Serial.print("\t"); Serial.print(max0);
  Serial.print("\t"); Serial.print(max1);
  Serial.print("\t"); Serial.print(max2);
  Serial.print("\t"); Serial.print(max3);
  Serial.println(" ");
  delay(10);
  if (maxCounter == 10)
  {
    max0 = 32765; max1 = 32765; max2 = 32765; max3 = 32765;
    maxCounter = 0;
  }
  maxCounter = maxCounter + 1;
}

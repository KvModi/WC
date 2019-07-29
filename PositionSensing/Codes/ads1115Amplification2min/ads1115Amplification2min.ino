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
int16_t minval0[10], minval1[10], minval2[10], minval3[10];
int16_t max0, max1, max2, max3;
int16_t min0, min1, min2, min3;
int maxCounter = 0;
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
   ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
   // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV

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
  //Serial.print("AIN0: ");



  // Saving past 10 values and then trying to amplify the difference
  // keeping the value at 0 the oldest and 9 the latest
  for (int i = 0; i < 9; i++) {
    val0[i] = val0[i + 1];
    val1[i] = val1[i + 1];
    val2[i] = val2[i + 1];
    val3[i] = val3[i + 1];

  }
  for (int i = 0; i < 9; i++) {
    minval0[i] = minval0[i + 1];
    minval1[i] = minval1[i + 1];
    minval2[i] = minval2[i + 1];
    minval3[i] = minval3[i + 1];

  }
  
  // saving the current value
  val0[9] = adc0;
  val1[9] = adc1;
  val2[9] = adc2;
  val3[9] = adc3;
   // saving the current value
  minval0[9] = adc0;
  minval1[9] = adc1;
  minval2[9] = adc2;
  minval3[9] = adc3;
  //
  //  if (abs(val0[9] - val0[0]) > 200)
  //  {
  //    adc0 = adc0 + adc0 * 200;
  //  }
  //  if (abs(val1[9] - val1[0]) > 200)
  //  {
  //    adc1 = adc1 + adc1 * 200;
  //  }
  //  if (abs(val2[9] - val2[0]) > 200)
  //  {
  //    adc2 = adc2 + adc2 * 200;
  //  }
  //  if (abs(val3[9] - val3[0]) > 200)
  //  {
  //    adc3 = adc3 + adc3 * 200;
  //  }
  //
  //
  
  
  int val=(abs(val0[9] - val0[0]) > 200) && (abs(val1[9] - val1[0]) > 200) && (abs(val2[9] - val2[0]) > 200) && (abs(val3[9] - val3[0]) > 200);
  //Serial.println(val);
  //Serial.print("\t");
  if(val)
  {
    selectiveAmplifier=18;
  //  adc0 = adc0 + adc0 * 20;
  //   adc1 = adc1 + adc1 * 20;
  //   adc2 = adc2 + adc2 * 20;
  //    adc3 = adc3 + adc3 * 20;
  }
  else
  {
    selectiveAmplifier=10;
  }
for (int i = 0; i < 10; i++)
  {
    max0 = max0 > val0[i] ? max0 : val0[i];
    max1 = max1 > val1[i] ? max1 : val1[i];
    max2 = max2 > val2[i] ? max2 : val2[i];
    max3 = max3 > val3[i] ? max3 : val3[i];

  }

for (int i = 0; i < 10; i++)
  {
    min0 = min0 < minval0[i] ? min0 : minval0[i];
    min1 = min1 < minval1[i] ? min1 : minval1[i];
    min2 = min2 < minval2[i] ? min2 : minval2[i];
    min3 = min3 < minval3[i] ? min3 : minval3[i];

  }
  Serial.print(adc0);
  Serial.print("\t"); Serial.print(adc1);
  Serial.print("\t"); Serial.print(adc2);
  Serial.print("\t"); Serial.print(adc3);
 // Serial.println(" ");
  Serial.print("\t"); Serial.print(max0);
  Serial.print("\t"); Serial.print(max1);
  Serial.print("\t"); Serial.print(max2);
  Serial.print("\t"); Serial.print(max3);
  Serial.print("\t"); Serial.print(min0);
  Serial.print("\t"); Serial.print(min1);
  Serial.print("\t"); Serial.print(min2);
  Serial.print("\t"); Serial.print(min3);
  Serial.println(" ");
//  Serial.println(" ");
  
  delay(10);
  if (maxCounter == 20)
  {
    max0 = 0; max1 = 0; max2 = 0; max3 = 0;
    min0 = 70000; min1 = 70000; min2 = 70000; min3 = 70000;
    maxCounter = 0;
  }
  maxCounter = maxCounter + 1;
}

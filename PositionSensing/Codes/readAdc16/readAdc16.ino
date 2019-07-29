#include <Wire.h>
#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads(0x48);
float Voltage0,Voltage1,Voltage2,Voltage3 = 0.0;

void setup(void) 
{
  Serial.begin(9600);  
  ads.begin();
}

void loop(void) 
{
  int16_t adc0, adc1, adc2, adc3;  // we read from the ADC, we have a sixteen bit integer as a result

  adc0 = ads.readADC_SingleEnded(0);
  Voltage0 = (adc0 * 0.1875)/1000;

  adc1 = ads.readADC_SingleEnded(1);
  Voltage1 = (adc1 * 0.1875)/1000;

  adc2 = ads.readADC_SingleEnded(2);
  Voltage2 = (adc2 * 0.1875)/1000;

  adc3 = ads.readADC_SingleEnded(3);
  Voltage3 = (adc3 * 0.1875)/1000;
  
 // Serial.print("AIN0: "); 
 
 Serial.print(adc0);
  Serial.print("\t"); 
  //Serial.print(adc1);
  Serial.print("\t");
   //Serial.print(adc2);
  Serial.print("\t");
  //Serial.print(adc3);
  //Serial.print("\t");
  Serial.println();
  
  delay(10);
}

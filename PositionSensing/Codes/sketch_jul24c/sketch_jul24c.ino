#include <Wire.h>
#include <Adafruit_ADS1015.h>
Adafruit_ADS1115 ads; // * Use this for the 16-bit version * /

void setup (void)
{
  Serial.begin (9600);
  ads.setGain (GAIN_TWOTHIRDS);
  ads.begin ();
}

void loop (void)
{
  int16_t adc0, adc1, adc2, adc3;

  adc0 = ads.readADC_SingleEnded (0);
  adc1 = ads.readADC_SingleEnded (1);
  adc2 = ads.readADC_SingleEnded (2);
  adc3 = ads.readADC_SingleEnded (3);
  //adc0=1;
  Serial.print ("\t"); Serial.print (adc0);
  Serial.print ("\t"); Serial.print (adc1);
  Serial.print ("\t"); Serial.print (adc2);
  Serial.print ("\t"); Serial.print (adc3);
  Serial.println (" " );
  delay (10);
}

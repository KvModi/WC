        #include <Wire.h>
        #include <Adafruit_ADS1015.h>
        int16_t sensor1, sensor2, sensor3, sensor4;
        int16_t total1, total11 , total2, total22 , total3, total33, total4, total44 = 0;
        
        Adafruit_ADS1115 ads(0x48);
        float Voltage = 0.0;
        float Voltage2 = 0.0;
        float thold1, thold2, feedback = 0;
        int avg = 40;
        float Vref = 16384;
        float sensitivity = .87; //100mA per 500mV = 0.2
        // int sensorValue = 0;
        const int Signal = 8;
        const int threshold = 1000;
        int i = 0;  // variable to store the value coming from the sensor
        
        void setup(void)
        {
          Serial.begin(9600);
          ads.begin();
        }
        
        void loop(void)
        {
          //sensorValue = sensorValue / avgSamples;
        
          int16_t adc0, adc1, adc2, adc3; // we read from the ADC, we have a sixteen bit integer as a result
          sensor1 = ads.readADC_SingleEnded(0);
          sensor2 = ads.readADC_SingleEnded(1);
          sensor3 = ads.readADC_SingleEnded(2);
          sensor4 = ads.readADC_SingleEnded(3);
        
          total1 = total1 + sensor1;
          total2 = total2 + sensor2;
          total3 = total3 + sensor3;
          total4 = total4 + sensor4;
          i++;
          //avg=20, i=0 initially
          // doing calculations on average data ( after taking 20 values)
          if (i == (avg-1)) {
            //feedback = feedback / avg;
        
            // taking average volatge from each sensor
            total1 = total1 / avg;
            total2 = total2 / avg;
            total3 = total3 / avg;
            total4 = total4 / avg;
        
            // Scaling up
            total11 = (total1 * total1 * 10);
            total22 = (total2 * total2 * 10);
            total33 = (total3 * total3 * 10);
            total44 = (total4 * total4 * 10);
            Serial.print(int(total11));
            Serial.print("\t");
            Serial.print(int(total22));
            Serial.print("\t");
            Serial.print(int(total33));
            Serial.print("\t");
            Serial.print(int(total44));
            Serial.print("\t");
            Serial.println();
        
            total1, total2, total3, total4, i = 0;
            //feedback = 0;
          }
        
        
          //delay(10);
        }

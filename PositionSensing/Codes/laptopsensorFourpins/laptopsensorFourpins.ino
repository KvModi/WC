  float sensor1;
  float sensor2;
  float sensor3;
  float sensor4;// select the input pin for the potentiometer
  int ledPin = 13;      // select the pin for the LED// Pin 13: Arduino has an LED connected on pin 13// Pin 11: Teensy 2.0 has the LED on pin 11// Pin  6: Teensy++ 2.0 has the LED on pin 6// Pin 13: Teensy 3.0 has the LED on pin 13
  double total1, total11 = 0.0;
  double total2, total22 = 0;
  double total3, total33 = 0;
  double total4, total44 = 0;
  int i = 0;  // variable to store the value coming from the sensor
  float thold1, thold2, feedback = 0;
  int avg = 20;
  
  
  const int analogInPin = A7;
  const int Signal = 8;
  const int threshold = 1000;
  
  // Number of samples to average the reading over. //Change this to make the reading smoother... but beware of buffer overflows!
  const int avgSamples = 10;
  
  int sensorValue = 0;
  
  float sensitivity = .87; //100mA per 500mV = 0.2
  float Vref = 1950; // Output voltage with no current: ~ 2500mV or 2.5V
  
  
  void setup() {
    // declare the ledPin as an OUTPUT:
    Serial.begin(9600);
    pinMode(ledPin, OUTPUT);
    pinMode(Signal, OUTPUT);
  
  }
  
  void loop() {
  
  
    sensorValue = sensorValue / avgSamples;
  
    // The on-board ADC is 10-bits -> 2^10 = 1024 -> 5V / 1024 ~= 4.88mV // The voltage is in millivolts
   // float voltage = 4.88 * sensorValue;
  
    // This will calculate the actual current (in mA)
    // Using the Vref and sensitivity settings you configure
    // Reading the inouts from arduino board.
    sensor1 = analogRead(A1);
    sensor2 = analogRead(A2);
    sensor3 = analogRead(A3);
    sensor4 = analogRead(A4);
    sensorValue = analogRead(analogInPin);
  
    // converting the positional value from (0, 1023) to (0,5)V
    sensor1 = (sensor1 * 5) / 1024;
    sensor2 = (sensor2 * 5) / 1024;
    sensor3 = (sensor3 * 5) / 1024;
    sensor4 = (sensor4 * 5) / 1024;
  
    feedback = sensorValue + feedback;
  
    total1 = total1 + sensor1;
    total2 = total2 + sensor2;
    total3 = total3 + sensor3;
    total4 = total4 + sensor4;

    //avg=20, i=0 initially
    // doing calculations on average data ( after taking 20 values)
    if (i == avg) {
      feedback = feedback / avg;

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

      // The on-board ADC is 10-bits -> 2^10 = 1024 -> 5V / 1024 ~= 4.88mV // The voltage is in millivolts
      feedback = 4.88 * feedback;
      
      float current = (feedback - Vref) * sensitivity;
      Serial.print(int(total11));
      Serial.print("  ");
      Serial.print(int(total22));
      Serial.print("  ");
      Serial.print(int(total33));
      Serial.print("  ");
      Serial.print(int(total44));
      Serial.print("  ");
     
      if (current >= threshold) {
        Serial.print("yes");
        Serial.print("  ");
        Serial.println(current);
        digitalWrite(ledPin, HIGH);
      } else {
        Serial.print("no");
        Serial.print("  ");
        Serial.println(current);
        
        digitalWrite(ledPin, LOW);
      }
      Serial.print("  ");
      Serial.println(threshold);
      
      total1, total2, total3, total4, i = 0;
      feedback = 0;
    }
    i++;
  
    delay (1);
  
  }

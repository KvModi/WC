/*
  Smoothing

  Reads repeatedly from an analog input, calculating a running average and
  printing it to the computer. Keeps ten readings in an array and continually
  averages them.

  The circuit:
  - analog sensor (potentiometer will do) attached to analog input 0

  created 22 Apr 2007
  by David A. Mellis  <dam@mellis.org>
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Smoothing
*/

// Define the number of samples to keep track of. The higher the number, the
// more the readings will be smoothed, but the slower the output will respond to
// the input. Using a constant rather than a normal variable lets us use this
// value to determine the size of the readings array.
const int numReadings = 50;

int readings1[numReadings];      // the readings from the analog input
int readIndex = 0;              // the index of the current reading
int total1 = 0;                  // the running total
int average1 = 0;                // the average

int readings2[numReadings];
int total2 = 0;                  // the running total
int average2 = 0;

int readings3[numReadings];
int total3 = 0;                  // the running total
int average3 = 0;  

int readings4[numReadings];
int total4 = 0;                  // the running total
int average4 = 0;

void setup() {
  // initialize serial communication with computer:
  Serial.begin(9600);
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings1[thisReading] = 0;
    readings2[thisReading] = 0;
    readings3[thisReading] = 0;
    readings4[thisReading] = 0;
  }
}

void loop() {
  analogReadResolution(12);
  // subtract the last reading:
  total1 = total1 - readings1[readIndex];
  total2 = total2 - readings2[readIndex];
  total3 = total3 - readings3[readIndex];
  total4 = total4 - readings4[readIndex];
 
  // read from the sensor:
  readings1[readIndex] = analogRead(A0);
  readings2[readIndex] = analogRead(A1);
  readings3[readIndex] = analogRead(A2);
  readings4[readIndex] = analogRead(A3);
  
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

  // calculate the average:
  average1 = total1 / numReadings;
  average2 = total2 / numReadings;
  average3 = total3 / numReadings;
  average4 = total4 / numReadings;
  // send it to the computer as ASCII digits
  //average = average*(100.0/4095.0);
  //Serial.print("6000");
  // Serial.print("500");
  Serial.print(average1*100);
  Serial.print("\t");
  Serial.print(average2*100);
  Serial.print("\t");
  Serial.print(average3*100);
  Serial.print("\t");
  Serial.println(average4*100);

  // delay in between reads for stability
  // {@Plot.MyPlotWindow.Sensor.Green average}
  //Serial.println(sensorValue);  // To send all three 'data' points to the plotter
  delay(10);
}

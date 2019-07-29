

void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(19200);
}

// the loop routine runs over and over again forever:
void loop() {
  delay(1);
  // read the input on analog pin 0:
  int sensorValue1 = analogRead(A1);
   int sensorValue2 = analogRead(A2);
   

  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  float voltage1 = sensorValue1 * (10.0 / 1023.0);
  // print out the value you read:
  
  float voltage2 = sensorValue2 * (10.0 / 1023.0);

  Serial.print(voltage1);
  Serial.print("  ");
  Serial.println(voltage2);
  // print out the value you read:
  }

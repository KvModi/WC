void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
 Serial.print(analogRead(A1));
 Serial.print("\t");
 
 Serial.println(analogRead(A0));
 
 delay(100);
}

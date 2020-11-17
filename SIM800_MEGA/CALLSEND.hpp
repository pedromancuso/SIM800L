void setup(){
  Serial.begin(115200);//Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial3.begin(115200);//Begin serial communication with Arduino and SIM800L
  Serial.println("Initializing..."); 
  delay(1000);
  Serial3.println("AT"); //Once the handshake test is successful, i t will back to OK
  updateSerial();
  Serial3.println("ATD+ +5492615131175;"); //  change ZZ with country code and xxxxxxxxxxx with phone number to dial
  updateSerial();
  delay(20000); // wait for 20 seconds...
  Serial3.println("ATH"); //hang up
  updateSerial();
}
void loop(){}
void updateSerial(){
  delay(500);
  while (Serial.available()) {Serial3.write(Serial.read());}//Forward what Serial received to Software Serial Port
  while(Serial3.available()) {Serial.write(Serial3.read());}//Forward what Software Serial received to Serial Port
}

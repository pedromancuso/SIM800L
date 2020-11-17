void setup()
{
  Serial.begin(115200);//Begin serial communication with Arduino and Arduino IDE (Serial Monitor) 
  Serial3.begin(115200);//Begin serial communication with Arduino and SIM800L
  Serial.println("Initializing..."); 
  delay(1000);
  Serial3.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  Serial3.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  Serial3.println("AT+CNMI=1,2,0,0,0"); // Decides how newly arrived SMS messages should be handled
  updateSerial();
}

void loop(){updateSerial();}
void updateSerial(){
  delay(500);
  while (Serial.available()) {Serial3.write(Serial.read());}//Forward what Serial received to Software Serial Port
  while(Serial3.available()) {Serial.write(Serial3.read());}//Forward what Software Serial received to Serial Port
}

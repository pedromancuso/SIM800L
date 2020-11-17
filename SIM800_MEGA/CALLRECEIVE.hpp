void setup(){
  Serial.begin(115200);//Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial3.begin(115200);//Begin serial communication with Arduino and SIM800L
  Serial.println("Initializing..."); 
}
void loop(){updateSerial();}
void updateSerial(){
  delay(500);
  while (Serial.available()) {Serial3.write(Serial.read());}//Forward what Serial received to Software Serial Port  
  while(Serial3.available()){Serial.write(Serial3.read());}//Forward what Software Serial received to Serial Port
}

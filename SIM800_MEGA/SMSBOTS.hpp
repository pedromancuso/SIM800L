String strtemp;String strtempPrev;String mensaje;String intervalo;String credito;
void setup(){  
  Serial.begin(115200);//Begin serial communication with Arduino and Arduino IDE (Serial Monitor)
  Serial3.begin(115200);//Begin serial communication with Arduino and SIM800L
  Serial.println("");Serial.print("smsAlerta");
  delay(1000);
  Serial3.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();
  Serial3.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  Serial3.println("AT+CMGS=\"+5492615131175\"");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  int dif = strtemp.toInt() - strtempPrev.toInt();
  mensaje = "La temperatura actual es de " + String(strtemp) + "°C. A variado " + String(dif) + "°C en los ultimos " + String(intervalo) + " minutos"
            + "el credito disponible en tu cuenta es " + String(credito);
  Serial3.print(mensaje); //text content
  updateSerial();
  Serial3.write(26);
}
void loop(){}
void updateSerial(){
  delay(500);
  while (Serial.available()){Serial3.write(Serial.read());}//Forward what Serial received to Software Serial Port
  while(Serial3.available()){Serial.write(Serial3.read());}//Forward what Software Serial received to Serial Port  
}

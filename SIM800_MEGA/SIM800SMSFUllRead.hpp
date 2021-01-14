char RcvdMsg[200] = "";
int RcvdCheck = 0;
int RcvdConf = 0;
int index = 0;
int RcvdEnd = 0;
char MsgMob[15];
char MsgTxt[50];
int MsgLength = 0;

void Config() // This function is configuring our SIM900 module i.e. sending the initial AT commands
{
delay(1000);
Serial.print("ATE0\r");
Response();
Serial.print("AT\r");
Response();
Serial.print("AT+CMGF=1\r");
Response();
Serial.print("AT+CNMI=1,2,0,0,0\r");
Response();
}


void setup()
{
  Serial.begin(9600);
  Config();
}

void loop()
{
  RecSMS();
}


void Response() // Get the Response of each AT Command
{
int count = 0;
Serial.println();
while(1)
{
if(Serial.available())
{
char data =Serial.read();
if(data == 'K'){Serial.println("OK");break;}
if(data == 'R'){Serial.println("GSM Not Working");break;}
}
count++;
delay(10);
if(count == 1000){Serial.println("GSM not Found");break;}

}
}

void RecSMS() // Receiving the SMS and extracting the Sender Mobile number & Message Text
{
if(Serial.available())
{
char data = Serial.read();
if(data == '+'){RcvdCheck = 1;}
if((data == 'C') && (RcvdCheck == 1)){RcvdCheck = 2;}
if((data == 'M') && (RcvdCheck == 2)){RcvdCheck = 3;}
if((data == 'T') && (RcvdCheck == 3)){RcvdCheck = 4;}
if(RcvdCheck == 4){RcvdConf = 1; RcvdCheck = 0;}

if(RcvdConf == 1)
{
if(data == '\n'){RcvdEnd++;}
if(RcvdEnd == 3){RcvdEnd = 0;}
RcvdMsg[index] = data;

index++;
if(RcvdEnd == 2){RcvdConf = 0;MsgLength = index-2;index = 0;}
if(RcvdConf == 0)
{
Serial.print("Mobile Number is: ");
for(int x = 4;x < 17;x++)
{
  MsgMob[x-4] = RcvdMsg[x];
  Serial.print(MsgMob[x-4]);
}
  Serial.println();
  Serial.print("Message Text: ");
for(int x = 46; x < MsgLength; x++)
{
  MsgTxt[x-46] = RcvdMsg[x];
  Serial.print(MsgTxt[x-46]);
}

Serial.println();
Serial.flush();


}
}
}
}
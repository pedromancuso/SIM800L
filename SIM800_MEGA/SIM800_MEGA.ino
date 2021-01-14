/*SIMREADER*/char newsms[500];String smstxt="";int smscheck=0;int smsindex=0;int smsnl=0;int smslen=0;int smstxtstart=0;int simconf=0;String sms="";

void setup() {Serial.begin(115200);Serial.println("");Serial.println("SIM800L EVB");Serial3.begin(115200);}
void loop() {delay(300);RecSMS();}
void RecSMS(){
  if(Serial3.available()){
    char data = Serial3.read(); 
    if(data=='+'){smsindex=0;}
    smslen=smsindex;
    newsms[smsindex]=data;
    newsms[smsindex+1]=' ';    
    Serial.print(newsms[smsindex]);
    if((newsms[0]=='+')&&(smscheck==0)){smscheck=1;}
    if((newsms[1]=='C')&&(smscheck==1)){smscheck=2;}
    if((newsms[2]=='M')&&(smscheck==2)){smscheck=3;}
    if((newsms[3]=='T')&&(smscheck==3)){smscheck=4;}
    if((newsms[4]==':')&&(smscheck==4)){smscheck=5;}
    if(smscheck==5){if(newsms[smsindex]=='\n'){smsnl++;smstxtstart=smsindex+1;}}
    smsindex++;
  }else{
    if(smsnl>0){
      Serial.println("");Serial.print("smstxtstart: "+String(smstxtstart)+" / smslen: "+String(smslen));
      Serial.println("");Serial.print("Message Body: ");
      for(int x = smstxtstart; x <= smslen; x++){sms=sms+String(newsms[x]);}
      Serial.print(sms);
      smscheck=0;smsindex=0;smsnl=0;smstxtstart=0;smslen=0;sms="";
      Serial.flush();
    }else{      
      if(simconf==2){Serial3.println("AT+CNMI=1,2,0,0,0");simconf++;}
      if(simconf==1){Serial3.println("AT+CMGF=1");simconf++;}
      if(simconf==0){Serial3.println("AT");simconf++;}
    }
  }
}

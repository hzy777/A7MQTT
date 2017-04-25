#include <SoftwareSerial.h>
#include <stdlib.h>
#include <string.h>
char atCommand[50];
unsigned char mqttMessage[127];
int mqttMessageLength = 0;
int baseIndex;
long lastMsg = 0;//存放时间的变量 

unsigned char subback[127];

SoftwareSerial AT(3, 2);//实际只用2号脚发送AT指令,由硬串口RX接收数据






void setup() {
pinMode(4,OUTPUT);
digitalWrite(4,HIGH);
delay(2000);
digitalWrite(4,LOW);
  Serial.begin(115200);
  AT.begin(115200);
  Serial.println(111); 
  ciphmode();
  in("aaaaaasss","","");
  sendMQTTMessage("888","helloword");
  delay(10);
  SUB("hzy");
}

void loop() {


int j= BackBit(200);
for(int i=0;i<j;i++){
  Serial.print(subback[i]);
  }
 Serial.println();
  
pub_topic_delay("888","HelloWorld!",15000);

}



int BackBit(int t){//接收AT指令反馈

  int i=0;
  for(i=0;i<127;i++){
    subback[i]=0;
  }
   i=0;
  long last2 = millis();
  long now2 = millis();//记录当前时间 
  Serial.flush(); 
   while (last2-now2< t) {//运行t/1000秒
         while(Serial.available()) {
              subback[i]=Serial.read(); 
              i++;
       }
         last2 = millis(); 
   }
  return i;
}




void pub_topic_delay(char* topic, char* message,int delaytime){
       long now = millis();//记录当前时间
     if (now - lastMsg > delaytime) {//每隔delaytime/1000秒发一次信号
        sendMQTTMessage("888","helloword");
        lastMsg = now;//刷新上一次发送数据的时间
       }
  }




 void in (char* clientId,char* username, char* password){
   String buf="";
 mqttMessageLength= mqtt_connect_message(mqttMessage, clientId,username,password);
 delay(7000);
 for (int j = 0; j < mqttMessageLength; j++) {
  AT.write(mqttMessage[j]); // Message contents
 }
   buf=""; 
   buf=SerialRead(2000);
   Serial.println(buf); 
 
  }


 void sendMQTTMessage( char* topic, char* message ){
 String buf;
 mqttMessageLength = mqtt_publish_message(mqttMessage, topic, message);

 for (int k = 0; k < mqttMessageLength; k++) {
  AT.write(mqttMessage[k]);
 }
  buf=""; 
   buf=SerialRead(1000);
   Serial.println(buf); 

}


 void SUB( char* topic ){
 String buf;
 mqttMessageLength =  mqtt_sub_message(mqttMessage,topic);

 for (int k = 0; k < mqttMessageLength; k++) {
  AT.write(mqttMessage[k]);
 }
  buf=""; 
   buf=SerialRead(1000);
   Serial.println(buf); 

}



void ciphmode(){
   String buf="";
      buf=SerialRead(20000);
   Serial.println(buf); 
   AT.println("ATI");
   buf=""; 
   buf=SerialRead(100);
   Serial.println(buf); 

    AT.println("AT+CCID"); 
    buf="";
    buf=SerialRead(100);
    Serial.println(buf); 

    AT.println("AT+CREG?");
    buf=""; 
    buf=SerialRead(100);
    Serial.println(buf); 
   
    AT.println("AT+CGATT=1"); 
    buf="";
    buf=SerialRead(5000);
    Serial.println(buf); 
   
    AT.println("AT+CGDCONT=1,\"IP\",\"CMNET\""); 
    buf="";
    buf=SerialRead(100);
    Serial.println(buf); 

    AT.println("AT+CGACT=1,1"); 
    buf="";
    buf=SerialRead(4000);
    Serial.println(buf); 

    AT.println("AT+CIPSTART=\"TCP\",\"182.254.140.181\",3381"); 
    buf="";
    buf=SerialRead(7000);
    Serial.println(buf); 

    AT.println("at+ciphcfg?"); 
    buf="";
    buf=SerialRead(1000);
    Serial.println(buf); 

    AT.println("at+ciphcfg=1,55FAFBEE"); 
    buf="";
    buf=SerialRead(100);
    Serial.println(buf); 

    AT.println("at+ciphcfg=2,55AFBFEE"); 
    buf="";
    buf=SerialRead(100);
    Serial.println(buf); 

    AT.println("at+ciphcfg=0,15"); 
    buf="";
    buf=SerialRead(100);
    Serial.println(buf); 

    AT.println("at+ciphmode=1"); 
    buf="";
    buf=SerialRead(100);
    Serial.println(buf); 

    AT.println("AT+CIPTMODE=1"); 
    buf="";
    buf=SerialRead(100);
    Serial.println(buf); 
   
  }



String SerialRead(int t){//接收AT指令反馈
  String buf="";
long last2 = millis();
  long now2 = millis();//记录当前时间
   while (last2-now2< t) {//运行t/1000秒
         while(Serial.available()) {
              buf+=char(Serial.read()); 
       }
         last2 = millis(); 
   }
  return buf;
}






int mqtt_connect_message(unsigned char *mqttMessage,char* client_id,char* username,char* password)  
{   
    char i = 0;    
    char client_id_length = strlen(client_id);    
    int username_length = strlen(username);    
    int password_length = strlen(password);    
    int packetLen = 12 + 2 + client_id_length + 2 + username_length + 2 + password_length;    
        
    mqttMessage[0] = 16;                      // MQTT Message Type CONNECT    
    mqttMessage[1] = packetLen%256;    
    baseIndex = 2;    
    if( packetLen >127 ){//    
        mqttMessage[2] = 1;//packetLen/127;    
        baseIndex = 3;    
    }    
    mqttMessage[baseIndex] = 0;                       // Protocol Name Length MSB    
    mqttMessage[baseIndex+1] = 6;                       // Protocol Name Length LSB    
    mqttMessage[baseIndex+2] = 77;                      // ASCII Code for M    
    mqttMessage[baseIndex+3] = 81;                      // ASCII Code for Q    
    mqttMessage[baseIndex+4] = 73;                      // ASCII Code for I    
    mqttMessage[baseIndex+5] = 115;                     // ASCII Code for s    
    mqttMessage[baseIndex+6] = 100;                     // ASCII Code for d    
    mqttMessage[baseIndex+7] = 112;                     // ASCII Code for p    
    mqttMessage[baseIndex+8] = 3;                      // MQTT Protocol version = 3    
    mqttMessage[baseIndex+9] = 194;                   // conn flags    
    mqttMessage[baseIndex+10] = 0;                      // Keep-alive Time Length MSB    
    mqttMessage[baseIndex+11] = 60;                     // Keep-alive Time Length LSB    
        
    mqttMessage[baseIndex+12] = 0;                      // Client ID length MSB    
    mqttMessage[baseIndex+13] = client_id_length;       // Client ID length LSB    
        
    baseIndex += 14;    
    // Client ID    
    for(i = 0; i < client_id_length; i++){    
        mqttMessage[baseIndex + i] = client_id[i];    
    }    
        
    baseIndex = baseIndex+client_id_length;    
        
    //username    
    mqttMessage[baseIndex] = 0;                      //username length MSB    
    mqttMessage[baseIndex+1] = username_length;       //username length LSB    
    baseIndex = baseIndex+2;    
    for(i = 0; i < username_length ; i++){    
        mqttMessage[baseIndex + i] = username[i];    
    }    
        
    baseIndex = baseIndex + username_length;    
        
    //password    
    mqttMessage[baseIndex] = 0;                      //password length MSB    
    mqttMessage[baseIndex+1] = password_length;       //password length LSB    
    baseIndex = baseIndex + 2;    
    for(i = 0; i < password_length ; i++){    
        mqttMessage[baseIndex + i] = password[i];    
    }    
        
    baseIndex += password_length;    
    
    return baseIndex;    
}  


int mqtt_publish_message(unsigned char *mqttMessage, char  *topic, char  *message) {    
        
    //mqttMessage = 0;    
        
    unsigned char i = 0;    
    unsigned char topic_length = strlen(topic);    
    unsigned char message_length = strlen(message);    
        //固定头部                                        // 7 6 5 4 3 2 1 0   
    mqttMessage[0] = 48;                                  // 0 0 1 1 0 0 0 0
    mqttMessage[1] = 2 + topic_length + message_length;   // Remaining length    
    //可变头部
    mqttMessage[2] = 0;                                   // length MSB 
    mqttMessage[3] = topic_length;                        // length LSB(topic长度）
        
    // Topic    
    for(i = 0; i < topic_length; i++){    
        mqttMessage[4 + i] = topic[i];    
    }    
        
    // Message    
    for(i = 0; i < message_length; i++){    
        mqttMessage[4 + topic_length + i] = message[i];    
    }    
        
    return 4 + topic_length + message_length;    
}

int mqtt_sub_message(unsigned char *mqttMessage, char  *topic) {    
        
    unsigned char i = 0;    
    unsigned char topic_length = strlen(topic);    
        //固定头部                                        // 7 6 5 4 3 2 1 0   
    mqttMessage[0] = 130;                                  // 
    mqttMessage[1] = 5 + topic_length;   // Remaining length    
    //可变头部
    mqttMessage[2] = 0;                                   // length MSB 
    mqttMessage[3] = 10;                        // length LSB

    mqttMessage[4] = 0;                               
    mqttMessage[5] = topic_length;      
        
    // Topic    
    for(i = 0; i < topic_length; i++){    
        mqttMessage[6 + i] = topic[i];    
    }    
 mqttMessage[6+ topic_length]=0;
        
    return 7 + topic_length ;    
}


  

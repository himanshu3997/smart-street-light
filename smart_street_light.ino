
#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;
const char* ssid = "PKD";
const char* password = "Covid1964";
unsigned long myChannelNumber = 1256374;
const char * myWriteAPIKey = "2OCMJQ5SG3Z1BHJV";
const char * myReadAPIKey = "4SZQ6D31BETB8AMX";
WiFiClient client;
int led_1;
int led_2;
int led_3;

int ir1 = D0;
int led1 = D5;

int ir2 = D1;
int led2 = D6;

int ir3 = D2;
int led3 = D7;

int ldr = A0;
int val =0;
pinMode(ir1,INPUT);
  pinMode(led1,OUTPUT);

  pinMode(ir2,INPUT);
  pinMode(led2,OUTPUT);

  pinMode(ir3,INPUT);
  pinMode(led3,OUTPUT);
  WiFi.begin(ssid, password);
ThingSpeak.begin(client);
int s1 = digitalRead(ir1);
  int s2 = digitalRead(ir2);
  int s3 = digitalRead(ir3);
  val = analogRead(ldr);
   if(val<700)
  {
    if(s1==0)
    {
      digitalWrite(led1,LOW);
    }
    else
    {
      digitalWrite(led1,HIGH);
    }
    if(s2==0)
    {
      digitalWrite(led2,LOW);
    }
    else
    {
      digitalWrite(led2,HIGH);
    }
    if(s3==0)
    {
      digitalWrite(led3,LOW);
    }
    else
    {
      digitalWrite(led3,HIGH);
    }
  }
  else
  {
    digitalWrite(led1,LOW);
    digitalWrite(led2,LOW);
    digitalWrite(led3,LOW);
  }
  ThingSpeak.writeField(myChannelNumber, 1,val, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2,s1, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 3,s2, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 4,s3, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 5,led1, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 6,led2, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 7,led3, myWriteAPIKey);
  led_1 = ThingSpeak.readIntField(myChannelNumber, 5, myReadAPIKey);
led_2 = ThingSpeak.readIntField(myChannelNumber, 6, myReadAPIKey);
 led_3 = ThingSpeak.readIntField(myChannelNumber, 7, myReadAPIKey);
  if(led_1==1)
  {
    digitalWrite(led1,HIGH);
  }
  else
  {
    digitalWrite(led1,LOW);
  }

  if(led_2==1)
  {
    digitalWrite(led2,HIGH);
  }
  else
  {
    digitalWrite(led2,LOW);
  }

  if(led_3==1)
  {
    digitalWrite(led3,HIGH);
  }

  else
  {
    digitalWrite(led3,LOW);
  }
 }

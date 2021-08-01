//First all the required libraries are included

#include <ESP8266WiFi.h>;
#include <WiFiClient.h>;
#include <ThingSpeak.h>;

//my wifi ssid and password is given

const char* ssid = "PKD";
const char* password = "Covid1964";

WiFiClient client;

//channel number, read and write API keys from ThingSpeak sever is taken

unsigned long myChannelNumber = 1256374;
const char * myWriteAPIKey = "2OCMJQ5SG3Z1BHJV";
const char * myReadAPIKey = "4SZQ6D31BETB8AMX";

//variable for GPIO pins of leds and IR sensors, ADC channel are defined

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

void setup() {
  Serial.begin(9600);
  delay(10);

  //pinMode for pins of led and IR sensor on the NodeMCU is set
  
  pinMode(ir1,INPUT);
  pinMode(led1,OUTPUT);

  pinMode(ir2,INPUT);
  pinMode(led2,OUTPUT);

  pinMode(ir3,INPUT);
  pinMode(led3,OUTPUT);

  //Initialization of Wi-Fi and ThingSpeak

  WiFi.begin(ssid, password);
  ThingSpeak.begin(client);
}

void loop() {

  //Now  digital values of the IR sensors and analog value of LDR sensors are taken and store them in variables.
  
  int s1 = digitalRead(ir1);
  int s2 = digitalRead(ir2);
  int s3 = digitalRead(ir3);
  s3=not(s3);
  s1=not(s1);
  s2=not(s2);

  val = analogRead(ldr);

  //for displaying the values in serial monitor

  Serial.print(s1);
  Serial.print(":");
  Serial.print(s2);
  Serial.print(":");
  Serial.print(s3);
  Serial.print("  ");
  Serial.println(val);
  
  //Now check the value of LDR sensor for low light. 
  //Here I have set value as 150 means if the analog value of LDR is lower than 150
  //then it will be night time or low light and hence it will turn on the led if IR sensors detect some obstacle or motion.
  //If the analog value of the LDR sensor is more than 150 then it will be considered as daytime and 
  //LEDs will not glow even if IR sensor detects someone passing the street.
  
  if(val<100) // if it is nighttime
  {
    if(s1==0)    // if no object passes
    {
      digitalWrite(led1,LOW);   //led is given low
    }
    else
    {
      digitalWrite(led1,HIGH);   // led is given high
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
  
//Finally upload the data on the ThingSpeak cloud by using function ThingSpeak.writeField(). 
//It take channel number, field number, data (you want to upload in respective field) and write API key. 
//Here we are uploading LDR sensor data, IR sensors data and LEDs data to the ThingSpeak cloud.

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

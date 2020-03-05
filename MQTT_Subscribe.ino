#include<ESP8266WiFi.h>
#include<Adafruit_MQTT_Client.h>

#define led 16 
#define wifi "xxxxxxxxx"
#define password "xxxxxxx"
#define server "io.adafruit.com"
#define port 1883
#define username "xxxxxxx"
#define key "xxxxxx"

WiFiClient esp;
Adafruit_MQTT_Client mqtt(&esp,server,port,username,key);
Adafruit_MQTT_Subscribe feed(&mqtt,username"/feeds/led");


void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(115200);
  delay(10);
  Serial.println("\nAdafruit MQTT");
  Serial.print("Connecting to ");
  Serial.println(wifi);
  WiFi.begin(wifi,password);
  while(WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(".");
    digitalWrite(16,HIGH);
    delay(200);
    digitalWrite(16,LOW);
    delay(200);
   
  }
  Serial.println();
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  mqtt.subscribe(&feed);
  Serial.println("Connecting to MQTT");
  while(mqtt.connect())
  {
    delay(500);
    Serial.print(".");
    
  }

}
 
void loop() {
 while(mqtt.readSubscription(5000))
 {
  Serial.print("Got: ");
  int a=atoi((char *)feed.lastread);
  Serial.print('\t');
  Serial.println(a);
  if(a==0)
  {
    digitalWrite(led,LOW);
    }
    else
    {
      digitalWrite(led,HIGH);
      }
 }
    if(WiFi.status()!=WL_CONNECTED)
  {
    
    digitalWrite(16,HIGH);
    delay(200);
    digitalWrite(16,LOW);
    delay(200);
   
  } 
    

}

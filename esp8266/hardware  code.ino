#include <ESP8266WiFi.h>
String apiKey = "F70F6X29QTE9CWP9";    
const char *ssid =  "vignesh";    
const char *pass =  "12345678";
const char* server = "184.106.153.149";
int sensorPin = A0;   
WiFiClient client;
 void setup() 
{
 Serial.begin(115200);
  Serial.println("Connecting to ");
  Serial.println (ssid);
  WiFi.begin(ssid, pass);
 while (WiFi.status() != WL_CONNECTED)
{
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
}
 void loop() 
{
  int p = analogRead(sensorPin);    
  delay(300);
     if (isnan(p)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }

                         if (client.connect(server,80))                         
{  
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(p/8);
                             postStr +="&field2=";
                             postStr += String(p/8);
                             postStr += "\r\n\r\n";
 
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.println(p/8); 
                             Serial.println("%. The Values Are.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  delay(10000);
}

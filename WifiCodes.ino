#include <SoftwareSerial.h>
SoftwareSerial s(D2,D3);
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

            
#define WIFI_SSID "iPhone"                                           
#define WIFI_PASSWORD "hqaeeb3oeonv1"   
  
void setup() {
  // Initialize Serial port
  Serial.begin(115200);
  s.begin(115200);
  while (!Serial) continue;
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);


  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            //print local IP address
  delay (1000);
}
 
void loop() {
 
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
 
  if (root == JsonObject::invalid())
  {
    return;
    
  }
  //Print the data in the serial monitor
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println("");
  Serial.print("Temperature ");
  float data1=root["temp"];
  Serial.println(data1);
  Serial.print("Humidity    ");
  float data2=root["hum"];
  Serial.println(data2);
  Serial.print("water ");
  float data3=root["water"];
  Serial.println(data3);
   Serial.print("ph ");
  float data4=root["ph"];
  Serial.println(data4);
   Serial.print("cm");
  int data5=root["cm"];
  Serial.println(data5);
  Serial.println("---------------------xxxxx--------------------");
 

 }
}

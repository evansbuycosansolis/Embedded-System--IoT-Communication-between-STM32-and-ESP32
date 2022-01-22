#include <cactus_io_AM2302.h>
#include <Ultrasonic.h>
#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(3,2);
 #define AM2302_PIN 5     
AM2302 dht(AM2302_PIN); 
int watertemp=2;
 float water;
 float calibration = 30.00; //change this value to calibrate
const int analogInPin = A0; 
int sensorValue = 0; 
unsigned long int avgValue; 
float b;
int buf[10],temp;
Ultrasonic ultrasonic(12, 13);
int distance;
void setup() {
   Serial.begin(115200);
   s.begin(115200);
  dht.begin(); 
  
}
StaticJsonBuffer<1000> jsonBuffer;
JsonObject& root = jsonBuffer.createObject();
void loop() {

  //codes for ultra sonic
 distance = ultrasonic.read();
  
  Serial.print("Distance in CM: ");
  Serial.println(distance);
  delay(1000);
  // end of codes for ultrasonic
   dht.readHumidity();
  dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(dht.humidity) || isnan(dht.temperature_C)) {
  Serial.println("AM2302 sensor read failure!");
  return;
  }
////// codes for ph level=========================
   for(int i=0;i<10;i++) 
 { 
 buf[i]=analogRead(analogInPin);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buf[i]>buf[j])
 {
 temp=buf[i];
 buf[i]=buf[j];
 buf[j]=temp;
 }
 }
 }
 avgValue=0;
 for(int i=2;i<8;i++)
 avgValue+=buf[i];
 float pHVol=(float)avgValue*5.0/1024/6;
 float phValue = -5.70 * pHVol + calibration;
 Serial.print("sensor = ");
  Serial.println(phValue);

 //end of the codes for ph level
  water = dht.temperature_C - watertemp;
  // If the DHT-11 is not connected to correct pin or if it doesnot
//work no data will be sent
  root["temp"] = (dht.temperature_C);
  root["hum"] = (dht.humidity);
  root["water"] = (water);
   root["ph"] = (phValue);
      root["cm"] = (distance);
   
if(s.available()>0)
{
 root.printTo(s);
}
}



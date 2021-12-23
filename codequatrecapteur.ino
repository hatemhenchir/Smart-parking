#include <ArduinoJson.h>
#include <SoftwareSerial.h>

// Declare the "link" serial port
// Please see SoftwareSerial library for detail
SoftwareSerial linkSerial(A5, A4); // RX, TX
#define t1 13
#define t11 10
#define t2 9
#define t22 8
#define t3 7
#define t33 6
#define t4 5
#define t44 4

int distanceThreshold = 100;

void setup() {
  // Initialize "debug" serial port
  // The data rate must be much higher than the "link" serial port
  Serial.begin(115200);
  while (!Serial) continue;

  // Initialize the "link" serial port
  // Use the lowest possible data rate to reduce error ratio
  linkSerial.begin(4800);
}
 long readDistance(int triggerPin, int echoPin)
{
  pinMode(triggerPin, OUTPUT); 
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  return pulseIn(echoPin, HIGH);
}
void loop() {
  // Values we want to transmit
  float d1 = 0.01723 * readDistance(t1, t11);
  float d2 = 0.01723 * readDistance(t2, t22);
  float d3 = 0.01723 * readDistance(t3, t33);
  float d4 = 0.01723 * readDistance(t4, t44);
  

  // Print the values on the "debug" serial port
  

  // Create the JSON document
  StaticJsonDocument<200> doc;
  if(d1>10){
  doc["cap1"] = 0;
  }
  else{ 
  doc["cap1"] = 1;
  }
  if(d2>10){
  doc["cap2"] = 0;
  }
  else{ 
  doc["cap2"] = 1;
  }
  if(d3>10){
  doc["cap3"] = 0;
  }
  else{ 
  doc["cap3"] = 1;
  }
  if(d4>10){
  doc["cap4"] = 0;
  }
  else{ 
  doc["cap4"] = 1;
  }
  

  // Send the JSON document over the "link" serial port
  serializeJson(doc, linkSerial);

  // Wait
  delay(5000);
}

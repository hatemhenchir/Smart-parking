#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>
StaticJsonDocument<300> doc;
const char* ssid = "Lenovo A7010";
const char* password = "bluekayn11";
//Your Domain name with URL path or IP address with path
const char* serverName = "http://192.168.43.31:1880/update-sensor";

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastTime = 0;
// Timer set to 10 minutes (600000)
//unsigned long timerDelay = 600000;
// Set timer to 5 seconds (5000)
unsigned long timerDelay = 5000;

// Declare the "link" serial port
// Please see SoftwareSerial library for detail
SoftwareSerial linkSerial(5, 4); // RX, TX

void setup() {
  // Initialize "debug" serial port
  // The data rate must be much higher than the "link" serial port
  Serial.begin(115200);
   WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
 
  Serial.println("Timer set to 5 seconds (timerDelay variable), it will take 5 seconds before publishing the first reading.");
  while (!Serial) continue;

  // Initialize the "link" serial port
  // Use the lowest possible data rate to reduce error ratio
  linkSerial.begin(4800);
}
 
void loop() {
  // Check if the other Arduino is transmitting
  if (linkSerial.available()) 
  {
    // Allocate the JSON document
    // This one must be bigger than for the sender because it must store the strings
    

    // Read the JSON document from the "link" serial port
    DeserializationError err = deserializeJson(doc, linkSerial);

    if (err == DeserializationError::Ok) 
    {
      // Print the values
      // (we must use as<T>() to resolve the ambiguity)
      Serial.print("cap1 = ");
      Serial.println(doc["cap1"].as<int>());
      Serial.print("cap2 = ");
      Serial.println(doc["cap2"].as<int>());
      Serial.print("cap3 = ");
      Serial.println(doc["cap3"].as<int>());
      Serial.print("cap4 = ");
      Serial.println(doc["cap4"].as<int>());
    } 
    else 
    {
      // Print error to the "debug" serial port
      Serial.print("deserializeJson() returned ");
      Serial.println(err.c_str());
  
      // Flush all bytes in the "link" serial port buffer
      while (linkSerial.available() > 0)
        linkSerial.read();
    }
    
  }
  if ((millis() - lastTime) > timerDelay) {
    //Check WiFi connection status
    if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, serverName);

      // Specify content-type header
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");
      // Data to send with HTTP POST
      String ch="api_key=tPmAT5Ab3j7F9";
      String ch1="&cap1=";
      int ch2=doc["cap1"];
      String ch3=ch1+ch2;
      String ch4=ch+ch3;
      String ch5="&cap2=";
      int ch6=doc["cap2"];
      String ch7=ch5+ch6;
      String ch8=ch4+ch7;
      String ch9="&cap3=";
      int ch10=doc["cap3"];
      String ch11=ch9+ch10;
      String ch12=ch8+ch11;
      String ch13="&cap4=";
      int ch14=doc["cap4"];
      String ch15=ch13+ch14;
      String ch16=ch12+ch15;
      String httpRequestData = ch16;           
      // Send HTTP POST request
      int httpResponseCode = http.POST(httpRequestData);
      
      // If you need an HTTP request with a content type: application/json, use the following:
      //http.addHeader("Content-Type", "application/json");
      //int httpResponseCode = http.POST("{\"api_key\":\"tPmAT5Ab3j7F9\",\"sensor\":\"BME280\",\"value1\":\"24.25\",\"value2\":\"49.54\",\"value3\":\"1005.14\"}");

      // If you need an HTTP request with a content type: text/plain
      //http.addHeader("Content-Type", "text/plain");
      //int httpResponseCode = http.POST("Hello, World!");
     
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
        
      // Free resources
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}

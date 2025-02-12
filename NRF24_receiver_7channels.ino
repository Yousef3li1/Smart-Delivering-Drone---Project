#define BLYNK_TEMPLATE_ID "TMPLmmTli_q5"
#define BLYNK_DEVICE_NAME "the catcher"
#define BLYNK_AUTH_TOKEN "DbWB2_HVh2pd9hw9Yj3OklmtafBTT5fT"


#define BLYNK_PRINT Serial
#include <WiFi.h>
//#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp32.h>

#include <DHT.h>


char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "TP-Link_4DBA";  
char pass[] = "91576811";

BlynkTimer timer;


#define DHTPIN 2 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V1, t);
    Blynk.virtualWrite(V2, h);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("    Humidity : ");
    Serial.println(h);
}
void setup()
{   
  
  Serial.begin(115200);
  

  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(100L, sendSensor);
 
  }

void loop()
{
  Blynk.run();
  timer.run();
 }

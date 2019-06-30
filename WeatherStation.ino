#include "DHTesp.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define DHTpin 5
#define TIME_TO_SLEEP 15
#define uS_TO_MIN_FACTOR 60000000

char auth[] = "MYAUTHKEY";
char ssid[] = "MYHOMESSID";
char pass[] = "MYHOMEPASSWORD";

DHTesp dht;
BlynkTimer timer;

void setup()
{
  Serial.begin(115200);
  delay(1000); 
  Serial.println("Starting up");
  
  dht.setup(DHTpin, DHTesp::DHT11);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Serial.println("Sending data to Blynk");
  getData();
  Blynk.run();
  
  delay(1000);
  
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_MIN_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) + " Minutes");

  //Go to sleep now
  esp_deep_sleep_start();
}

void getData() {
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();
  float heatIndex = dht.computeHeatIndex(temperature, humidity, false);
  
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, temperature);
  Blynk.virtualWrite(V3, heatIndex);
}

/* 
 * ESP32 NodeMCU DHT11 - Humidity Temperature Sensor Example
 * https://circuits4you.com
 * 
 * References
 * https://circuits4you.com/2017/12/31/nodemcu-pinout/
 * 
 */
 
#include "DHTesp.h"

#define DHTpin 5    //D5 of ESP32 DevKit

DHTesp dht;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  Serial.println("Status\tHumidity (%)\tTemp (C)\tHeatIndex (C)");
  
  dht.setup(DHTpin, DHTesp::DHT11); //for DHT11 Connect DHT sensor to GPIO 17
}

void loop()
{
  //delay(dht.getMinimumSamplingPeriod());
  delay(5000);
  
  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();

  Serial.print(dht.getStatusString());
  Serial.print("\t");
  Serial.print(humidity, 1);
  Serial.print("\t\t");
  Serial.print(temperature, 1);
  Serial.print("\t\t");
  Serial.println(dht.computeHeatIndex(temperature, humidity, false), 1);
}

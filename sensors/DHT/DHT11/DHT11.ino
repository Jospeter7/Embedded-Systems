#include <DHT.h>

#define DHTPIN D4     
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); 
  dht.begin();        
}

void loop() {
  float hum = dht.readHumidity();   
  float temp = dht.readTemperature();

  
  if (isnan(hum) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    delay(10000); 
    return;
  }


  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(" °C");

  Serial.print("Humidity: ");
  Serial.print(hum);
  Serial.println(" %");

  delay(10000); 
}

#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTPIN 7
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);

void setup()
{
  lcd.begin(16, 2);
  dht.begin();
}
void loop(){
  lcd.clear();
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  lcd.setCursor(0,0);
  lcd.print(" TEMPE.: ");
  lcd.print(temp);
  lcd.print(" C ");
  lcd.setCursor(0,1);
  lcd.print(" HUMI.: ");
  lcd.print(hum);
  lcd.print(" % ");
  delay(10000);
  if(isnan(hum)||isnan(temp)){
    lcd.print("AUTOCONFIGURING SYSTEM");
    delay(10000);
    return;
  }

}


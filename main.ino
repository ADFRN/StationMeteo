#include <Adafruit_BME280.h>                
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <LiquidCrystal_I2C.h>
#include <WiFiNINA.h>
#include <SPI.h>
#include <WiFiNINA.h>


#define adresseI2CduBME280                0x76            
#define pressionAuNiveauDeLaMerEnHpa      1024.90                  

Adafruit_BME280 bme;
LiquidCrystal_I2C lcd(0x27, 16, 2);

char ssid[] = "TON SSID ICI";
char pass[] = "TON MDP ICI";
int status = WL_IDLE_STATUS;

void setup() {
  
  Serial.begin(9600);
  while(!Serial);

  lcd.init();
  lcd.backlight();

  while (status != WL_CONNECTED) {
    lcd.setCursor(3,0);
    lcd.print("CONNEXION..");
    status = WiFi.begin(ssid, pass);
    delay(10000);
    lcd.clear();
  }

  lcd.setCursor(4,0);
  lcd.print("CONNEXION");
  lcd.setCursor(5,1);
  lcd.print("ETABLIE");
  delay(5000);
  lcd.clear();

  bme.begin(adresseI2CduBME280);
}

void loop() {

  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Station13");

  lcd.setCursor(2,1);
  IPAddress ip = WiFi.localIP();
  lcd.print(ip);

  delay(5000);

  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("Temp: ");
  lcd.print(bme.readTemperature());
  lcd.print(" C");

  lcd.setCursor(2,0);
  lcd.print("Hum: ");
  lcd.print(bme.readHumidity());
  lcd.print(" %");

  delay(5000);

  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print("PA: ");
  lcd.print(bme.readPressure() / 100.0F);
  lcd.print(" hPa");

  lcd.setCursor(2,0);
  lcd.print("Alt: ");
  lcd.print(bme.readAltitude(pressionAuNiveauDeLaMerEnHpa));
  lcd.print(" m");

  delay(5000);
}

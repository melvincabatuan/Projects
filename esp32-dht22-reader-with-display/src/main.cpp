
#include <Arduino.h>
#include <Wire.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 4
#define DHTTYPE DHT22

#define SDA_PIN 21
#define SCL_PIN 22

DHT dht(DHTPIN, DHTTYPE);

// LCD address, columns, rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    Serial.begin(115200);

    // Initialize I2C
    Wire.begin(SDA_PIN, SCL_PIN);

    // Initialize LCD
    lcd.init();
    lcd.backlight();
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("ESP32 DHT22");
    lcd.setCursor(0, 1);
    lcd.print("Initializing...");

    // Initialize DHT22
    dht.begin();

    delay(2000);
    lcd.clear();
}

void loop() {
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    if (isnan(humidity) || isnan(temperature)) {
        Serial.println("Sensor read failed");

        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Sensor Error");
    } else {
        Serial.printf("Temp: %.1f C | Humidity: %.1f%%\n",
                      temperature, humidity);

        lcd.setCursor(0, 0);
        lcd.print("Temp: ");
        lcd.print(temperature, 1);
        lcd.print((char)223);
        lcd.print("C   ");

        lcd.setCursor(0, 1);
        lcd.print("Humidity: ");
        lcd.print(humidity, 1);
        lcd.print("%  ");
    }

    delay(2000);
}

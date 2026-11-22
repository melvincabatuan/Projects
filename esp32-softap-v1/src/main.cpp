#include <Arduino.h>
#include <WiFi.h>  // Include ESP32 Wi-Fi functions

// Set the Wi-Fi network name and password
const char ssid[] = "ESP32-AP";
const char pass[] = "esp32accesspoint";

// OPTIONAL: Set the access point's IP address and network settings
// IPAddress ip(192, 168, 1, 1);       // default: 192.168.4.1
// IPAddress gateway(192, 168, 1, 1);  // default: 192.168.4.1
// IPAddress subnet(255, 255, 255, 0); // default: 255.255.255.0

// Store the previous number of connected devices
int currentNumOfStation = -1;

void setup() {
    Serial.begin(115200);  // Start Serial Monitor
    delay(500);            // Allow time for Serial initialization

    WiFi.mode(WIFI_AP);    // Set ESP32 to Access Point mode
    // https://docs.espressif.com/projects/arduino-esp32/en/latest/api/wifi.html

    // Configure the access point's IP settings
    // if (!WiFi.softAPConfig(ip, gateway, subnet)) {
    //     Serial.println("Config Failed!");
    //     return;  // Stop setup if configuration fails
    // }

    Serial.println("Config Ready");

    // Create the Wi-Fi access point using the SSID and password
    if (!WiFi.softAP(ssid, pass)) {
        Serial.println("AP Failed!");
        return;  
    }

    Serial.println("AP Ready");

    Serial.print("SSID: ");
    Serial.println(ssid);  // Display the Wi-Fi network name

    Serial.print("IP address: ");
    Serial.println(WiFi.softAPIP());  // Display the access point's IP
}

void loop() {
    // Get the current number of connected devices
    int n = WiFi.softAPgetStationNum();

    // Check whether the number of connected devices has changed
    if (n != currentNumOfStation) {
        currentNumOfStation = n;  // Update the previous count

        // Display the updated number of connected devices
        Serial.printf("Stations connected to AP: %d\n", n);
    }

    delay(200);  // Wait before checking again
}
#include <M5StickCPlus.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

// Define the GPIO pin that the data line of the temperature sensor is connected to
#define ONE_WIRE_BUS 26

// Define your WiFi credentials
const char* ssid = "geoffreywifi";
const char* password = "Gefofrey2";

// Define the API endpoint URL
const char* url = "https://mmi20d13.mmi-troyes.fr/esp/post.php";

// Create a OneWire instance to communicate with the sensor
OneWire oneWire(ONE_WIRE_BUS);

// Create a DallasTemperature instance to work with the sensor
DallasTemperature sensors(&oneWire);

void setup() {
  // Initialize M5StickC Plus
  M5.begin();

  // Initialize the sensors
  sensors.begin();

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
}

void loop() {
  // Request temperature readings from all connected sensors
  sensors.requestTemperatures();

  // Read the temperature from the first sensor
  float temperature = sensors.getTempCByIndex(0);

  String url = "https://mmi20d13.mmi-troyes.fr/esp/post.php?temperature=" + String(temperature);
  
  HTTPClient http;
  http.begin(url);
  int httpCode = http.GET();
  if (httpCode == HTTP_CODE_OK) {
    String payload = http.getString();
    Serial.println(payload);
  }
  else {
    Serial.printf("HTTP error: %s\n", http.errorToString(httpCode).c_str());
  }
  
  http.end();

  // Wait for a short time before taking another reading
  delay(30000);
}

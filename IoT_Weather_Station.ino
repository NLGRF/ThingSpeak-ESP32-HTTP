#include <WiFi.h>

const char* ssid = "kidbright";
const char* password = "12345678";

const char* host = "api.thingspeak.com";
String api_key = "S0R2P1E0TH8K2SUY"; // Your API Key provied by thingspeak
String api_key_read = "channels/328411/fields/1/last"; // Your API Key provied by thingspeak
/*
  //Library for ESP Sleep
  #include "esp_deep_sleep.h"

  #define uS_TO_m_FACTOR 60000000   // Conversion factor for micro seconds to minutes
  #define TIME_TO_SLEEP  1        // Time ESP32 will go to sleep (in minutes)
*/
int test;

void setup() {

  Serial.begin(115200);
  Serial.println("");
  pinMode(LED_BUILTIN, OUTPUT);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Get_Values();

  //  Send_Data();

  /*
    esp_deep_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_m_FACTOR);

    Serial.println("Going to sleep now");

    esp_deep_sleep_start();
  */

}

void loop() {
  // put your main code here, to run repeatedly:
   Get_Values();
   Send_Data();
  //Get_Data();
}


void Get_Values()
{

  test = random(1, 10);
  //delay(100);

  Serial.println("Collect data");

  Serial.print("Number :");
  Serial.print(test);

}

void Send_Data()
{

  Serial.println("Prepare to send data");

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  else
  {
    String data_to_send = api_key;
    data_to_send += "&field1=";
    data_to_send += String(test);

    data_to_send += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);

    delay(15000);
  }

  client.stop();

}


void Get_Data() // No success
{

  Serial.println("Data");

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  const int httpPort = 80;

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  else
  {
    String data_to_send = api_key_read;
    //  data_to_send += "&field1=";
    //  data_to_send += String(test);

    data_to_send += "\r\n\r\n";

    client.print("POST HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print(api_key_read + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);

    while (client.available()) {
      char c = client.read();
      Serial.print(c);
    }

    delay(15000);
  }

  client.stop();

}

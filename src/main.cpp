#include <Arduino.h>
#include <WiFi.h>
#include <FS.h>                   //this needs to be first, or it all crashes and burns...

//needed for library
#include <DNSServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager

void setup() {

  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Start WifiManager test:");
  Serial.println("- Command: r=reset_wifi c=continu. Make your choice\n\r");
  while(!Serial.available()){}
	uint8_t c = (uint8_t)Serial.read();
  
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;


  //reset settings - for testing
  if (c=='r')
    wifiManager.resetSettings();


  //tries to connect to last known settings or start access point
  if (!wifiManager.autoConnect("ESP32-Dudu")) {
    Serial.println("failed to connect, we should reset as see if it connects");
    delay(3000);
    ESP.restart();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...yeey :)");

  Serial.println("local ip");
  Serial.println(WiFi.localIP());

  Serial.println("Reboot in 30 sec.");

  delay(30000);
  ESP.restart();
}

void loop() {
  // put your main code here, to run repeatedly:
}

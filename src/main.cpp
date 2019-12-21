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
  

    // BUG IMPOSSIBLE TO SET MAC since last version....
    // ATTENTION A L'ADRESSE 
    uint8_t MacAddress[] = {0xAA,2,3,4,5,0x1};
    esp_base_mac_addr_set(MacAddress); // Wifi_STA=mac  wifi_AP=mac+1  BT=mac+2
 
   //wifi_set_macaddr(SOFTAP_IF, MacAddress); //8688 code
   //wifi_set_macaddr(STATION_IF, MacAddress); //8688 code
   esp_wifi_set_mac(ESP_IF_WIFI_STA, MacAddress); // esp32 code

  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;


  //reset settings - for testing
  if (c=='r')
    wifiManager.resetSettings();

  Serial.printf("IP:%s MAC:%s \n\r", WiFi.localIP().toString().c_str() , WiFi.macAddress().c_str()); 


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

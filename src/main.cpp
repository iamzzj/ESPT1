#include <Arduino.h>
#include "WiFiManager.h"
#include "WebServer.hpp"
#include "SocketClient.hpp"

WebServer web_server;
SocketClient socket_client;
int loop_count;

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(74880);

  WiFiManager wifi_manager;

  wifi_manager.connectWiFi(
      (char *)"GX",
      (char *)"999999999");

  // wifi
  Serial.printf("WiFi ssid ");
  Serial.print(WiFi.SSID());
  Serial.printf(" localIp: ");
  Serial.print(WiFi.localIP());
  Serial.printf("\n");

  wifi_manager.openWiFiAp(
      (char *)"1104",
      (char *)"1104wifipwd");

  IPAddress ap_ip_address = WiFi.softAPIP();

  // web_server
  web_server.start();

  Serial.printf("WebServer start ");
  Serial.print(ap_ip_address);
  Serial.printf(":%d \n", web_server.getPort());

  // socket server

  // socket client
  socket_client.connect("192.168.0.106", 81, "/");
}

void loop()
{
  // web_server
  web_server.handleClient();

  loop_count++;

  if (loop_count % 100000 == 0)
  {
    // Heap Free
    Serial.printf("Connect AP Count: (%d), Heap Free %d\n", WiFi.softAPgetStationNum(), ESP.getFreeHeap());

    // socket client
    socket_client.loop();
  }
}

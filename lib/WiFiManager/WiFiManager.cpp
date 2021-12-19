#include "WiFiManager.h"
#include <ESP8266WiFi.h>
#include <lwip/napt.h>
#include <lwip/dns.h>
#include <LwipDhcpServer.h>

WiFiManager::WiFiManager()
{
}

WiFiManager::~WiFiManager()
{
}

void WiFiManager::connectWiFi(char *wifi_ssid, char *wifi_pwd)
{
  WiFi.mode(WIFI_STA);

  Serial.printf("连接WIFI  ");
  Serial.printf(wifi_ssid);
  Serial.printf("  ");
  Serial.println(wifi_pwd);

  WiFi.begin(wifi_ssid, wifi_pwd);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("正在连接WIFI");
  }

  Serial.println("连接WIFI成功");
  Serial.print("WIFI:");
  Serial.println(WiFi.SSID());
  Serial.print("PWD:");
  Serial.println(WiFi.psk());
}

void WiFiManager::openWiFiAp(char *wifi_ap_ssid, char *wifi_ap_pwd)
{

  // first, connect to STA so we can get a proper local DNS server
  // give DNS servers to AP side
  dhcpSoftAP.dhcps_set_dns(0, WiFi.dnsIP(0));
  dhcpSoftAP.dhcps_set_dns(1, WiFi.dnsIP(1));

  WiFi.softAPConfig( // enable AP, with android-compatible google domain
      IPAddress(192, 168, 110, 1),
      IPAddress(192, 168, 110, 1),
      IPAddress(255, 255, 255, 0));
  WiFi.softAP(wifi_ap_ssid, wifi_ap_pwd);

  Serial.print("AP_IP:");
  Serial.println(WiFi.softAPIP());
  Serial.print("AP_SSID:");
  Serial.println(WiFi.softAPSSID());
  Serial.print("AP_PWD:");
  Serial.println(WiFi.softAPPSK());

  Serial.printf("Heap before: %d\n", ESP.getFreeHeap());
  err_t ret = ip_napt_init(NAPT, NAPT_PORT);
  Serial.printf("ip_napt_init(%d,%d): ret=%d (OK=%d)\n", NAPT, NAPT_PORT, (int)ret, (int)ERR_OK);
  if (ret == ERR_OK)
  {
    ret = ip_napt_enable_no(SOFTAP_IF, 1);
    Serial.printf("ip_napt_enable_no(SOFTAP_IF): ret=%d (OK=%d)\n", (int)ret, (int)ERR_OK);
    if (ret == ERR_OK)
    {
      Serial.printf("WiFi Network '%s' with same password is now NATed behind '%s'\n", wifi_ap_ssid, wifi_ap_pwd);
    }
  }
  Serial.printf("Heap after napt init: %d\n", ESP.getFreeHeap());
  if (ret != ERR_OK)
  {
    Serial.printf("NAPT initialization failed\n");
  }
}
#ifndef WIFI_MANAGER
#define WIFI_MANAGER

#define NAPT 1000
#define NAPT_PORT 10

class WiFiManager
{
private:
public:
    WiFiManager();
    ~WiFiManager();

public:
    void connectWiFi(char *wifi_ssid, char *wifi_pwd);
    void openWiFiAp(char *wifi_ap_ssid, char *wifi_ap_pwd);
};

#endif
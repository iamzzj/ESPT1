#ifndef WEB_SERVER
#define WEB_SERBER

#include <ESP8266WebServer.h>

const String INDEX_HTML = "<!DOCTYPE html><html><body><button>button</button></body></html>";

class WebServer
{
private:
    int port;
    ESP8266WebServer *p_server;

public:
    WebServer() : port(80)
    {
        p_server = new ESP8266WebServer(port);
    }

    WebServer(int port)
    {
        this->port = port;
        p_server = new ESP8266WebServer(port);
    }

    ~WebServer()
    {
        delete p_server;
        Serial.println("~WebServer()");
    }

public:
    int getPort() {
        return this->port;
    }

    void start()
    {
        p_server->on("/", [=]()
                     { p_server->send(200, "text/plain", "ESP8266 WebServer"); });
        p_server->on("/index.html", [=]()
                     { p_server->send(200, "text/html", INDEX_HTML); });
        p_server->on("/get", HTTP_GET, [=]()
                     { p_server->send(200, "text/application", "{\"ret\": 1, \"msg\": \"success\"}"); });
        p_server->begin();
    }

    void handleClient()
    {
        p_server->handleClient();
    }
};

#endif
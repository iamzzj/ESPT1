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
        pinMode(LED_BUILTIN, OUTPUT);
        p_server = new ESP8266WebServer(port);
    }

    WebServer(int port)
    {
        this->port = port;
        pinMode(LED_BUILTIN, OUTPUT);
        p_server = new ESP8266WebServer(port);
    }

    ~WebServer()
    {
        delete p_server;
        Serial.println("~WebServer()");
    }

public:
    int getPort()
    {
        return this->port;
    }

    void start()
    {
        p_server->on("/", [=]()
                     { p_server->send(200, "text/plain", "ESP8266 WebServer"); });
        p_server->on("/button", HTTP_GET, [=]()
                     { p_server->send(200, "text/html", "<form action=\"/led\" method=\"POST\"><input type=\"submit\" value=\"Toggle LED\"></form>"); });
        p_server->on("/led", HTTP_POST, [=]()
                     {
                         digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
                         p_server->sendHeader("Location", "/button");
                         p_server->send(303);
                     });
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
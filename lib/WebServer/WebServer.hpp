#ifndef WEB_SERVER
#define WEB_SERBER

#include <ESP8266WebServer.h>
#include <LittleFS.h>

class WebServer
{
private:
    int port;
    ESP8266WebServer *p_server;

public:
    WebServer() : port(80)
    {
        pinMode(LED_BUILTIN, OUTPUT);
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN)); //关闭系统灯，因为默认是打开的
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
        p_server->on("/get", HTTP_GET, [=]()
                     { p_server->send(200, "text/application", "{\"ret\": 1, \"msg\": \"success\"}"); });
        p_server->onNotFound([=]()
                             {
                                 String web_address = p_server->uri();
                                 Serial.printf("Web Server web_address: %s\n", web_address.c_str());
                                 if (LittleFS.exists(web_address))
                                 {
                                     File file = LittleFS.open(web_address, "r");
                                     p_server->streamFile(file, getContentType(web_address));
                                     file.close();
                                 }
                                 else
                                 {
                                     p_server->send(404, "text/plain", "404 Not Found");
                                 }
                             });
        p_server->begin();
    }

    String getContentType(String filename)
    {
        if (filename.endsWith(".htm"))
            return "text/html";
        else if (filename.endsWith(".html"))
            return "text/html";
        else if (filename.endsWith(".css"))
            return "text/css";
        else if (filename.endsWith(".js"))
            return "application/javascript";
        else if (filename.endsWith(".png"))
            return "image/png";
        else if (filename.endsWith(".gif"))
            return "image/gif";
        else if (filename.endsWith(".jpg"))
            return "image/jpeg";
        else if (filename.endsWith(".ico"))
            return "image/x-icon";
        else if (filename.endsWith(".xml"))
            return "text/xml";
        else if (filename.endsWith(".pdf"))
            return "application/x-pdf";
        else if (filename.endsWith(".zip"))
            return "application/x-zip";
        else if (filename.endsWith(".gz"))
            return "application/x-gzip";
        return "text/plain";
    }

    void handleClient()
    {
        p_server->handleClient();
    }
};

#endif
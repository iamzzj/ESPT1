#ifndef SOCKET_CLIENT
#define SOCKET_CLIENT

#include <ArduinoWebsockets.h>
#include <string>

using namespace std;

using namespace websockets;

class SocketClient
{
private:
    int seq = 0;
    WebsocketsClient *p_client;
    /* data */
public:
    SocketClient(/* args */)
    {
        p_client = new WebsocketsClient();
    }
    ~SocketClient()
    {
        delete p_client;
    }

public:
    void connect(WSInterfaceString host, int port, WSInterfaceString path)
    {
        bool connected = p_client->connect(host, port, path);

        if (connected)
        {
            Serial.println("WebClient Connecetd!");
        }
        else
        {
            Serial.println("WebClient Not Connected!");
        }

        // run callback when messages are received
        p_client->onMessage([=](WebsocketsMessage message)
                            {
                                Serial.print("WebClient Got onMessage: ");
                                Serial.println(message.data());
                            });

        p_client->onEvent([=](WebsocketsEvent event, WSInterfaceString data)
                          {
                              Serial.print("WebClient onEvent: ");
                              Serial.println(data);
                          });
    }

    void loop()
    {
        if (p_client->available())
        {
            string message = "seq " + to_string(seq++);
            Serial.printf("WebClient Send Message: %s\n", message.c_str());
            p_client->send(message.c_str());

            p_client->poll();

        }
    }
};

#endif
#ifndef SOCKET_CLIENT
#define SOCKET_CLIENT

#include <ArduinoWebsockets.h>

using namespace websockets;

class SocketClient
{
private:
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
            p_client->send("hello");
        }
        else
        {
            Serial.println("WebClient Not Connected!");
        }

        // run callback when messages are received
        p_client->onMessage([&](WebsocketsMessage message)
                            {
                                Serial.print("WebClient Got onMessage: ");
                                Serial.println(message.data());

                                p_client->send("message");
                            });

        p_client->onEvent([=](WebsocketsEvent event, WSInterfaceString data)
                          {
                              Serial.print("WebClient onEvent: ");
                              Serial.println(data);
                          });
    }
};

#endif
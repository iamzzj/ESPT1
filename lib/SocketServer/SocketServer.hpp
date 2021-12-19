#ifndef SOCKET_SERVER
#define SOCKET_SERVER

#include <ArduinoWebsockets.h>
#include <Ticker.h>

using namespace websockets;

class SocketServer
{
private:
    Ticker tiker;
    int port;
    WebsocketsServer *p_server;
    WebsocketsClient *c_client = NULL;

public:
    SocketServer() : port(81)
    {
        p_server = new WebsocketsServer();
    }

    ~SocketServer()
    {
        delete p_server;
    }

public:
    int getPort()
    {
        return this->port;
    }

    void listen()
    {
        p_server->listen(port);
        Serial.printf("WebSocketServer: %d\n" + p_server->available());

        //Serial.printf("SocketServer start ws://");
        //Serial.print(ap_ip_address);
        //Serial.printf(":%d \n", socket_server.getPort());

        /*tiker.attach(1, [=]()
                     {
                         Serial.printf("WebSocketServer1: \n");
                         if (this->c_client == NULL || !(this->c_client->available()))
                         {
                             Serial.printf("WebSocketServer2: \n");
                             // 这里阻塞住了，等待连接客户端，想办法多线程
                             WebsocketsClient client = p_server->accept();

                             this->c_client = &client;

                             // 一个客户端，循环给它发送消息
                             while (client.available())
                             {
                                 WebsocketsMessage msg = client.readBlocking();
                                 // log
                                 Serial.print("WebSocketServer Got Message: ");
                                 Serial.println(msg.data());

                                 // return echo
                                 client.send("WebSocketServer Echo: " + msg.data());

                                 // close the connection
                                 //client.close();
                             }
                         }
                     });*/
    }

    void loop()
    {
        // 这里阻塞住了，等待连接客户端，想办法多线程
        WebsocketsClient client = p_server->accept();
        // 一个客户端，循环给它发送消息
        while (client.available())
        {
            WebsocketsMessage msg = client.readBlocking();
            // log
            Serial.print("WebSocketServer Got Message: ");
            Serial.println(msg.data());

            // return echo
            client.send("WebSocketServer Echo: " + msg.data());

            // close the connection
            //client.close();
        }
    }
};

#endif
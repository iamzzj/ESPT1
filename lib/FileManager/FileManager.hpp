#ifndef FILE_MANAGER
#define FILE_MANAGER

#include <LittleFS.h>

class FileManager
{
private:
    /* data */
public:
    FileManager(/* args */)
    {
        //LittleFS.format();    // 格式化SPIFFS

        if (LittleFS.begin())
        { // 启动闪存文件系统
            Serial.println("FileManager LittleFS Started.");
        }
        else
        {
            Serial.println("FileManager LittleFS Failed to Start.");
        }
    }
    ~FileManager()
    {
    }

public:
    void write(String file_name, String text)
    {
        File dataFile = LittleFS.open(file_name, "w"); // 建立File对象用于向SPIFFS中的file对象（即/notes.txt）写入信息
        dataFile.println(text);                        // 向dataFile写入字符串信息
        dataFile.close();
    }

    void read(String file_name)
    {
        //确认闪存中是否有file_name文件
        if (LittleFS.exists(file_name))
        {
            Serial.print(file_name);
            Serial.println("FileManager FOUND.");

            //建立File对象用于从SPIFFS中读取文件
            File dataFile = LittleFS.open(file_name, "r");

            //读取文件内容并且通过串口监视器输出文件信息
            for (size_t i = 0; i < dataFile.size(); i++)
            {
                Serial.print((char)dataFile.read());
            }

            //完成文件读取后关闭文件
            dataFile.close();
        }
        else
        {
            Serial.print(file_name);
            Serial.print("FileManager NOT FOUND.");
        }
    }
};

#endif
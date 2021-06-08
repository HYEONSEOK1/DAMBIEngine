#pragma once
#include <mutex>
#include <queue>
#define LOG_LEVEL_FATAL 10
#define LOG_LEVEL_ERROR 20
#define LOG_LEVEL_WARN 30
#define LOG_LEVEL_INFO 40
#define LOG_LEVEL_DEBUG 50
#define LOG_LEVEL_TRACE 60
class Logger {
private:
    int logLevel;
    bool isOutput;
    std::queue<char*> LogQueue;
    std::string getTimestamp();
    std::mutex mtx;
    std::ofstream *filestream;
    
   
public:
    Logger();
    Logger(int level);
   
    bool isLogEmpty();
    void LogWrite();
    void LogPush(const char* funcName, int line, int level, const char* str, ...);
};


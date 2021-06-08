#include <fstream>
#include <queue>
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <mutex>
#include <queue>
#include "extern.h"
#include <stdarg.h>


Logger::Logger()
{
    this->logLevel = LOG_LEVEL_ERROR;
    std::ofstream out("Log.txt");
    filestream = new std::ofstream;
    filestream->open("Log.txt");
}
Logger::Logger(int level)
{
    this->logLevel = level;
}
std::string Logger::getTimestamp()
{
    std::string result;
    time_t currentSec = time(NULL);
    tm* t = localtime(&currentSec);
    std::ostringstream oss;
    switch (t->tm_mon)
    {
    case(0): result = "Jan"; break;
    case(1): result = "Feb"; break;
    case(2): result = "Mar"; break;
    case(3): result = "Apr"; break;
    case(4): result = "May"; break;
    case(5): result = "Jun"; break;
    case(6): result = "Jul"; break;
    case(7): result = "Aug"; break;
    case(8): result = "Sep"; break;
    case(9): result = "Oct"; break;
    case(10): result = "Nov"; break;
    case(11): result = "Dec"; break;
    }
    oss.clear();
    oss << " " << std::setfill('0') << std::setw(2) << t->tm_mday << " " << t->tm_year + 1900;
    oss << " " << std::setfill('0') << std::setw(2) << t->tm_hour;
    oss << ":" << std::setfill('0') << std::setw(2) << t->tm_min;
    oss << ":" << std::setfill('0') << std::setw(2) << t->tm_sec << '\0';
    result = result + oss.str();
    return result;
}
bool Logger::isLogEmpty()
{
    return LogQueue.empty();
}
void Logger::LogWrite()
{
    mtx.lock();
    if (!LogQueue.empty())
    {
        std::string nxtLine = "\n";
        std::string msg = LogQueue.front() + nxtLine;
        const char* fileMsg = msg.c_str();
        LogQueue.pop();
        filestream->write(fileMsg, strlen(fileMsg));

        filestream->flush();
        /*std::vector<char> writable(msg.begin(), msg.end());
        writable.push_back('\0');
        char* fileMsg = &writable[0];
        filestream->write(fileMsg, strlen(fileMsg));
        free(fileMsg);*/
    }
    mtx.unlock();
}
void Logger::LogPush(const char* funcName, int line, int lv, const char* str, ...)
{
    va_list Ap;
    char Buffer[1024];
    memset(Buffer, 0, sizeof(Buffer));
    va_start(Ap, str);
    vsprintf(Buffer, str, Ap);
    va_end(Ap);
    char* result = NULL;
    char level[10];
    switch (lv)
    {
    case(LOG_LEVEL_FATAL): strcpy(level, "[FATAL]"); break;
    case(LOG_LEVEL_ERROR): strcpy(level, "[ERROR]"); break;
    case(LOG_LEVEL_WARN): strcpy(level, "[WARN] "); break;
    case(LOG_LEVEL_INFO): strcpy(level, "[INFO] "); break;
    case(LOG_LEVEL_DEBUG): strcpy(level, "[DEBUG]"); break;
    case(LOG_LEVEL_TRACE): strcpy(level, "[TRACE]"); break;
    }

    result = (char*)malloc(sizeof(char) * (21 + strlen(funcName) + strlen(str) + 30));
    sprintf(result, "%s %s [%s:%d] : %s", level, getTimestamp().c_str(), funcName, line, Buffer);
    mtx.lock();
    LogQueue.push(result);
    mtx.unlock();
    return;
}
#pragma once

#include <iostream>
#include <ctime>
#include <cstdio>
#include <cstdarg>
#include <sys/types.h>
#include <unistd.h>
#include <string>

const std::string filename = "tcp_server.log";

enum
{
    Debug = 0,
    Info,
    Warning,
    Error,
    Fatal,
    Unknow,
    Setsid,
    Open
};

static std::string getlevel_string(int level)
{
    switch (level)
    {
    case Debug:
        return "Debug";
    case Info:
        return "Info";
    case Warning:
        return "Warning ";
    case Error:
        return "Error";
    case Fatal:
        return "Fatal";
    default:
        return "Unkown";
    }
}
static std::string gettime_string()
{
    time_t currtime = time(nullptr);
    struct tm *t = localtime(&currtime);
    char buffer[128];
    snprintf(buffer, sizeof(buffer), "%d-%d-%d %d:%d:%d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday,
             t->tm_hour, t->tm_min, t->tm_sec);
    return buffer;
}

void logMessage(int level, const char *format, ...)
{
    char leftbuffer[1024];
    std::string level_string = getlevel_string(level);
    std::string time = gettime_string();
    snprintf(leftbuffer, sizeof(leftbuffer), "[%s] [%s] [%d] ", level_string.c_str(), time.c_str(), getpid());

    char rightbuffer[1024];
    va_list p;
    va_start(p, format);
    vsnprintf(rightbuffer,sizeof(rightbuffer),format,p);
    va_end(p);

    //直接打印
    printf("%s%s\n",leftbuffer,rightbuffer);

    //写到文件中
    // FILE* pf = fopen(filename.c_str(),"a");
    // if(pf == nullptr) return;
    // fprintf(pf,"%s%s\n",leftbuffer,rightbuffer);
    // fflush(pf);
    // fclose(pf);
}
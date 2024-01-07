#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>

class Util
{
public:
    static bool SetNonBlock(int &fd)
    {
        int f1 = fcntl(fd, F_GETFL);
        if (f1 < 0)
            return false;
        fcntl(fd, F_SETFL, f1 | O_NONBLOCK);
        return true;
    }

    static bool StringSplit(const std::string &str, const std::string &sep, std::vector<std::string> *res)
    {
        int start = 0;
        while (start < str.size())
        {
            auto pos = str.find(sep, start);
            if (pos == std::string::npos)
                break;
            std::string sub = str.substr(start, pos - start);
            res->push_back(sub);
            start = pos + sep.size();
        }
        if (start < str.size())
            res->push_back(str.substr(start));

        return true;
    }

    static int toInt(const std::string &str)
    {
        return atoi(str.c_str());
    }
};
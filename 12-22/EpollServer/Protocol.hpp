#pragma once

#include <iostream>
#include <vector>
#include <jsoncpp/json/json.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "Util.hpp"

namespace Protocol
{

#define SEP " "
#define HEADER "\r\n"
#define HEADER_LEN strlen(HEADER)

    // #define MYSELF

    class Request
    {
    public:
        Request() {}
        Request(int x, int y, char op) : _x(x), _y(y), _op(op)
        {
        }

        // 序列化
        bool Serialization(std::string *outStr)
        {
            outStr->clear();
#ifdef MYSELF
            std::string x_str = std::to_string(_x);
            std::string y_str = std::to_string(_y);
            *outStr = x_str + SEP + _op + SEP + y_str;

#else
            Json::Value root;
            root["x"] = _x;
            root["op"] = _op;
            root["y"] = _y;

            Json::FastWriter writer;
            *outStr = writer.write(root);

#endif
            return true;
        }

        // 反序列化
        bool Deserialization(const std::string &inStr)
        {
#ifdef MYSELF
            std::vector<std::string> result;
            utility::StringSplit(inStr, SEP, &result);

            if (result.size() != 3)
                return false;
            if (result[1].size() != 1)
                return false;

            _x = utility::toInt(result[0]);
            _y = utility::toInt(result[2]);
            _op = result[1][0];

#else
            Json::Value root;
            Json::Reader reader;
            reader.parse(inStr, root);

            _x = root["x"].asInt();
            _op = root["op"].asInt();
            _y = root["y"].asInt();

#endif
            return true;
        }

        ~Request() {}

    public:
        int _x;
        int _y;
        char _op;
    };

    std::string AddHeader(const std::string &str)
    {
        std::string res = std::to_string(str.size());
        res += HEADER + str + HEADER;

        return res;
    }

    std::string RemoveHeader(const std::string &str, int len)
    {
        return str.substr(str.size() - HEADER_LEN - len, len);
    }

    int ParsePackage(std::string &str, std::string *package)
    {
        auto pos = str.find(HEADER, 0);
        if (pos == std::string::npos)
            return 0;
        std::string lenstr = str.substr(0, pos);
        int len = Util::toInt(lenstr);
        int sum_len = lenstr.size() + HEADER_LEN + len + HEADER_LEN;
        if (sum_len > str.size())
            return 0;
        *package = str.substr(0, sum_len);
        str.erase(0, sum_len);
        return len;
    }

    class Response
    {
    public:
        Response() {}
        Response(int result, int code) : _result(result), _code(code)
        {
        }
        // 序列化
        bool Serialization(std::string *outStr)
        {
            outStr->clear();
#ifdef MYSELF
            std::string res_str = std::to_string(_result);
            std::string code_str = std::to_string(_code);

            *outStr = res_str + SEP + code_str;

#else
            Json::Value root;
            root["result"] = _result;
            root["code"] = _code;

            Json::FastWriter writer;
            *outStr = writer.write(root);

#endif
            return true;
        }

        // 反序列化
        bool Deserialization(const std::string &inStr)
        {
#ifdef MYSELF
            std::vector<std::string> result;
            utility::StringSplit(inStr, SEP, &result);

            if (result.size() != 2)
                return false;

            _result = utility::toInt(result[0]);
            _code = utility::toInt(result[1]);

#else
            Json::Value root;
            Json::Reader reader;
            reader.parse(inStr, root);

            _result = root["result"].asInt();
            _code = root["code"].asInt();

#endif
            return true;
        }

        ~Response()
        {
        }

    public:
        int _result;
        int _code;
    };
}
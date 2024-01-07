#include <memory>
#include "EpollServer.hpp"

Response calculate(const Request &req)
{
    // logMessage(Debug,"%d%c%d",req._x,req._op,req._y);
    // 走到这里，一定保证req是有具体数据的！
    // _result(result), _code(code)
    Response resp(0, 0);
    switch (req._op)
    {
    case '+':
        resp._result = req._x + req._y;
        break;
    case '-':
        resp._result = req._x - req._y;
        break;
    case '*':
        resp._result = req._x * req._y;
        break;
    case '/':
        if (req._y == 0)
            resp._code = 1;
        else
            resp._result = req._x / req._y;
        break;
    case '%':
        if (req._y == 0)
            resp._code = 2;
        else
            resp._result = req._x % req._y;
        break;
    default:
        resp._code = 3;
        break;
    }

    // logMessage(Debug,"%d %d",resp._result,resp._code);
    return resp;
}

// void Process(Connection *con, Request req)
// {
//     Response res = calculate(req);
//     std::string str;
//     res.Serialization(&str);
//     str = AddHeader(str);
//     con->outbuffer_ += str;

//     con->Ep->EnableReadWrite(con, true, true);
// }

int main()
{
    std::unique_ptr<EpollServer> svr(new EpollServer(calculate));
    svr->InitServer();
    svr->Dispatcher();
    return 0;
}
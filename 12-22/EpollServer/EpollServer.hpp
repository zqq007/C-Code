#pragma once

#include <iostream>
#include <string>
#include <assert.h>
#include <functional>
#include <unordered_map>
#include "Sock.hpp"
#include "log.hpp"
#include "Epoller.hpp"
#include "Util.hpp"
#include "Protocol.hpp"

using namespace Protocol;

class Connection;
class EpollServer;

// using func_t = std::function<std::string(std::string)>;
// using func_t = std::function<void(Connection *, Request)>;
using func_t = std::function<Response(const Request &)>;
using callback_t = std::function<void(Connection *)>;

const static uint16_t defaultport = 8888;
const static int buffer_size = 1024;
const static std::string defaultip = "127.0.0.1";

class Connection
{
public:
    Connection(const int &fd, const std::string &clientip, const uint16_t &clientport)
        : fd_(fd), clientip_(clientip), clientport_(clientport)
    {
    }

    void Register(callback_t recver, callback_t sender, callback_t excepter)
    {
        recver_ = recver;
        sender_ = sender;
        excepter_ = excepter;
    }

    ~Connection() {}

public:
    int fd_;
    std::string inbuffer_;
    std::string outbuffer_;

    // client info
    std::string clientip_;
    uint16_t clientport_;

    callback_t recver_;
    callback_t sender_;
    callback_t excepter_;

    uint32_t event_;

    EpollServer *Ep;
};

class EpollServer
{
    const static int gnum = 64;

public:
    EpollServer(func_t func, uint16_t port = defaultport) : func_(func), port_(port) {}

    void InitServer()
    {
        listensock_.Socket();
        listensock_.Bind(port_);
        listensock_.Listen();
        epoller_.Create();

        // 先将listen套接字保存到epoll模型中
        AddConnection(listensock_.getsock(), EPOLLIN | EPOLLET);
    }

    void AddConnection(int fd, uint32_t event, std::string clientip = defaultip, uint16_t clientport = defaultport)
    {
        if (event & EPOLLET)
            Util::SetNonBlock(fd);
        Connection *con = new Connection(fd, clientip, clientport);
        if (fd == listensock_.getsock())
            con->Register(std::bind(&EpollServer::Accepter, this, std::placeholders::_1), nullptr, nullptr);
        else
            con->Register(std::bind(&EpollServer::Recver, this, std::placeholders::_1),
                          std::bind(&EpollServer::Sender, this, std::placeholders::_1),
                          std::bind(&EpollServer::Excepter, this, std::placeholders::_1));
        con->event_ = event | EPOLLET;
        con->Ep = this;
        connects_.insert(std::pair<int, Connection *>(fd, con));

        bool n = epoller_.AddModEvent(fd, event, EPOLL_CTL_ADD);
        assert(n);
        (void)n;

        logMessage(Debug, "AddConnection success,client info:[%s|%d]", clientip.c_str(), clientport);
    }

    void Dispatcher()
    {
        int timeout = -1;
        while (true)
        {
            /* code */
            LoopOncce(timeout);
            // sleep(1);
        }
    }

    void LoopOncce(int timeout)
    {
        int res = epoller_.Wait(revs_, gnum, timeout);

        for (int i = 0; i < res; ++i)
        {
            int fd = revs_[i].data.fd;
            uint32_t event = revs_[i].events;

            if ((event & EPOLLERR) || (event & EPOLLHUP))
                event |= (EPOLLIN | EPOLLOUT);

            if ((event & EPOLLIN) && CheckExists(fd))
                connects_[fd]->recver_(connects_[fd]);
            if ((event & EPOLLOUT) && CheckExists(fd))
                connects_[fd]->sender_(connects_[fd]);
        }
    }

    bool CheckExists(int fd)
    {
        return connects_.find(fd) != connects_.end();
    }

    void Accepter(Connection *con)
    {
        do
        {
            std::string clientip;
            uint16_t clientport;

            int err = 0;
            int sock = listensock_.Accept(&clientip, &clientport, &err);
            if (sock > 0)
            {
                logMessage(Debug, "[%s|%d]已连上服务器了", clientip.c_str(), clientport);
                AddConnection(sock, EPOLLIN | EPOLLET, clientip, clientport);
                // break;
            }
            else
            {
                if (err == EAGAIN || err == EWOULDBLOCK)
                    break;
                else if (err == EINTR)
                    continue;
                else
                {
                    logMessage(Warning, "errstring : %s, errcode: %d", strerror(err), err);
                    continue;
                }
            }

        } while (con->event_ & EPOLLET);
    }

    void HanderResquest(Connection *con)
    {
        bool quit = false;
        while (!quit)
        {
            std::string str;
            int x = ParsePackage(con->inbuffer_, &str);
            if (x > 0)
            {
                str = RemoveHeader(str, x);
                Request req;
                req.Deserialization(str);

                Response res = func_(req);
                std::string send_str;
                res.Serialization(&send_str);

                // 忘了添加报头
                send_str = AddHeader(send_str);

                con->outbuffer_ += send_str;
            }
            else
                quit = true;
        }
    }

    void Recver(Connection *con)
    {
        bool safe = true;
        do
        {
            /* code */
            char buffer[buffer_size];
            ssize_t n = recv(con->fd_, buffer, sizeof(buffer) - 1, 0);
            if (n > 0)
            {
                buffer[n] = 0;
                con->inbuffer_ += buffer;
            }
            else if (n == 0)
            {
                con->excepter_(con);
                safe = false;
                break;
            }
            else
            {
                if (errno == EAGAIN || errno == EWOULDBLOCK)
                    break;
                else if (errno == EINTR)
                    continue;
                else
                {
                    con->excepter_(con);
                    safe = false;
                    break;
                }
            }
        } while (con->event_ & EPOLLET);

        if (!safe)
            return;
        HanderResquest(con);
        if (!con->outbuffer_.empty())
            con->sender_(con);
    }

    void Sender(Connection *con)
    {
        bool safe = true;
        do
        {
            /* code */
            ssize_t n = send(con->fd_, con->outbuffer_.c_str(), con->outbuffer_.size(), 0);
            if (n > 0)
            {
                con->outbuffer_.erase(0, n);
                if (con->outbuffer_.empty())
                {
                    break;
                }
            }
            else
            {
                if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                    break;
                else if (errno == EINTR)
                    continue;
                else
                {
                    safe = false;
                    con->excepter_(con);
                    break;
                }
            }
        } while (con->event_ & EPOLLET);
        if (!safe)
            return;
        if (!con->outbuffer_.empty())
            EnableReadWrite(con, true, true);
        else
            EnableReadWrite(con, true, false);
    }

    bool EnableReadWrite(Connection *con, bool read_event, bool write_event)
    {
        con->event_ = ((read_event ? EPOLLIN : 0) | (write_event ? EPOLLOUT : 0) | EPOLLET);
        return epoller_.AddModEvent(con->fd_, con->event_, EPOLL_CTL_MOD);
    }

    void Excepter(Connection *con)
    {
        // 1、把epoller中fd移除
        epoller_.DelEvent(con->fd_);

        // 2、从unordered_map中删除kv关系
        connects_.erase(con->fd_);

        // 3、关闭文件描述符
        close(con->fd_);

        // 4、释放con对象
        delete con;

        logMessage(Warning, "Except...");
    }

    ~EpollServer()
    {
    }

private:
    uint16_t port_;
    Sock listensock_;
    Epoller epoller_;
    struct epoll_event revs_[gnum];
    func_t func_;
    std::unordered_map<int, Connection *> connects_;
};

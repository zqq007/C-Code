#ifndef __CONN_HPP__
#define __CONN_HPP__

#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <memory>
#include <cassert>
#include <unistd.h>
#include <sys/stat.h>

#define PATHNAME "."
#define PROJ_ID 0x6666

#define SERVER 1
#define CLIENT 0

const int gsize = 4096;

key_t getKey()
{
    key_t k = ftok(PATHNAME, PROJ_ID);
    if (k == -1)
    {
        perror("ftok fail");
        exit(-1);
    }
    return k;
}

/*十六进程转换*/
std::string toHex(int k)
{
    char buf[64];
    snprintf(buf, sizeof(buf), "0x%x", k);
    return buf;
}

/*Helper：帮忙创建共享内存，如果是服务端就创建，如果是客户端就获取共享内存id*/
static int createShmHelper(key_t key, int size, int flags)
{
    int shmid = shmget(key, size, flags);
    if (shmid == -1)
    {
        perror("shmget fail");
        exit(-1);
    }
    return shmid;
}

/*创建共享内存*/
int createShm(key_t key, int size = gsize)
{
    umask(0);
    return createShmHelper(key, size, IPC_CREAT | IPC_EXCL | 0666);
}

/*获取共享内存id*/
int getShm(key_t key, int size = gsize)
{
    return createShmHelper(key, size, IPC_CREAT);
}

/*删除共享内存*/
void delShm(int id)
{
    int n = shmctl(id, IPC_RMID, nullptr);
    assert(n != -1);
    (void)n;
}

/*连接*/
char *attchShm(int shmid)
{
    char *start = (char *)shmat(shmid, nullptr, 0);
    if (start == (char *)-1)
    {
        perror("shmat fail");
        exit(-1);
    }

    return start;
}

/*断开连接*/
void detachShm(char *start)
{
    int val = shmdt(start);
    assert(val != -1);
    (void)val;
}

class Init
{
public:
    Init(int type) : worker_(type)
    {
        int key = getKey();
        if (worker_ == SERVER)
            shmid_ = createShm(key);
        else
            shmid_ = getShm(key);

        start_ = attchShm(shmid_);
    }

    char *getStart() { return start_; }

    ~Init()
    {
        detachShm(start_);
        if (worker_ == SERVER)
            delShm(shmid_);
    }

private:
    int worker_;
    char *start_;
    int shmid_;
};

#endif
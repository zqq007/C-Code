#include "comm.hpp"

int main()
{
    // key_t k = getKey();
    // std::cout << "client:" << toHex(k) << std::endl;

    // int shmid = getShm(k);
    // std::cout << "client_shmid:" << toHex(shmid) << std::endl;

    // // 把自己和共享内存关联起来
    // char *start = attchShm(shmid);

    // sleep(2);

    // // 去关联
    // detachShm(start);

    // sleep(10);

    // std::shared_ptr<Init> init(new Init(CLIENT));
    // char *start = init->getStart();

    Init init(CLIENT);
    char *start = init.getStart();

    char c = 'A';
    int cnt = 0;
    while (cnt < 26)
    {
        start[c - 'A'] = c;
        c++;
        start[c - 'A'] = '\0';
        cnt++;
        sleep(1);
    }

    return 0;
}
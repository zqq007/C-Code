#include "comm.hpp"

int main()
{
    // key_t k = getKey();
    // std::cout << "server:" << toHex(k) << std::endl;

    // int shmid = createShm(k);
    // std::cout << "server_shmid:" << toHex(shmid) << std::endl;

    // // struct shmid_ds ds;
    // // int val = shmctl(n, IPC_STAT, &ds);
    // // if (val != -1)
    // // {
    // //     std::cout << "shmid:" << toHex(ds.shm_perm.__key) << std::endl;
    // //     std::cout << "create pid:" << ds.shm_cpid << " " << getpid() << std::endl;
    // // }
    // sleep(3);

    // // 把自己和共享内存关联起来
    // char *start = attchShm(shmid);

    // sleep(15);

    // // 去关联
    // detachShm(start);

    // sleep(5);

    // delShm(shmid);

    // std::shared_ptr<Init> init(new Init(SERVER));
    // char *start = init->getStart();

    Init init(SERVER);
    char *start = init.getStart();

    int cnt = 0;
    while (cnt <= 50)
    {
        std::cout << "client->server: " << start << std::endl;
        sleep(1);
        cnt++;
    }
    return 0;
}
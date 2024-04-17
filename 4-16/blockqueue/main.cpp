#include "blockqueue.hpp"

void *consumer(void *args)
{
    blockqueue<int> *bq = static_cast<blockqueue<int> *>(args);
    while (true)
    {
        int data = 0;
        bq->pop(&data);

        std::cout << "get data:" << data << std::endl;
        sleep(1);
    }
}

void *producer(void *args)
{
    blockqueue<int> *bq = static_cast<blockqueue<int> *>(args);

    while (true)
    {
        int data = rand() % 100;
        bq->push(data);

        std::cout << "push data:" << data << std::endl;
        sleep(1);
    }
}

int main()
{
    srand(time(nullptr));
    pthread_t csr, pdr;
    // std::shared_ptr<blockqueue<int>> bq(new blockqueue<int>());
    blockqueue<int> *bq = new blockqueue<int>();

    // 创建线程
    pthread_create(&csr, nullptr, consumer, bq);
    pthread_create(&pdr, nullptr, producer, bq);

    // 释放线程
    pthread_join(csr, nullptr);
    pthread_join(pdr, nullptr);

    delete[] bq;
    return 0;
}
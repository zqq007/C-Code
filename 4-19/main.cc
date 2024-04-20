#include "RingQueue.hpp"

void *consumerRoutine(void *args)
{
    RingQueue<int> *rq = static_cast<RingQueue<int> *>(args);

    while (true)
    {
        int data = 0;
        rq->pop(&data);

        std::cout << "get data: " << data << std::endl;

        // sleep(1);
    }
}

void *producerRoutine(void *args)
{
    RingQueue<int> *rq = static_cast<RingQueue<int> *>(args);

    while (true)
    {
        int data = rand() % 1000;
        rq->push(data);

        std::cout << "push data: " << data << std::endl;

        // sleep(1);
        usleep(5000);
    }
}

int main()
{
    srand(time(nullptr));
    RingQueue<int> *rq = new RingQueue<int>();

    // 线程创建 - 单生产单消费
    // pthread_t c, p;
    // pthread_create(&c, nullptr, consumerRoutine, rq);
    // pthread_create(&p, nullptr, producerRoutine, rq);

    // pthread_join(c, nullptr);
    // pthread_join(p, nullptr);

    // 多生产多消费版本
    pthread_t c[3], p[2];
    for (int i = 0; i < 3; ++i)
        pthread_create(c + i, nullptr, consumerRoutine, rq);

    for (int i = 0; i < 2; ++i)
        pthread_create(p + i, nullptr, producerRoutine, rq);

    for (int i = 0; i < 3; ++i)
        pthread_join(*(c + i), nullptr);
    for (int i = 0; i < 2; ++i)
        pthread_join(*(p + i), nullptr);

    delete[] rq;
    return 0;
}
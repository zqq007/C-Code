#include <iostream>
#include <unistd.h>

// 僵尸进程
//  int main()
//  {
//      pid_t id = fork();
//      if (id < 0)
//      {
//          perror("fork fail");
//          exit(-1);
//      }
//      else if (id == 0) // child process
//      {
//          std::cout << "I'm child process" << std::endl;
//          sleep(30);
//          exit(EXIT_SUCCESS);
//      }
//      else // parent process
//      {
//          std::cout << "I'm parent process" << std::endl;
//          sleep(5);
//      }
//      return 0;
//  }

// 孤儿进程
int main()
{
    pid_t id = fork();
    if (id < 0)
    {
        perror("fork fail");
        exit(-1);
    }
    else if (id == 0) // child process
    {
        std::cout << "I'm child process,id : " << getpid() << std::endl;
        sleep(5);
    }
    else
    {
        std::cout << "I'm parent process,id : " << getpid() << std::endl;
        sleep(1);
        exit(0);
    }
    return 0;
}
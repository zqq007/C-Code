#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <cstring>
#include <cassert>

#define PARSE " "

/*This function is used to execute command*/
bool execute()
{
    if (execlp("ls", "", nullptr) == -1)
    {
        perror("ls fail");
        return false;
    }
    return true;
}

int main()
{
    // if (execlp("ls", "", nullptr) == -1)
    // {
    //     perror("execlp fail");
    //     exit(-1);
    // }

    execute();
    return 0;
}
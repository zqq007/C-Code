#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
    int outfd = open("source_backup.txt", O_WRONLY | O_CREAT, 0644);
    if (outfd == -1)
    {
        perror("open fail");
        exit(-1);
    }

    // mkfifo("tp", 0644);
    int infd = open("tp", O_RDONLY);
    if (infd == -1)
    {
        perror("open fail");
        exit(-1);
    }

    int n = 0;
    char buf[1024] = {0};
    while ((n = read(infd, buf, 1024)) > 0)
    {
        write(outfd, buf, n);
    }
    close(infd);
    close(outfd);
    return 0;
}
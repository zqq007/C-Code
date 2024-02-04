#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// int main()
// {
// FILE *fp = fopen("./file.txt", "w+");
// if (!fp)
// {
//     perror("fopen file fail");
//     exit(-1);
// }
// char msg[] = "hello\n";
// fwrite(msg, sizeof(msg), 1, fp);

// fseek(fp, 0, SEEK_SET);

// char buf[32];
// fread(buf, sizeof(msg), 1, fp);

//     // printf("%s\n", buf);

//     // fclose(fp);

//     // const char *msg = "hello linux\n";
//     // fwrite(msg, strlen(msg), 1, stdout);

//     // fprintf(stdout, "%s", msg);

//     umask(0);
//     int fd = open("file", O_WRONLY | O_CREAT, 0644);
//     if (fd < 0)
//     {
//         perror("fd open fail");
//         exit(-1);
//     }

//     const char *msg = "I'm comming in";
//     write(fd, msg, strlen(msg));

//     char buf[32];
//     read(fd, buf, strlen(msg));

//     printf("%s\n",msg);

//     close(fd);
//     return 0;
// }

// int main()
// {
//     // close(0);
//     close(2);
//     umask(0);
//     int fd = open("./file", O_RDWR | O_CREAT, 0644);
//     if (fd < 0)
//     {
//         perror("open fail");
//         exit(-1);
//     }

//     // char str[32] = "Can you see me?";
//     // write(0, str, strlen(str));

//     printf("fd:%d\n", fd);
//     return 0;
// }

// int main()
// {
//     close(1);
//     int fd = open("./file", O_CREAT | O_RDWR);
//     if (fd < 0)
//     {
//         perror("open fail");
//         exit(-1);
//     }
//     dup2(fd, 1);

//     char buf[32];
//     ssize_t n = read(0, buf, sizeof(buf));
//     if (n > 0)
//         printf("%s", buf);
//     return 0;
// }

int main()
{
    const char *msg0 = "printf\n";
    const char *msg1 = "fwrite\n";
    const char *msg2 = "write\n";

    printf("%s", msg0);
    fwrite(msg1, strlen(msg1), 1, stdout);

    write(1, msg2, strlen(msg2));
    return 0;
}
#include <stdio.h>
#include <sys/select.h>

int main()
{
    printf("%ld\n", sizeof(fd_set));
    return 0;
}
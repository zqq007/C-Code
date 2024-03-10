/*写一个程序判断该机器是大端还是小端存储*/
#include <stdio.h>
#include <string.h>

// int main()
// {
//     int i = 1;
//     char cur = (char)i;
//     if (cur == 1)
//         printf("我是小端存储\n");
//     else
//         printf("我是大端存储\n");
//     return 0;
// }

// int main()
// {

//     const char *const delim = "/;";

//     char str[] = "some/splite;string";

//     char *token, *cur = str;

//     while (token = strsep(&cur, delim))

//     {

//         printf("%s %s %s\n", token, cur, str);
//     }

//     return 0;
// }

// typedef int (*fun_t)(int, int);

// int add(int val1, int val2)
// {
//     return val1 + val2;
// }

// int main()
// {
//     fun_t func = add;
//     int res = func(2, 3);
//     printf("%d\n", res);
//     return 0;
// }

// int main()
// {
//     int a[] = {1, 2, 3, 4};
//     printf("%ld\n", sizeof(*&a));
//     return 0;
// }

int main()
{
    char str[] = "abcdef";
    // printf("%ld\n", sizeof(str));//7
    // printf("%ld\n", sizeof(str + 0));//8
    // printf("%ld\n", sizeof(*str));//1
    // printf("%ld\n", sizeof(str[1]));//1
    // printf("%ld\n", sizeof(&str));//8
    // printf("%ld\n", sizeof(&str + 1));//8
    // printf("%ld\n", sizeof(&str[0] + 1));//8

    printf("%ld\n", strlen(str));//6
    printf("%ld\n", strlen(str + 0));//6
    printf("%ld\n", strlen(*str));//6
    printf("%ld\n", strlen(str[1]));//1
    // printf("%ld\n", strlen(&str));//8
    // printf("%ld\n", strlen(&str + 1));//8
    printf("%ld\n", strlen(&str[0] + 1));//8
    return 0;
}
#include <stdio.h>
#include <string.h>

// int len(const char *str)
// {
//     if (*str == '\0')
//         return 0;
//     else
//         return 1 + len(str + 1);
// }

// int main()
// {
//     char arr[50] = {0};
//     scanf("%[^\n]s", arr);
//     int ret = len(arr);
//     printf("%d\n", ret);
//     return 0;
// }

// int main()
// {
//     char str[] = "abcdef";
//     // printf("%ld\n", sizeof(str));//7
//     // printf("%ld\n", sizeof(str + 0));//8
//     // printf("%ld\n", sizeof(*str));//1
//     // printf("%ld\n", sizeof(str[1]));//1
//     // printf("%ld\n", sizeof(&str));//8
//     // printf("%ld\n", sizeof(&str + 1));//8
//     // printf("%ld\n", sizeof(&str[0] + 1));//8

//     printf("%ld\n", strlen(str));//6
//     printf("%ld\n", strlen(str + 0));//6
//     // printf("%ld\n", strlen(*str));//6
//     printf("%ld\n", strlen(str[1]));//1
//     printf("%ld\n", strlen(&str));//8
//     printf("%ld\n", strlen(&str + 1));//8
//     printf("%ld\n", strlen(&str[0] + 1));//8
//     return 0;
// }

// int main()
// {
//     int a[3][4] = {0};
//     printf("%zd\n", sizeof(a));//48
//     printf("%zd\n", sizeof(a[0][0]));//4
//     printf("%zd\n", sizeof(a[0]));//16
//     printf("%zd\n", sizeof(a[0] + 1));//16  8
//     printf("%zd\n", sizeof(*(a[0] + 1)));//4
//     printf("%zd\n", sizeof(a + 1));//48  8
//     printf("%zd\n", sizeof(*(a + 1)));//4  16
//     printf("%zd\n", sizeof(&a[0] + 1));//16  8
//     printf("%zd\n", sizeof(*(&a[0] + 1)));//4  16
//     printf("%zd\n", sizeof(*a));//4  16
//     printf("%zd\n", sizeof(a[3]));//16
//     return 0;
// }

// int main()
// {
//     int a[5] = {1, 2, 3, 4, 5};
//     int *ptr = (int *)(&a + 1);
//     printf("%d,%d", *(a + 1), *(ptr - 1));
//     return 0;
// }

// struct Test
// {
//     int Num;
//     char *pcName;
//     short sDate;
//     char cha[2];
//     short sBa[4];
// } *p;
// 假设p 的值为0x100000。 如下表表达式的值分别为多少？
// 已知，结构体Test类型的变量大小是20个字节
// int main()
// {
//     p = (struct Test *)0x100000;
//     printf("%p\n", p + 0x1);
//     printf("%p\n", (unsigned long)p + 0x1);
//     printf("%p\n", (unsigned int *)p + 0x1);
//     return 0;
// }

struct test
{
    int val;
    struct test *next;
};

int main()
{
    return 0;
}
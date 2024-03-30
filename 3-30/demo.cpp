#include <iostream>
#include <mysql/mysql.h>

int main()
{
    std::cout << mysql_get_client_info() << std::endl;
    return 0;
}
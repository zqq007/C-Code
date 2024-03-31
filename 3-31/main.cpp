#include <iostream>
#include <string>
#include <unistd.h>
#include <mysql/mysql.h>

const std::string host = "127.0.0.1";
const std::string user = "zqq";
const std::string passwd = "zqq20030613";
const std::string db = "conn";
const unsigned int port = 3306;

int main()
{
    MYSQL *my = mysql_init(nullptr);
    if (my == nullptr)
    {
        std::cerr << "mysql_init error" << std::endl;
        return -1;
    }

    if (mysql_real_connect(my, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, nullptr, 0) == nullptr)
    {
        std::cerr << "mysqld connect error" << std::endl;
        return -2;
    }

    mysql_set_character_set(my, "utf-8");

    std::string sql = "select * from user";
    // std::cout << "MYSQL >>> ";
    int n = mysql_query(my, sql.c_str());
    if (n != 0)
    {
        std::cerr << sql << " error" << std::endl;
        return -3;
    }
    // while (true)
    // {
    //     std::cout << "MYSQL >>> ";
    //     if (!std::getline(std::cin, sql) || sql == "quit")
    //     {
    //         std::cout << "Bye" << std::endl;
    //         break;
    //     }

    //     int res = mysql_query(my, sql.c_str());
    //     if (res == 0)
    //     {
    //         std::cout << sql << " sucess:" << res << std::endl;
    //     }
    //     else
    //     {
    //         std::cerr << sql << " error:" << std::endl;
    //     }
    // }
    // std::cout << "mysqld connect success" << std::endl;

    // sleep(10);

    // 获取select查询到的结果
    MYSQL_RES *res = mysql_store_result(my);
    if (res == nullptr)
    {
        std::cerr << "store result error" << std::endl;
        return -4;
    }

    // 获取行列信息
    my_ulonglong rows = mysql_num_rows(res);
    my_ulonglong fields = mysql_num_fields(res);

    // std::cout << "行:" << rows << std::endl;
    // std::cout << "列:" << fields << std::endl;

    // 获取属性
    MYSQL_FIELD *field_array = mysql_fetch_fields(res);
    for (int i = 0; i < fields; ++i)
    {
        std::cout << field_array[i].name << "\t";
    }
    std::cout << std::endl;

    // 打印内容
    for (int i = 0; i < rows; ++i)
    {
        MYSQL_ROW row = mysql_fetch_row(res);
        for (int j = 0; j < fields; ++j)
        {
            std::cout << row[j] << "\t";
        }
        std::cout << std::endl;
    }

    mysql_close(my);
    return 0;
}
//
// Created by hongrjia on 2024/6/24.
//


#include "http_conn.h"

#include <mysql/mysql.h>
#include <fstream>
#include <string>

using namespace std;


locker m_lock;
map<string, string> users;


void http_conn::initmysql_result(Connection_pool *connPool)
{
    //从连接池获取一个连接
    MYSQL *mysql = NULL;
    connectionRAII mysqlcon(&mysql,connPool);

    //在user表中检索username passwd数据
    if(mysql_query(mysql,"SELECT username,passwd FROM user"))
    {
        LOG_ERROR("SELECT error:%s\n",mysql_error(mysql));
    }


    //从表中检索完整的结果集
    MYSQL_RES *result = mysql_store_result(mysql);

    //返回结果集中的列数
    int num_fields = mysql_num_fields(result);


    //返回所有结构字段的数组
    MYSQL_field *fields = mysql_fetch_fields(result);

    //从结构集中获取下一行，将对应的用户名和密码，存入map中
    while(MYSQL_ROW row = mysql_fetch_row(result))
    {
        string temp1(row[0]);
        string temp2(row[1]);
        users[temp1] = temp2;
    }


}
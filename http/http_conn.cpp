//
// Created by hongrjia on 2024/6/24.
//


#include "http_conn.h"

#include <mysql/mysql.h>
#include <fstream>


locker m_lock;
map<string, string> users;


void http_conn::initmysql_result(Connection_pool *connPool)
{

}
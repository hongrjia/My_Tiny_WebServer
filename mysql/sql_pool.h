//
// Created by hongrjia on 2024/6/21.
// Emil hongrjia@163.com

#ifndef MY_TINY_WEB_TEST_SQL_POOL_H
#define MY_TINY_WEB_TEST_SQL_POOL_H

#include <iostream>
#include <list>
#include <mysql/mysql.h>
#include <../lock/locker.h>
#include <string>
#include <stdlib.h>
#include "../log/log.h"

using namespace std;


using namespace std;


class Connection_pool
{
public:
    MYSQL* GetConnection(); //获取数据库连接
    bool ReleaseConnection(MYSQL *Conn); //释放连接
    int GetFreeConn();  //获取连接
    void DestroyPool(); //销毁连接

    //单例
    static Connection_pool* get_instance()
    {
        static Connection_pool instance;
        return &instance;
    }

    void init(string url,string User,string PassWord,string DataBaseName,int Port,int MaxConn,int close_log);
private:
    Connection_pool();
    ~Connection_pool();

    int m_MaxConn; //最大连接数
    int m_CurConn; //当前已使用最大连接数
    int m_FreeConn; //当前空闲连接数
    locker lock;
    list<MYSQL *> connList; //连接池
    sem reserve;

public:

    string m_url;			 //主机地址
    string m_Port;		 //数据库端口号
    string m_User;		 //登陆数据库用户名
    string m_PassWord;	 //登陆数据库密码
    string m_DatabaseName; //使用数据库名
    int m_close_log;	//日志开关

};

class connectionRAII{
public:
    connectionRAII(MYSQL **con,Connection_pool *connPool);
    ~connectionRAII();


private:
    MYSQL *conRAII;
    Connection_pool *poolRAII;
};


#endif //MY_TINY_WEB_TEST_SQL_POOL_H

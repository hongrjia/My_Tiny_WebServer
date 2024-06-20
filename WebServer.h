//
// Created by hongrjia on 2024/6/18.
//

#ifndef MY_TINY_WEB_TEST_WEBSERVER_H
#define MY_TINY_WEB_TEST_WEBSERVER_H

#include <iostream>
#include <string>


class WebServer
{
public:
    WebServer();
    ~WebServer();

    void init(int port,string user,string passwd,string databaseName,
              int log_Write,int opt_linger,int trig_mode,int sql_num,
              int thread_num,int close_log,int actor_model);


    /**
     * @brief 日志初始化
     * */
     void log_write();


private:
    //基础
    int m_port;
    char* m_root;
    int m_log_write;
    int m_close_log;
    int m_actormodel;

    int m_pipefd[2];
    int m_epollfd;
    http_conn *users;

    //数据库相关
    connection_pool *m_connPool;
    string m_user;         //登陆数据库用户名
    string m_passWord;     //登陆数据库密码
    string m_databaseName; //使用数据库名
    int m_sql_num;

    //线程池相关
    int m_thread_num;

    //epoll_evetn

    int m_listenfd;
    int m_Opt_LINGER;
    INT m_TRIGMode;
    int m_ListenTrigmode;
    int m_CONNTrigMode;

    //定时器相关

};


#endif //MY_TINY_WEB_TEST_WEBSERVER_H

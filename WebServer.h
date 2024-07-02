//
// Created by hongrjia on 2024/6/18.
//

#ifndef MY_TINY_WEB_TEST_WEBSERVER_H
#define MY_TINY_WEB_TEST_WEBSERVER_H

#include <iostream>
#include <string>
#include "./mysql/sql_pool.h"
#include "./http/http_conn.h"
#include "./threadpool/thread_pool.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include "./timer/lst_timer.h"
#include <sys/epoll.h>
#include <assert.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <time.h>


using namespace std;

const int MAX_FD = 65535; //最大文件描述符
const int MAX_EVENT_NUMBER = 10000; //最大事件数
const int  TIMESLOT = 5; //最小超时单位


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

     /**
      * @brief 数据库初始化
      * */
    void sql_pool();

    /**
     * @brief 初始化线程池
     * */
    void thread_pool();

    /**
     * @brief 触发模式
     * */
    void trig_mode();

    /**
     * @brief 监听
     * */
     void eventListen();

     /**
      * @brief 运行
      * */
      void eventLoop();

      void timer(int connfd,struct sockaddr_in client_address);
      void adjust_timer(util_time *timer);
      void deal_timer(util_time *timer,int sockfd);


      bool dealclientdata();
      bool dealwithsignal(bool &timeout,bool& stop_server);
      void dealwithread(int sockfd);
      void dealwithwrite(int sockfd);

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
    Connection_pool *m_connPool;
    string m_user;         //登陆数据库用户名
    string m_passWord;     //登陆数据库密码
    string m_databaseName; //使用数据库名
    int m_sql_num;

    //线程池相关
    int m_thread_num;
    threadpool<http_conn> *m_pool;

    //epoll_event相关
    epoll_event events[MAX_EVENT_NUMBER];

    int m_listenfd;
    int m_Opt_LINGER;
    int m_TRIGMode;
    int m_ListenTrigmode;
    int m_CONNTrigMode;

    //定时器相关
    client_data *users_timer;
    Utils utils;
};


#endif //MY_TINY_WEB_TEST_WEBSERVER_H

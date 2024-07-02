//
// Created by hongrjia on 2024/7/2.
//

#ifndef MY_TINY_WEB_TEST_LST_TIMER_H
#define MY_TINY_WEB_TEST_LST_TIMER_H

#include <unistd.h>
#include <sys/socket.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <string.h>




class util_time;

struct client_data
{
    sockaddr_in address;
    int sockfd;
    util_time *timer;
};


class util_time
{
public:
    util_time() : prev(NULL),next(NULL){}

public:
    time_t expire;

    void (*cb_func)(client_data *); //回调
    client_data *user_data;
    util_time *prev;
    util_time *next;
};

class  sort_timer_lst
{
public:
    sort_timer_lst();
    ~sort_timer_lst();

    void add_timer(util_time *timer);
    void adjust_timer(util_time *timer);
    void del_timer(util_time *timer);
    void tick();

private:
    void add_timer(util_time *timer,util_time *lst_timer);

    util_time *head;
    util_time *tail;
};


class Utils
{
public:
    Utils(){}
    ~Utils(){}

    void init(int timeout);

    //对文件描述符设置非阻塞
    int setnonblocking(int fd);

    //将内核时间表注册读事件 ET模式，选择开启EPOLLONESHOT
    void addfd(int epollfd,int fd,bool one_shot,int TRIGMode);

    //信号处理函数
    static void sig_handler(int sig);

    //设置信号函数
    void addsig(int sig,void(handler)(int),bool restart = true);

    //定时处理任务
    void timer_handler();

    void show_error(int coonfd,const char *info);

public:
    static int *u_pipefd;
    sort_timer_lst m_timer_lst;
    static int u_epollfd;
    int m_TIMEOUT;
};


void cb_func(client_data *user_data);


#endif //MY_TINY_WEB_TEST_LST_TIMER_H

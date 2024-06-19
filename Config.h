//
// Created by hongrjia on 2024/6/18.
//

#ifndef MY_TINY_SERVER_TEST_CONFIG_H
#define MY_TINY_SERVER_TEST_CONFIG_H

#include <unistd.h>
#include <cstdlib>

class Config
{
public:
    Config();
    ~Config(){}

    void parse_arg(int argc,char*argv[]);

    //端口号
    int PORT;

    //日志写入方式
    int LogWrite;

    //触发组合模式
    int TrigMode;

    //listenfd触发模式
    int ListenTrigMode;

    //connfd触发模式
    int ConnTrigMode;

    //关闭连接
    int Opt_Linger;

    //数据库连接池个数
    int sql_num;

    //线程池的线程数量
    int thread_num;

    //是否关闭日志
    int close_log;

    //并发模型选择
    int actor_model;

};


#endif //MY_TINY_SERVER_TEST_CONFIG_H

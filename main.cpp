/**
 * @author hongrjia
 * @brief My tiny web test
 * @date 2024-6-18
 * @emil hongrjia@163.coom
 * */


#include <iostream>
#include <string>
#include "Config.h"
#include <WebServer.h>


int main(int argc,char* argv[]){

    string user = "root";
    string passwd = "root";
    string databasename = "hongrjiadb";


    //命令行解析
    Config config;
    config.parse_arg(argc,argv);

    WebServer server;
    //初始化
    server.init(config.PORT,user,passwd,databasename,config.LogWrite,
                config.Opt_Linger,config.TrigMode,config.sql_num,config.thread_num,
                config.close_log,config.actor_model);


    //日志初始化
    server.log_write();


    //数据库
    server.sql_pool();

    //线程池
    server.thread_pool();


    //触发模式
    server.trig_mode();

    //监听
    server.eventListen();

    //运行
    server.eventLoop();

    return 0;
}



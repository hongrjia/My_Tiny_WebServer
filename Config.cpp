//
// Created by hongrjia on 2024/6/18.
//

#include "Config.h"


Config::Config()
{
    //初始化默认信息

    //端口号,默认9600
    PORT = 9600;

    //日志写入方式，默认同步
    LogWrite = 0;

    //触发组合模式,默认listenfd LT + connfd LT
    TrigMode = 0;

    //listenfd触发模式，默认LT
    ListenTrigMode = 0;

    //connfd触发模式，默认LT
    ConnTrigMode = 0;

    //优雅关闭连接。默认LT
    Opt_Linger = 0;

    //数据库连接数量，默认8
    sql_num = 8;

    //线程吃数量，默认8
    thread_num = 8;

    //关闭日志，默认开启
    close_log = 0;

    //并发模式=，默认是proactor
    actor_model = 0;
}

void Config::parse_arg(int argc, char **argv)
{
    int opt;
    const char* str = "p:l:m:o:s:t:c:a";
    while((opt = getopt(argc,argv,str)) != -1)
    {
        switch (opt) {
            case 'p':
            {
                PORT = atoi(optarg);
                break;
            }
            case 'l':
            {
                LogWrite = atoi(optarg);
                break;
            }
            case 'm':
            {
                TrigMode = atoi(optarg);
                break;
            }
            case 'o':
            {
                Opt_Linger = atoi(optarg);
                break;
            }
            case 's':
            {
                sql_num = atoi(optarg);
                break;
            }
            case 't':
            {
                thread_num = atoi(optarg);
                break;
            }
            case 'c':
            {
                close_log = atoi(optarg);
                break;
            }
            case 'a':
            {
                actor_model = atoi(optarg);
                break;
            }
            default:
                break;



        }
    }

}

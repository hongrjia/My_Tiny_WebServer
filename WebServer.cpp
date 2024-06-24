//
// Created by hongrjia on 2024/6/19.
//

#include "WebServer.h"

#include "./log/log.h"

WebServer::WebServer()
{

}


WebServer::~WebServer()
{

}


void WebServer::init(int port, string user, string passwd, string databaseName, int log_Write, int opt_linger, int trig_mode,
                     int sql_num, int thread_num, int close_log, int actor_model)
{
    m_port  = port;
    m_user = user;
    m_passWord = passwd;
    m_databaseName = databaseName;
    m_sql_num =sql_num;
    m_thread_num = thread_num;
    m_log_write = log_Write;
    m_Opt_LINGER = opt_linger;
    m_TRIGMode = trig_mode;
    m_close_log = close_log;
    m_actormodel = actor_model;

}

void WebServer::log_write()
{
    if(0 == m_close_log)
    {
        //初始化日志
        if(1 == m_log_write)
            //异步
            Log::get_instance()->init("./ServerLog",m_close_log,2000,800000,800);
        else
            Log::get_instance()->init("./ServerLog",m_close_log,2000,800000,0);
    }
}

void WebServer::sql_pool()
{
    //初始化数据库连接池
    m_connPool = Connection_pool::get_instance();
    m_connPool->init("localhost",m_user,m_passWord,m_databaseName,3306,m_sql_num,m_close_log);

    users->initmysql_result(m_connPool);
}




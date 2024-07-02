//
// Created by hongrjia on 2024/6/24.
//


#include "sql_pool.h"
#include <string>
using namespace std;


Connection_pool::Connection_pool()
{
    m_CurConn =0;
    m_FreeConn =0;
}

Connection_pool::~Connection_pool()
{
    DestroyPool();
}

void Connection_pool::init(string url, string User, string PassWord, string DataBaseName, int Port, int MaxConn, int close_log)
{
    //初始化
    m_url =url;
    m_Port = Port;
    m_User = User;
    m_PassWord = PassWord;
    m_DatabaseName = DataBaseName;
    m_close_log = close_log;

    for(int i=0;i<MaxConn;++i)
    {
        MYSQL* con = NULL;
        con = mysql_init(con);

        if(con == NULL)
        {
            LOG_ERROR("MYSQL INIT ERROR");
            exit(-1);
        }

        con = mysql_real_connect(con,url.c_str(),User.c_str(),PassWord.c_str(),DataBaseName.c_str(),Port,NULL,0);

        if(con == NULL)
        {
            LOG_ERROR("MySql Error");
            exit(-1);
        }

        connList.push_back(con);
        ++m_FreeConn;

    }

    reserve = sem(m_FreeConn);
    m_MaxConn = m_FreeConn;

}

//当有请求时，从数据库连接池中返回一个可用连接，更新使用和空闲连接数
MYSQL *Connection_pool::GetConnection()
{
    MYSQL* conn;

    if(0 == connList.size())
        return NULL;

    reserve.wait();

    lock.lock();
    conn = connList.front();
    connList.pop_front();

    --m_FreeConn;
    ++m_CurConn;
    lock.unlock();

    return conn;
}

//释放当前使用的连接
bool Connection_pool::ReleaseConnection(MYSQL *Conn)
{
    if(NULL == Conn)
        return false;

    lock.lock();
    connList.push_back(Conn);
    ++m_FreeConn;
    --m_CurConn;

    lock.lock();

    reserve.post();
    return true;
}

//销毁数据库连接池
void Connection_pool::DestroyPool()
{
    lock.lock();
    if(connList.size() > 0)
    {
        for(auto it = connList.begin();it != connList.end();++it)
        {
            MYSQL *con = *it;
            mysql_close(con);
        }

        m_CurConn = 0;
        m_FreeConn = 0;
        connList.clear();
    }
    lock.unlock();
}

//当前空闲的连接数
int Connection_pool::GetFreeConn()
{
    return this->m_FreeConn;
}


connectionRAII::connectionRAII(MYSQL **con, Connection_pool *connPool)
{
    *con = connPool->GetConnection();

    conRAII = *con;
    poolRAII = connPool;
}

connectionRAII::~connectionRAII()
{
    poolRAII->ReleaseConnection(conRAII);
}

































//
// Created by hongrjia on 2024/6/24.
//

#ifndef MY_TINY_WEB_TEST_HTTP_CONN_H
#define MY_TINY_WEB_TEST_HTTP_CONN_H

#include <iostream>
#include "../mysql/sql_pool.h"
#include "../lock/locker.h"
#include <string>
#include <netinet/in.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <map>

using namespace std;


class http_conn
{
public:
    static const int FILENAME_LEN = 200;
    static const int READ_BUFFER_SIZE = 2048;
    static const int WRITE_BUFFER_SZIE = 1024;

    enum METHOD
    {
        GET = 0,
        POST,
        HEAD,
        PUT,
        DELETE,
        TRACE,
        OPTIONS,
        CONNECT,
        PATH
    };

    enum CHECK_STATE
    {
        CHECK_STATE_REQUESTLINE = 0,
        CHECK_STATE_HEADER,
        CHECK_STATE_CONTENT
    };

    enum HTTP_CODE
    {
        NO_REQUEST,
        GET_REQUEST,
        BAD_REQUEST,
        NO_RESURCE,
        FORBIDDEN_REQUEST,
        FILE_REQUEST,
        INTERNAL_ERROR,
        CLOSED_CONNECTION
    };

    enum LINE_SRARUS
    {
        LINE_OK = 0,
        LINE_BAD,
        LINE_OPEN
    };

public:
    http_conn(){}
    ~http_conn(){}

    void init(int sockfd,const sockaddr_in &addr,char *,int ,int ,string user,string passwd,string sqlname);
    void close_conn(bool real_close = true);
    void process();
    bool read_once();
    bool write();

    sockaddr_in* get_address()
    {
        return &m_address;
    }


    void initmysql_result(Connection_pool *connPool);

    int timer_flag;
    int improv;

private:
    void init();
    HTTP_CODE process_read();
    bool process_write(HTTP_CODE RET);
    HTTP_CODE parse_request_line(char *text);
    HTTP_CODE parse_headers(char *text);
    HTTP_CODE parse_content(char *text);
    HTTP_CODE do_request();
    char *get_line(){ return m_read_buf + m_start_line;}
    LINE_SRARUS parse_line();
    void unmap();
    bool add_response(const char *fromat, ...);
    bool add_content(const char *content);
    bool add_status_line(int status, const char *title);
    bool add_headers(int content_length);
    bool add_content_type();
    bool add_content_length(int content_length);
    bool add_linger();
    bool add_blank_line();


public:
    static int m_epollfd;
    static int m_user_count;
    MYSQL *mysql;
    int m_state; //0-读  1-写

private:
    int m_sockfd;
    sockaddr_in m_address;
    char m_read_buf[READ_BUFFER_SIZE];
    long m_read_idx;
    long m_check_idx;
    int m_start_line;
    char m_write_buf[WRITE_BUFFER_SZIE];
    int m_write_line;
    CHECK_STATE m_check_state;
    METHOD m_method;
    char m_real_file[FILENAME_LEN];
    char *m_url;
    char *m_version;
    char *m_host;
    char *m_content_length;
    char *m_linger;
    char *m_file_address;
    struct stat m_file_stat;
    struct iovec m_iv[2];
    int m_iv_count;
    int cgi; //是否启用 POST
    char *m_string; //存储请求头数据
    int bytes_to_send;
    int bytes_have_send;
    char *doc_root;


    map<string,string> m_users;
    int m_TRIGMode;
    int m_close_log;

    char sql_user[100];
    char sql_passwd[100];
    char sql_name[100];

};



#endif //MY_TINY_WEB_TEST_HTTP_CONN_H

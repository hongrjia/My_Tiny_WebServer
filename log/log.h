//
// Created by hongrjia on 2024/6/19.
//  emil hongrjia@163.com
//

#ifndef MY_TINY_WEB_TEST_LOG_H
#define MY_TINY_WEB_TEST_LOG_H

#include <iostream>


class Log
{
public:
    static Log* get_instace()
    {
        static Log instance;
        return &instande;
    }


    bool init(const char *file_name,int close_log,int log_buf_size = 8192,int split_lines = 5000000,int max_queue_size = 0);


private:
    Log();
    //虚析构，针对继承后数据释放
    virtual ~Log();




    int m_close_log;


};






#endif //MY_TINY_WEB_TEST_LOG_H

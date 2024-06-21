//
// Created by hongrjia on 2024/6/21.
// Emil hongrjia@163.com

#ifndef MY_TINY_WEB_TEST_SQL_POOL_H
#define MY_TINY_WEB_TEST_SQL_POOL_H

#include <iostream>


using namespace std;


class Connection_pool
{
public:


    //单例
    static Connection_pool* get_instance()
    {
        static Connection_pool instance;
        return &instance;
    }


private:
    Connection_pool();
    ~Connection_pool();

    int


};


#endif //MY_TINY_WEB_TEST_SQL_POOL_H

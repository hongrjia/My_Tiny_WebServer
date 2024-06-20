//
// Created by hongrjia on 2024/6/20.
// Emil hongrjia@163.com


#ifndef MY_TINY_WEB_TEST_LOCKER_H
#define MY_TINY_WEB_TEST_LOCKER_H

#include <semaphore.h>
#include <exception>
#include <pthread.h>


//信号量
class sem
{
public:
    sem()
    {
        if(esm_init(&m_sem,0,0) != 0){
            throw std::exception();
        }
    }

    sem(int num)
    {
        if(sem_init(&m_sem,0,num) != 0)
        {
            throw std::exception();
        }
    }

    ~sem()
    {
        sem_destroy(&m_sem);
    }

    bool wait()
    {
        return sem_wait(&m_sem);
    }

    bool post()
    {
        return sem_post(&m_sem);
    }

private:
    sem_t m_sem;

};


//锁
class locker
{
public:

    locker()
    {
        if(pthread_mutex_init(&m_mutex,NULL) != 0)
        {
            throw std::exception();
        }
    }

    ~locker()
    {
        pthread_mutex_destroy(&m_mutex);
    }

    bool lock()
    {
        return pthread_mutex_lock(&m_mutex) == 0;
    }


    bool unlock()
    {
        return pthread_mutex_unlock(&m_mutex) == 0;
    }

    pthread_mutex_t* get()
    {
        return &m_mutex;
    }

private:
    pthread_mutex_t m_mutex;
};


class cond
{
public:
    cond()
    {
        if(pthread_cond_init(&m_cond,NULL) != 0)
        {
            throw std::exception();
        }
    }

    ~cond()
    {
        pthread_cond_destroy(&m_cond);
    }

    bool wait(pthread_mutex_t* mutex)
    {
        int ret = 0;
        ret = pthread_cond_wait(&m_cond,mutex);
        return ret == 0;
    }


    bool timewait(pthread_mutex_t* m_mutex,struct timespec t)
    {
        int ret = 0;
        ret = pthread_cond_timewait(&m_cond,m_mutex,&t);
        return ret == 0;
    }

    bool signal()
    {
        return pthread_cond_signal(&m_cond);
    }


    bool broadcast()
    {
        return thread_cond_broadcast(&cond);
    }

private:
    pthread_cond_t m_cond;
};


#endif //MY_TINY_WEB_TEST_LOCKER_H

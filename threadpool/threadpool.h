
#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <list>
#include <thread>
#include <functional>
#include <memory>
#include <atomic>

#include "syncqueue.h"

const int MAX_TASK_COUNT = 100;

class ThreadPool
{
private:
    using Task = std::function<void()>;
    std::list<std::shared_ptr<std::thread>> m_threadGroup;
    SyncQueue<Task> m_queue;
    std::atomic_bool m_running;
    std::once_flag m_flag;

    void runInThread()
    {
        while (m_running)
        {
            std::list<Task> list;
            m_queue.take(list);

            for (auto &task : list)
            {
                if (!m_running)
                    return;

                task();
            }
        }
    }

    void stopThreadGroup()
    {
        m_queue.stop();
        m_running = false;

        for (auto thread : m_threadGroup)
        {
            if (thread)
                thread->join();
        }

        m_threadGroup.clear();
    }

public:
    ThreadPool(int numThreads = std::thread::hardware_concurrency()) : m_queue(MAX_TASK_COUNT)
    {
        start(numThreads);
    }

    ~ThreadPool() { stop(); }

    void start(int numThreads)
    {
        m_running = true;
        for (int i = 0; i < numThreads; ++i)
        {
            m_threadGroup.push_back(std::make_shared<std::thread>(&ThreadPool::runInThread, this));
        }
    }

    void stop()
    {
        std::call_once(m_flag, [this]
                       { stopThreadGroup(); });
    }

    void addTask(Task &&task)
    {
        m_queue.put(std::forward<Task>(task));
    }

    void addTask(const Task &task)
    {
        m_queue.put(task);
    }
};

#endif
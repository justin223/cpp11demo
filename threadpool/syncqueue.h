
#ifndef SYNC_QUEUE_H
#define SYNC_QUEUE_H

#include <list>
#include <mutex>
#include <thread>
#include <condition_variable>
#include <iostream>

template <typename T>
class SyncQueue
{
private:
    std::list<T> m_queue;
    std::mutex m_mutex;
    std::condition_variable m_notEmpty;
    std::condition_variable m_notFull;
    int m_maxSize;
    bool m_needStop;

    bool notFull() const
    {
        bool full = m_queue.size() >= m_maxSize;
        if (full)
            std::cout << "Buffer full" << std::endl;
        return !full;
    }

    bool notEmpty() const
    {
        bool empty = m_queue.empty();
        if (empty)
            std::cout << "Buffer empty, thread ID: " << std::this_thread::get_id() << std::endl;

        return !empty;
    }

    template <typename F>
    void add(F &&x)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_notFull.wait(lock, [this]
                       { return m_needStop || this->notFull(); });
        if (m_needStop)
            return;

        m_queue.push_back(std::forward<F>(x));
        m_notEmpty.notify_one();
    }

public:
    SyncQueue(int maxSize) : m_maxSize(maxSize), m_needStop(false) {}

    void put(const T &x)
    {
        add(x);
    }

    void put(T &&x)
    {
        add(std::forward<T>(x));
    }

    void take(std::list<T> &list)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_notEmpty.wait(lock, [this]
                        { return m_needStop || this->notEmpty(); });
        if (m_needStop)
            return;

        list = std::move(m_queue);
        m_notFull.notify_one();
    }

    void take(T &t)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_notEmpty.wait(lock, [this]
                        { return m_needStop || this->notEmpty(); });

        if (m_needStop)
            return;

        t = m_queue.front();
        m_queue.pop_front();
        m_notFull.notify_one();
    }

    void stop()
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_needStop = true;
        }

        m_notFull.notify_all();
        m_notEmpty.notify_all();
    }

    bool empty()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.empty();
    }

    bool full()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.size() == m_maxSize;
    }

    size_t size()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        return m_queue.size();
    }

    int count()
    {
        return m_queue.size();
    }
};

#endif
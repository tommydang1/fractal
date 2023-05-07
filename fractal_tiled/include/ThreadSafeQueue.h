#pragma once

template <typename T> class TSQueue {

    protected:
    
    // Underlying queue
    std::queue<T> m_queue;
  
    // mutex for thread synchronization
    std::mutex m_mutex;
  
    // Condition variable for signaling
    std::condition_variable m_cond;

    public:

    TSQueue() {}

    void  push(T item)
    {
  
        // Acquire lock.  We will wait here if mutex locked
        std::unique_lock<std::mutex> lock(m_mutex);
  
        // Add item to the non-thread safe queue
        m_queue.push(item);
  
        // Notify one waiting thread that something is  waiting
        m_cond.notify_one();
    }

    T pop()
    {
  
        // acquire the lock
        std::unique_lock<std::mutex> lock(m_mutex);
  
        // wait until queue is not empty
        m_cond.wait(lock,
                    [this]() { return !m_queue.empty(); });
  
        // retrieve item
        T item = m_queue.front();
        m_queue.pop();
  
        // return item
        return item;
    }


};


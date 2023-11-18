#include <iostream>
#include "ThreadPool.h"

std::once_flag ThreadPool::m_onceflag;
std::unique_ptr<ThreadPool> ThreadPool::m_instance;

int main()
{
    ThreadPool &Pool=ThreadPool::getinstance(4);
    for (int i = 0; i < 8; ++i) {
        Pool.enqueue([i] {
            std::cout << "Task " << i << " is running in thread " << std::this_thread::get_id() << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "Task " << i << " is done" << std::endl;
            });
    }
}


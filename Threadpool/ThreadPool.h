#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include<functional>
#include<queue>
#include<vector>
#include<memory>


class ThreadPool
{
public:
	static ThreadPool& getinstance(int N) {
		std::call_once(m_onceflag, init, N);
		return *m_instance;
	}

	template<typename F,typename... Args> 
	void enqueue(F&& f, Args&&... args) {
		std::function<void()> Task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
		{
			std::unique_lock<std::mutex> lock(mutex);
			Tasks.emplace(std::move(Task));
		}
		cv.notify_one();
	}

	~ThreadPool() {
		{
			std::unique_lock<std::mutex> lock(mutex);
			stop = true;
		}
		cv.notify_all();
		for (std::thread& thread : Threads) {
			thread.join();
		}
	}

private:
	ThreadPool(int N) :stop(false){
		for (int i = 1; i <= N; ++i) {
			Threads.emplace_back([this]
				{
					while (true) {
						std::unique_lock<std::mutex> lock(mutex);
						cv.wait(lock, [this] {return stop || !Tasks.empty(); });
						if (stop && Tasks.empty()) {
							return;
						}
						std::function<void()> task(std::move(Tasks.front()));
						Tasks.pop();
						lock.unlock();
						task();
					}
				}
			);
		}
	};

	ThreadPool(const ThreadPool&) = default;
	ThreadPool& operator=(const ThreadPool&) = default;

	static void init(int N) {
		m_instance.reset(new ThreadPool(N));
	}


	static std::once_flag m_onceflag;
	static std::unique_ptr<ThreadPool> m_instance;
	std::vector<std::thread> Threads;
	std::queue<std::function<void()>> Tasks;
	std::mutex mutex;
	std::condition_variable cv;
	bool stop;
};

#endif
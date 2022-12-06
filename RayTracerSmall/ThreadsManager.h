#pragma once
#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <vector>
#include <queue>
#include <stdint.h>
#include <condition_variable>
#include <memory>
#include <stdexcept>
#include <future>

template<class F, class ... Args>
auto enqueue(F&& f, Args&&... args)->
	std::future<typename std::result_of<F(Args...)>::type>
{
	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::make_shared< std::packaged_task<return_type()>
	>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

	std::future<return_type> res = task->get_future();
	{
		std::unique_lock<std::mutex> lock(mutexQu)
	}
}

class ThreadsManager
{
public:
	ThreadsManager(size_t NumOfThreads);
	virtual ~ThreadsManager();

	//sync
	std::condition_variable condition;
	std::mutex mutexQueue;

	

private:
	//track of threads so we cna join
	std::vector< std::thread> workersT;

	//task queue
	std::queue< std::function<void()> > tasks;


	bool stop;
}





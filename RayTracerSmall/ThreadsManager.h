 #pragma once
#include <iostream>
#include <thread>
#include <atomic>
#include <functional>

class ThreadsManager
{
	std::atomic_bool done;
	thread_safe_queue<std::function<void()> > workQueue;

public:

private:

};





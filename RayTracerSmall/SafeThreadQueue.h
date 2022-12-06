#pragma once
#include "SafeThread.h"
#include <queue>

template<typename T>
class SafeThreadQueue
{
public:
	SafeThreadQueue() {}
	void push(T newValue)
	{
		std::lock_guard<std::mutex> lock(mutex);
		dataQueue.push(std::move(newValue));
		dataCondition.notify_one();
	}
	void waitPop(T& value)
	{
		std::unique_lock<std::mutex> lock(mutex);
		dataCondition.wait(lock, [this] {return !dataQueue.empty(); });
		value = std::move(dataQueue.front());
		dataQueue.pop();
	}

	std::shared_ptr<T> waitPop()
	{
		std::unique_lock<std::mutex> lock(mutex);
		dataCondition.wait(lock, [this] {return !dataQueue.empty()};);
		std::shared_ptr<T> res(
			std::make_shared<T>(std::move(dataQueue.front())));
		dataQueue.pop();
		return res;
	}

	std::shared_ptr<T> tryPop()
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (dataQueue.empty())
		{
			return std::shared_ptr<T>();
		}
		std::shared_ptr<T> res(
			std::make_shared<T>(std::move(dataQueue.front())));
		dataQueue.pop();
		return res;
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lock(mutex);
		return dataQueue.empty();
	}


private:
	mutable std::mutex mutex;
	std::queue<T> dataQueue;
	std::condition_variable dataCondition;

};

#pragma once
#include <exception>
#include <stack>
#include <mutex>
#include <memory>

struct EmptyStack : std::exception
{
	const char* what() const throw ();
};

template<typename T>
class SafeThread
{

public:
	SafeThread() {}
	SafeThread(const SafeThread& other)
	{
		std::lock_guard<std::mutex> lock(other.mutex);
		data = other.data;
	}
	SafeThread& operator=(const SafeThread&) = delete;

	void push(T nValue)
	{
		std::lock_guard<std::mutex> lock(mutex);
		data.push(std::move(nValue));
	}

	std::shared_ptr<T> pop()
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (data.empty()) throw EmptyStack();
		std::shared_ptr<T> const res
		(std::make_shared<T>(std::move(data.top())));
		data.pop();

		return res;

	}

	void pop(T& value)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (data.empty()) throw EmptyStack();
		value = std::move(data.top());
		data.pop();
	}

	bool empty() const
	{
		std::lock_guard<std::mutex> lock(mutex);
		
		return data.empty();
	}

private:
	std::stack<T> data;
	mutable std::mutex mutex;
};

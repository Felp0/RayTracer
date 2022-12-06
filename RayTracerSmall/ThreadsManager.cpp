#include "ThreadsManager.h"

inline ThreadsManager::ThreadsManager(size_t NumOfThreads) : stop(false)
{
	for (size_t i = 0; i < NumOfThreads; ++i)
		workersT.emplace_back([this]
			{
				//same as while(true)
				for (;;)
				{
					std::function<void()> task;
					{
						std::unique_lock<std::mutex> lock(this->mutexQueue);
						this->condition.wait(lock, [this]
							{
								return this->stop || !this->tasks.empty(); });
						if (this->stop && this->tasks.empty())
						{
							return;
						}
						task = std::move(this->tasks.front());
						this->tasks.pop();
					}
					task();
				}
			});
}


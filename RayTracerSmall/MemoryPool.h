#pragma once
#include <assert.h>

class MemoryPool
{
public:
	MemoryPool(size_t objSize, size_t objNumber) 
	{
		
	}
	~MemoryPool();

	void*					Allocate(size_t size);
	void					Free(void* p, size_t size);

private:
	MemoryPool(const MemoryPool&);
	MemoryPool& operator=(const MemoryPool&);

	char mem[4096]; //pre-allocated space in Memory
	char* pMem;//pointer to last element in memory pool

	size_t			sizeBlock;
	size_t			sizePool;


};


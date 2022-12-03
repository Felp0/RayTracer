#pragma once
#include <iostream>
struct Chunk
{
	Chunk* pNext;
};

//struct Object
//{
//	uint64_t data[2];
//
//	static Pool m_MemoryAllocator;
//
//	static void* operator new(size_t size)
//	{
//		return m_MemoryAllocator.Allocate(size);
//	}
//
//	static void operator delete(void* pMem, size_t size)
//	{
//		return m_MemoryAllocator.Deallocate(pMem, size);
//	}
//};
//
//Pool Object::m_MemoryAllocator{ 8 };

class Pool
{
public:
	Pool(size_t chunksPBlock) : m_chunksBlock(chunksPBlock) {};

	void* Allocate(size_t size);

	void Deallocate(void* pMem, size_t size);

private:
	size_t				m_chunksBlock;

	Chunk*				pAlloc = nullptr;

	Chunk* AllocateBlock(size_t Chunksize);


};


#pragma once
#include <iostream>

struct Header;

struct Tracker;

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
	Pool(Tracker* tracker, size_t chunksPBlock) : m_chunksBlock(chunksPBlock), m_tracker(tracker) {};

	void* Allocate(size_t size);

	void Deallocate(void* pMem, size_t size);

	Header*				m_header = nullptr;

private:
	size_t				m_chunksBlock;
	size_t				m_sizeOfChunks;

	Chunk*				pAlloc = nullptr;

	Tracker*			m_tracker;
	size_t				m_MemoryUsed;

	Chunk* AllocateBlock(size_t Chunksize);


};


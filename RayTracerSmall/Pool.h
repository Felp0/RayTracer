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
	Pool() {};

	void* Allocate(size_t size);
	void Deallocate(void* pMem, size_t size);

	static Pool& GetPool();

	inline size_t			GetAvailableMem() { return m_MemoryAvailable; }
	inline size_t			GetNumOfChunks() { return m_ChunksUsed; }

	inline void				AddAvailableMem() { m_MemoryAvailable++; }
	inline void				RemoveAvailableMem() { m_MemoryAvailable--; }
	inline void				SetChunksUsed() { m_ChunksUsed++; }
	

	Header*				m_header = nullptr;

private:
	static Pool			pPool;

	size_t				m_chunksBlock;
	size_t				m_sizeOfChunks;
	size_t				m_totalMemory;

	size_t				m_ChunksUsed = 0;
	size_t				m_MemoryAvailable = 0;

	Chunk*				pAlloc = nullptr;

	Tracker*			m_tracker;
	size_t				m_MemoryUsed;

	Chunk* AllocateBlock(size_t Chunksize);


};


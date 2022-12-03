#include "MemoryPool.h"

void* MemoryPool::Allocate(size_t size)
{
	//if no chunks left in the current blocl or any block exist yet, create new one
	if (pAlloc == nullptr)
	{
		pAlloc = AllocateBlock(size);
	}

	Chunk* pFreeChunk = pAlloc;

	pAlloc = pAlloc->pNext;

	return pFreeChunk;
}

void MemoryPool::Deallocate(void* pMem, size_t size)
{
	reinterpret_cast<Chunk*>(pMem)->pNext = pAlloc;

	pAlloc = reinterpret_cast<Chunk*>(pMem);

}

//Allocates a block for chunks
Chunk* MemoryPool::AllocateBlock(size_t Chunksize)
{

	std::cout << "Allocating Block: (" << m_ChunksBlock << " chunks) : \n\n";

	size_t sizeBlock = m_ChunksBlock * Chunksize;

	//First Chunk of new block
	Chunk* pBlockBegin = reinterpret_cast<Chunk*>(malloc(sizeBlock));

	//Chaining BlocksS
	Chunk* pChunk = pBlockBegin;

	for (int i = 0; i < m_ChunksBlock - 1; ++i)
	{
		pChunk->pNext = reinterpret_cast<Chunk*>(reinterpret_cast<char*>(pChunk + Chunksize));
		pChunk = pChunk->pNext;
	}
	pChunk->pNext = nullptr;

	return pBlockBegin;
}

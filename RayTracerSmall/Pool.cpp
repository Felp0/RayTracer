#include "Pool.h"

void* Pool::Allocate(size_t size)
{
	if (pAlloc == __nullptr)
		pAlloc = AllocateBlock(size);

	Chunk* pFreeChunk = pAlloc;
	pAlloc = pAlloc->pNext;

	return pFreeChunk;
}

void Pool::Deallocate(void* pMem, size_t size)
{
	reinterpret_cast<Chunk*>(pMem)->pNext = pAlloc;

	pAlloc = reinterpret_cast<Chunk*>(pMem);
}

Chunk* Pool::AllocateBlock(size_t Chunksize)
{
	std::cout << "Allocating Block: (" << m_chunksBlock << " chunks) : \n\n";

	size_t sizeBlock = m_chunksBlock * Chunksize;

	Chunk* pBlockBegin = reinterpret_cast<Chunk*>(malloc(sizeBlock));
	Chunk* pChunk = pBlockBegin;

	for (int i = 0; i < m_chunksBlock - 1; ++i)
	{
		pChunk->pNext = reinterpret_cast<Chunk*>(reinterpret_cast<char*>(pChunk + Chunksize));
		pChunk = pChunk->pNext;
	}

	pChunk->pNext = nullptr;

	return pBlockBegin;
}

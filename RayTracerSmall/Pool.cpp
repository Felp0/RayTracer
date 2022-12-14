#include "Pool.h"
#include "GlobalController.h"
#include "Tracker.h"


Pool Pool::pPool;

Pool& Pool::GetPool()
{
	return pPool;
}


//if no chunks in the block allocate a new one
void* Pool::Allocate(size_t size)
{
	m_totalMemory += size;
	//no chunks left in the current block, allocate a new one passing the chunk size and the header
	if (pAlloc == nullptr)
		pAlloc = AllocateBlock(size);
	
	//the return value is the current position of the allocation pointer
	Chunk* pFreeChunk = pAlloc;
	pAlloc = pAlloc->pNext;

	return pFreeChunk;
}

void Pool::Deallocate(void* pMem, size_t size)
{
	m_MemoryUsed--;
	m_MemoryAvailable += size;

	Header* pheader = (Header*)pMem;
	pheader->m_tracker = m_tracker;

	m_tracker->RemoveBytes(size, pheader);

	reinterpret_cast<Chunk*>(pMem)->pNext = pAlloc;

	pAlloc = reinterpret_cast<Chunk*>(pMem);

}


//Returns a Chunk pointer set to the beginining of the block.
Chunk* Pool::AllocateBlock(size_t Chunksize)
{
	pPool.GetPool().SetChunksUsed();

#ifdef D3BUG

	std::cout << "Allocating Block: (" << m_chunksBlock << " chunks) : " << std::endl << std::endl;
#endif // D3BUG

	size_t sizeBlock = m_chunksBlock * Chunksize;

	size_t requestedBytes = m_sizeOfChunks + sizeof(Header) + sizeof(Footer);
	char* pMem = (char*)malloc(requestedBytes);

	Header* pheader = (Header*)pMem;
	pheader->m_tracker = m_tracker;

	m_tracker->AllocateBytes(sizeBlock, pheader);

	//First chunk of new block
	Chunk* pBlockBegin = reinterpret_cast<Chunk*>(malloc(sizeBlock));

	//Chaining blocks
	Chunk* pChunk = pBlockBegin;

	for (int i = 0; i < m_chunksBlock - 1; ++i)
	{
		pChunk->pNext = reinterpret_cast<Chunk*>(reinterpret_cast<char*>(pChunk + Chunksize));
		pChunk = pChunk->pNext;
	}

	//std::cout << "Memory Used In Block --- " << m_MemoryUsed << std::endl;

	pChunk->pNext = nullptr;

	void* pFooterAddr = ((char*)pMem + sizeof(Header) + sizeBlock);
	Footer* pFooter = (Footer*)pFooterAddr;

	return pBlockBegin;
}

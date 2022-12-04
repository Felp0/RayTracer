#pragma once
#include "GlobalController.h"

struct Chunk
{
	//if pNext is free next contains the address of the next chunk in the list. if allocated this space is used 
	Chunk* pNext;
	Chunk* pPrev;
};


class MemoryPool
{
public:
	MemoryPool(size_t chunksPBlock): m_ChunksBlock(chunksPBlock), pAlloc(nullptr)
	{

	};

	void* Allocate(size_t size);
	

	void Deallocate(void* pMem, size_t size);
	


	

	
private:
	//number of chunks per block
	size_t					m_ChunksBlock;
	size_t					m_PoolSize;

	//Allocation Pointer
	Chunk*					pAlloc;
	Chunk*					pFree;

	//Allocates a block for chunks
	Chunk*					AllocateBlock(size_t Chunksize);

	
	


};






//The purpose of union is to save memory by using the same memory region for storing different objects at different times
//reinterpret_cast It is used to convert a pointer of some data type into a pointer of another data type, even if the data types before and after conversion are different.
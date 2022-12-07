#pragma once
#include <iostream>

//foward referecing
struct Header;

class Tracker
{
public:
	//Pointer to Header
	Header*					m_currentHeader = nullptr;

	//Bytes calculation
	void					AllocateBytes(size_t size, Header* header);
	void					RemoveBytes(size_t size, Header* header);
	
	//Access tracker from other files using ::
	static Tracker&			GetTracker();

	inline void				SetTotalMemory(size_t allocatedMem) { m_totalMemory = allocatedMem; }
	//inline void				AddUsedMem() { m_MemoryUsed++; }
	//inline void				RemoveUsedMem() { m_MemoryUsed--; }
	//inline void				SetChunksUsed() { m_ChunksUsed++; }

	inline size_t			GetTotalAllocatedMemory() { return m_totalMemory; }
	inline size_t			GetMemUsed() { return m_MemoryUsed; }
	//inline size_t			GetNumOfChunks() { return m_ChunksUsed; }


private:
	//Saw this in the Memory pool website ask  david
	//Tracker(const Tracker&);
	//Tracker& operator=(const Tracker&);

	//Default Tracker
	static Tracker			defaultTracker;

	size_t					m_totalMemory;
	size_t					m_trackerMemory = 0;

	size_t					m_MemoryUsed = 0;
	//size_t					m_MemoryAvailable = 0;
};


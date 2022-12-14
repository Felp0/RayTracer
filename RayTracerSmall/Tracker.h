#pragma once
#include <iostream>
#include <mutex>



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
	

	//inline Tracker& GetTracker() { return defaultTracker; }
	inline size_t			GetTotalAllocatedMemory() { return m_totalMemory; }
	inline size_t			GetMemUsed() { return m_MemoryUsed; }
	


private:
	//Default Tracker
	static Tracker			defaultTracker;

	std::mutex				aMutex; 

	size_t					m_totalMemory;
	size_t					m_trackerMemory = 0;

	size_t					m_MemoryUsed = 0;
};


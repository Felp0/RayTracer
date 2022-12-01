#pragma once
#include <iostream>

//foward referecing
struct Header;

class Tracker
{
public:
	//Pointer to Header
	Header*					m_header = nullptr;

	//Bytes calculation
	void					AllocateBytes(size_t size, Header* header);
	void					RemoveBytes(size_t size, Header* header);
	
	//Access tracker from other files using ::
	static Tracker&			GetTracker();


private:
	//Saw this in the Memory pool website ask  david
	//Tracker(const Tracker&);
	//Tracker& operator=(const Tracker&);

	//Default Tracker
	static Tracker			defaultTracker;

	size_t					m_totalMemory;
};


#include "GlobalController.h"
#include <iostream>

Header* Header::m_next;
Header* Header::m_prev;
Tracker* Header::m_tracker;


void* operator new(size_t size, Tracker* tracker)
{
	
	try 
	{
		size_t requestedBytes = size + sizeof(Header) + sizeof(Footer);
		char* pMem = (char*)malloc(requestedBytes);

		//Header
		Header* pHeader = (Header*)pMem;
		pHeader->m_tracker = tracker;
		tracker->AllocateBytes(size, pHeader);
		pHeader->pPool->Allocate(size);


		void* pFooterAddr = pMem + sizeof(Header) + size;
		Footer* pFooter = (Footer*)pFooterAddr;
		pFooter->checkvalue = 42;

		void* pStartMemBlock = pMem + sizeof(Header);
		return pStartMemBlock;
		
	}
	catch (const std::bad_alloc& error)
	{
		std::cout << "MEMORY COULD NOT BE ALLOCATED: " << error.what() << std::endl;
	}
}

void* operator new(size_t size)
{
	return::operator new(size, &Tracker::GetTracker());
}

void operator delete(void* pMem)
{
	Header* pHeader = (Header*)((char*)pMem - sizeof(Header));
	Footer* pFooter = (Footer*)((char*)pMem + pHeader->size);

	if (pHeader->checkvalue != 42)
	{
		std::cout << "---ERROR HEADER CODE NOT MATCHING---" << std::endl;
	}

	if (pFooter->checkvalue != 42)
	{
		std::cout << "---ERROR FOOTER CODE NOT MATCHING---" << std::endl;
	}
	pHeader->m_tracker->RemoveBytes(pHeader->size, pHeader);

	free(pHeader);
}

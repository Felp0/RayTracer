#pragma once
#include "Tracker.h"
#include "Pool.h"

void* operator new(size_t size);
void* operator new(size_t size, Tracker* tracker);

void operator delete(void* pMem);

struct Header
{
	int size;
	int checkvalue = 42;
	static Tracker* m_tracker;
	static Header* m_prev;
	static Header* m_next;
	Pool* pPool;
};

struct Footer
{
	int reserved;
	int checkvalue = 42;
};

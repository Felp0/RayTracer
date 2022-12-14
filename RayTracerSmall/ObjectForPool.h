#pragma once
#include <iostream>
#include "Pool.h"

//Simple struct to test my Memory Pool
struct Object
{
	uint64_t data[4];

	static Pool poolAlooc;

	static void* operator new(size_t size)
	{
		return poolAlooc.Allocate(size);
	}

	static void operator delete(void* pMem, size_t size)
	{
		return poolAlooc.Deallocate(pMem, size);
	}

};



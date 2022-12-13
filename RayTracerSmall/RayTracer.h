#pragma once
#include <fstream>
#include <iostream>
#include <cassert>
#include <algorithm>
#include <sstream>
#include <string.h>
#include <stdlib.h>
#include <cstdio>
#include <cmath>
#include <vector>
#include <chrono>

#include "Vec3.h"
#include "Sphere.h"
#include "GlobalController.h"
#include "ObjectForPool.h"
#include "Threads.h"

#ifdef _WIN32
#include <ppl.h>
#endif



#if defined __linux__ || defined __APPLE__
// "Compiled for Linux
#else
// Windows doesn't define these values by default, Linux does
#define M_PI 3.141592653589793
#define INFINITY 1e8
#endif

class RayTracer
{

public:
	//RayTracer() {}

    static void render(const std::vector<Sphere>& spheres, int iteration);
	void BasicRender();
	void SimpleShrinking();
	void SmoothScaling(int i);
    static void LinuxSmoothScaling();
	

	

	static Pool m_MemoryAllocator;

	static void* operator new(size_t size)
	{
		return m_MemoryAllocator.Allocate(size);
	}

	static void operator delete(void* pMem, size_t size)
	{
		return m_MemoryAllocator.Deallocate(pMem, size);
	}
private:
	std::mutex aMutex;
	
};


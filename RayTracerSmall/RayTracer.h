#pragma once
#include <stdlib.h>
#include <cstdio>
#include <cmath>
#include <fstream>
#include <vector>
#include <iostream>
#include <cassert>
// Windows only
#include <algorithm>
#include <sstream>
#include <string.h>
#include "Vec3.h"
#include "Sphere.h"
#include "GlobalController.h"




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
	static void* operator new(size_t size);
	static void operator delete(void* pMem);

	void render(const std::vector<Sphere>& spheres, int iteration);
	void BasicRender();
	void SimpleShrinking();
	void SmoothScaling();

	
};


// [header]
// A very basic raytracer example.
// [/header]
// [compile]
// c++ -o raytracer -O3 -Wall raytracer.cpp
// [/compile]
// [ignore]
// Copyright (C) 2012  www.scratchapixel.com
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
// [/ignore]
#include "RayTracer.h"
#include <thread>
#include <vector>


Pool Object::poolAlooc{&Tracker::GetTracker(), 2};
int main(int argc, char **argv)
{
	auto start = std::chrono::steady_clock::now();

	Tracker* pTracker = (Tracker*)malloc(sizeof(Tracker));
	Pool* pPool = (Pool*)malloc(sizeof(Pool));
	// This sample only allows one choice per program execution
	srand(13);
	//BasicRender();
	//SimpleShrinking();
	constexpr int arraysize = 7;

	Object* pObj[arraysize];

#ifdef D3BUG


	std::cout << "size(Obj) = " << sizeof(Object) << std::endl << std::endl;

	std::cout << "Allocating " << arraysize << " objs" << std::endl;
#endif // D3BUG

	//allocate
	for (int i = 0; i < arraysize; ++i)
	{
		pObj[i] = new Object();
		std::cout << "new [ " << i << " ] = " << pObj[i] << std::endl;
		pPool->GetPool().GetAvailableMem();
	}
	 
	std::cout << std::endl;
	


	//deallocate
	for (int i = arraysize - 1; i >= 0; --i)
	{
		std::cout << "deleting " << i << " " << pObj[i] << std::endl;
		delete pObj[i];
		//pTracker->GetTracker().RemoveUsedMem();
	}
#ifdef D3BUG
	std::cout << "---BLOCKS USED: " << pPool->GetPool().GetNumOfChunks() << std::endl;
	
#endif // D3BUG

	pObj[0] = new Object();
	std::cout << "new [0] = " << pObj[0] << std::endl;

	delete pObj[0];

	RayTracer rt;

	std::vector<std::thread> threads;
	for (int i = 0; i <= 100; i++)
	{

		threads.push_back(std::thread(&RayTracer::SmoothScaling, &rt,i));
	}
	for (auto& thread : threads)
	{
		thread.join();

	}
	threads.clear();
	
	free(pTracker); 
	free(pPool);

	auto finish = std::chrono::steady_clock::now();

	double secondsPass = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start).count();

//#ifdef D3BUG
	std::cout << "---TIME TO RUN APPLICATION: " << secondsPass << std::endl << std::endl;

//#endif // D3BUG

	return 0;
}



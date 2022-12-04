#include "Object.h"

MemoryPool* Object::m_MemoryAllocator;

Object::Object()
{
	//Testing Memory pool
	constexpr int arraySize = 10;

	Object* objects[arraySize];

	std::cout << "Size = " << sizeof(Object) << std::endl << std::endl;

	std::cout << "Allocating " << arraySize << " objs" << std::endl;

	//Allocate
	for (int i = 0; i < arraySize; ++i)
	{
		objects[i] = new Object();
		std::cout << "new: " << i << objects[i] << std::endl;
	}

	std::cout << std::endl;

	//Deallocate
	for (int i = arraySize; i >= 0; --i)
	{
		std::cout << "Deleting " << i << " " << objects[i] << std::endl;
		delete objects[i];

	}
	std::cout << std::endl;

	objects[0] = new Object();
	std::cout << "new [0] = " << objects[0] << std::endl << std::endl;


	//new objs reusing prev block

}

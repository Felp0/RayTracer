#pragma once
#include <memory>
#include <assert.h>

template <typename T> struct  MemoryPool
{

	union PoolItem {
	private:
		using StorageType = alignas(alignof(T)) char[sizeof(T)];

		//Points to the next item
		PoolItem* next;
		//Storage of the Item/share with the pointer pNext
		StorageType daTum;

	public:
		//Methos for the list of free items.
		PoolItem			*GetNextItem() const { return next; }

		void				*SetNextItem(PoolItem* newItem) { next = newItem; }

		//Methos for storage of the item
		T					*GetStorage() { return reinterpret_cast<T*>(daTum); }

		//Given T* cast to a PoolItem
		static PoolItem* pStorageToItem(T* t)
		{
			PoolItem* pCurrentItem = reinterpret_cast<PoolItem*>(t);
			return pCurrentItem;
		}
	
	};

	struct PoolArena
	{
	public:
		//Storage of the arena
		PoolItem[]* pStorage;
		//Pointer to the next arena.
		PoolArena* next;

		
		PoolArena(size_t arenaSize) : pStorage(new PoolItem[arenaSize])
		{
			for (size_t i = 1; i < arenaSize; i++)
			{
				pStorage[i - 1].SetNextItem(&pStorage[i]);
				
			}
			
			pStorage[arenaSize - 1].SetNextItem(nullptr);
			
		
			//return a pointer to the array of items
		}

		PoolItem*					getStorage() const { return pStorage.get(); }

		void setNextArena(PoolArena&& newItem)
		{
			assert(!next);

			next.reset(newItem.release());
		}

		//size of arena created by pool
		size_t						sizeOfArena;
		
		PoolArena*					pArena;

		PoolItem*					pFreeList;


	};

	PoolArena(size_t sizeOfArena) : 
		sizeOfArena(sizeOfArena), pArena(new PoolArena)), pFreeList(pArena->) {};


};



//Arenas is an
//The purpose of union is to save memory by using the same memory region for storing different objects at different times
//reinterpret_cast It is used to convert a pointer of some data type into a pointer of another data type, even if the data types before and after conversion are different.
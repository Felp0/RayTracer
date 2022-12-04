#include "Tracker.h"
#include "GlobalController.h"

Tracker Tracker::defaultTracker;

 Tracker& Tracker::GetTracker()
{
	 return defaultTracker;
}

 void Tracker::AllocateBytes(size_t size, Header* header)
 {
	 m_totalMemory += size;
	 m_MemoryAvailable += size;
	 std::cout << "---TOTAL MEMORY ALLOCATED: " << m_totalMemory << std::endl;

	 //Header stuff
	 header->size = size;
	 header->checkvalue = 42;
	 //Advantages of DLL
	/* A DLL can be traversed in both forwardand backward directions.
		 The delete operation in DLL is more efficient if a pointer to the node to be deleted is given.
		 We can quickly insert a new node before a given node.*/
	 //Disavantages of DLL
	/* Every node of DLL Requires extra space for a previous pointer.It is possible to implement DLL with a single pointer though*/
	 header->m_prev = NULL; //Set previous to null because it doesnt exist yet
	 header->m_next = m_currentHeader; //Set next header to the header pointer
	 if (m_currentHeader != NULL)
	 {
		 //if the Header got a value set it to point to previous header
		 m_currentHeader->m_prev = header;
	 }
	 m_currentHeader = header;
	 //ask about this
 }


 void Tracker::RemoveBytes(size_t size, Header* header)
 {
	 if (m_currentHeader == NULL)
		 return;

	 m_MemoryAvailable += size;
	 std::cout << "---TOTAL MEMORY FREE: " << m_MemoryAvailable << std::endl << std::endl;

	 //Setting the pointer from old current to new current (old current next) when deleting from the linked list
	 if (m_currentHeader == header)
	 {
		 m_currentHeader = header->m_next;
	 }

	 //Adjusting the next pointer for the linked list
	 if (header->m_next != NULL)
	 {
		 header->m_next->m_prev = header->m_prev;
	 }

	 //Adjusting previous pointer for the linked list
	 if (header->m_prev != NULL)
	 {
		 header->m_prev->m_next = header->m_next;		
	 }

	 
 }
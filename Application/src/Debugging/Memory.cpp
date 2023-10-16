#ifdef MEMORY_INSPECTION

#include "Debugging/Memory.h"

size_t MemoryAllocator::TotalAllocation = 0;
size_t MemoryAllocator::TotalFreed = 0;

void* operator new(size_t size)
{
	MemoryAllocator::TotalAllocation += size;

	void* address = malloc(size);
	std::cout << "Allocating: " << address << ", " << size << " bytes" << std::endl;
	return address;
}

void operator delete(void* memory, size_t size)
{
	MemoryAllocator::TotalFreed += size;
	std::cout << "Freeing: " << memory << ", " << size << " bytes" << std::endl;

	free(memory);
}

#endif
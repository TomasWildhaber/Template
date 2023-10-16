#pragma once
#include <memory>
#include <iostream>

struct MemoryAllocator
{
	static size_t TotalAllocation;
	static size_t TotalFreed;

	static size_t CurrentAllocation() { return TotalAllocation - TotalFreed; }
};
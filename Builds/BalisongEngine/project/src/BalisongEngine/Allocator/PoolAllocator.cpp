#include "PoolAllocator.h"
using namespace BalisongEngine;
using namespace BalisongEngineAllocator;

#include <stdlib.h>

#include <iostream>
using namespace std;

// ===============================================================================

void* PoolAllocator::Allocate(size_t chunk_size)
{
	// Check if _allocPtr points to null
	// If so, it means need to create a block first!
	// Create block using allocateBlock(chunkSize)
	// it returns a reference to the first chunk in the block.
	if (allocPtr == nullptr)
	{
		allocPtr = AllocateBlock(chunk_size);
	}

	// Otherwise, cache a reference to the current Chunk.
	Chunk* cached_reference = allocPtr;

	// Make _allocPtr point to the next Chunk
	allocPtr = allocPtr->next;

	// return the cached current Chunk reference.
	return cached_reference;
}

// ===============================================================================

void PoolAllocator::Deallocate(void* ptr, size_t chunk_size)
{
	// reinterprete ptr as Chunk
	Chunk* interpreted = reinterpret_cast<Chunk*>(ptr);

	// make the chunk point to _allocPtr
	interpreted->next = allocPtr;

	// update _allocPtr to point to the reinterpreted chunk
	allocPtr = interpreted;
}

// ===============================================================================

Chunk* PoolAllocator::AllocateBlock(size_t chunk_size)
{
	cout << "[PoolAllocator] Allocating block, chunks per block: " << chunksPerBlock << "\n\n";
	// find the size of a block given chunkSize
	size_t block_size = chunksPerBlock * chunk_size;

	void* allocated_memory = malloc(block_size);
	Chunk* first_chunk = reinterpret_cast<Chunk*>(allocated_memory);

	Chunk* chunk = first_chunk;

	// chain chunks in the block
	// from first to second last
	for (int i = 0; i < chunksPerBlock - 1; i++)
	{
		chunk->next = reinterpret_cast<Chunk*>(reinterpret_cast<char*>(chunk) + chunk_size);

		chunk = chunk->next;
	}

	// chunk now points to the last chunk in the block
	chunk->next = nullptr;

	return first_chunk;
}
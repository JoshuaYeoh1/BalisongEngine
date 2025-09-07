#pragma once

namespace BalisongEngine{
namespace BalisongEngineAllocator
{
	// In C++
	// struct by default is public scope
	// class by default is private scope
	// otherwise, they act the same in C++

	/// <summary>
	/// A single unit of memory in a memory pool, used to manage memory allocation and deallocation
	/// </summary>
	struct Chunk
	{
		/// <summary>
		/// Pointer to the next available chunk in the pool
		/// </summary>
		Chunk* next;
	};

	/// <summary>
	/// A pool allocator that manages memory in chunks, optimizing allocation and deallocation for fixed-size objects
	/// </summary>
	class PoolAllocator
	{
	public:

		/// <summary>
		/// Constructs a PoolAllocator with a specified number of chunks per memory block
		/// </summary>
		/// <param name="chunks_per_block"></param>
		PoolAllocator(size_t chunks_per_block) : chunksPerBlock(chunks_per_block) {}

		/// <summary>
		/// Allocates a chunk from the pool, creating a new block if necessary, and updates the pointer to the next available chunk
		/// </summary>
		/// <param name="chunk_size"></param>
		/// <returns></returns>
		void* Allocate(size_t chunk_size);

		/// <summary>
		/// Returns a chunk to the pool by linking it back to the allocation pointer
		/// </summary>
		/// <param name="ptr"></param>
		/// <param name="chunk_size"></param>
		void Deallocate(void* ptr, size_t chunk_size);

	private:

		size_t chunksPerBlock;
		Chunk* allocPtr = nullptr;

		// Allocates a block of memory, partitions it into chunks, links the chunks into a chain, and returns the reference to the first chunk
		Chunk* AllocateBlock(size_t chunk_size);
	};

}
}

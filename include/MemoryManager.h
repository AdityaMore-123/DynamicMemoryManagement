#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <cstdlib>
#include <list>  // Include for list container

struct MemoryBlock {
    void* address;
    size_t size;
    bool isAllocated;
};

class MemoryManager {
private:
    std::list<MemoryBlock> heap;             // List to track all memory blocks
    std::list<MemoryBlock> allocatedBlocks;  // List to track only allocated blocks
    size_t totalAllocated = 0;               // Total memory allocated (bytes)
    size_t totalFreed = 0;                   // Total memory freed (bytes)

public:
    void* allocate(size_t size);         // Allocate memory
    void deallocate(void* block);        // Deallocate memory
    void showStatistics();               // Show memory manager statistics
    void runGarbageCollector();          // Run garbage collection
};

#endif

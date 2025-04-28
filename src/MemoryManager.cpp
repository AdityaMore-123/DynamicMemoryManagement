#include "../include/MemoryManager.h"
#include <iostream>

using namespace std;

// Method to allocate memory
void* MemoryManager::allocate(size_t size) {
    void* block = nullptr;

    for (auto it = heap.begin(); it != heap.end(); ++it) {
        if (!it->isAllocated && it->size >= size) {
            block = it->address;

            if (it->size > size) {
                // Split the block
                MemoryBlock allocatedBlock = {it->address, size, true};
                MemoryBlock remainingBlock = {
                    static_cast<char*>(it->address) + size,
                    it->size - size,
                    false
                };

                it = heap.erase(it);
                heap.insert(it, remainingBlock);
                heap.insert(it, allocatedBlock);
            } else {
                // Exact size match
                it->isAllocated = true;
            }

            allocatedBlocks.push_back({block, size, true});
            totalFreed -= size; // 🔥 Added this line only (minimal required fix)
            cout << "Reused free block at " << block << " of size " << size << " bytes" << endl;
            
            // 🚫 Do not update totalAllocated when reusing!
            return block;
        }
    }

    // No suitable free block, allocate new memory
    block = malloc(size);
    if (block) {
        MemoryBlock newBlock = {block, size, true};
        heap.push_back(newBlock);
        allocatedBlocks.push_back(newBlock);

        totalAllocated += size; // ✅ Increase only here for new allocations
        cout << "Allocated new block at " << block << " of size " << size << " bytes" << endl;
    }

    return block;
}


// Method to deallocate memory
void MemoryManager::deallocate(void* block) {
    for (auto& allocatedBlock : allocatedBlocks) {
        if (allocatedBlock.address == block && allocatedBlock.isAllocated) {
            allocatedBlock.isAllocated = false;  // Mark as freed
            totalFreed += allocatedBlock.size;    // ✅ Increase totalFreed

            cout << "Deallocated block at " << block << endl;

            // Add the deallocated block back to the heap as a free block
            heap.push_back({allocatedBlock.address, allocatedBlock.size, false});
            return;
        }
    }
    cout << "Error: Attempt to free memory that was not allocated" << endl;
}

// Method to show statistics
void MemoryManager::showStatistics() {
    size_t currentlyOccupied = totalAllocated - totalFreed;
    size_t heapFragmentation = 0;

    for (const auto& block : heap) {
        if (!block.isAllocated) {
            heapFragmentation++;
        }
    }

    cout << "\n--- Memory Manager Statistics ---" << endl;
    cout << "Total Allocated: " << totalAllocated << " bytes" << endl;
    cout << "Total Freed: " << totalFreed << " bytes" << endl;
    cout << "Currently Occupied: " << currentlyOccupied << " bytes" << endl;
    cout << "Heap Fragmentation: " << heapFragmentation << " blocks" << endl;
    cout << "----------------------------------\n" << endl;
}

// Method to run garbage collection
void MemoryManager::runGarbageCollector() {
    cout << "Running Garbage Collector...\n";

    for (const auto& allocatedBlock : allocatedBlocks) {
        if (allocatedBlock.isAllocated) {
            cout << "Memory leak detected at " << allocatedBlock.address
                 << ", size: " << allocatedBlock.size << " bytes\n";
        }
    }
}

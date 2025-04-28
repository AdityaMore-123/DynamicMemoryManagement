// Block.h
#ifndef BLOCK_H
#define BLOCK_H

#include <cstddef>

class Block {
public:
    size_t size;
    bool free;
    void* address;

    Block(size_t size, void* address);

    void markFree();
    void markUsed();
};

#endif // BLOCK_H

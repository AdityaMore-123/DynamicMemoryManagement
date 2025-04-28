// Block.cpp
#include "../include/Block.h"


Block::Block(size_t sz, void* addr)
    : size(sz), free(false), address(addr) {}

void Block::markFree() {
    free = true;
}

void Block::markUsed() {
    free = false;
}

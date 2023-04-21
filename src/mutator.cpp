#include "mutator.hpp"

// make sure here call the copy-construct function
Mutator::Mutator(ELF& origin) : victim(origin) {

    let len = origin.map.size;

    self.buf.ptr  = new u8[len];
    self.buf.size = len;

    
}

Mutator::~Mutator() {
    if (self.buf.ptr)
        delete self.buf.ptr;
}

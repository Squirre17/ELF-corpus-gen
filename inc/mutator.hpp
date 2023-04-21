#ifndef __MUTATOR_H__
#define __MUTATOR_H__
#include "common.hpp"
#include "elf.hpp"

class Mutator {
pub:

    ELF victim;

    // Mutator() = default;
    Mutator(ELF& origin);
    void copy();
priv:    
};


#endif
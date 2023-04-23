#ifndef __MUTATOR_H__
#define __MUTATOR_H__
#include "common.hpp"
#include "elf.hpp"
#include "elfmut.hpp"

class Mutator {
pub:

    ELF& origin;
    queue<ELFMut> victims;

    // Mutator() = default;
    Mutator(ELF& origin);
    ~Mutator();

    void add(ELFMut slave);
    void dumpall();
    fn new_slave() -> ELFMut;

priv:    
};


#endif
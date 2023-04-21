#ifndef __MUTATOR_H__
#define __MUTATOR_H__
#include "common.hpp"
#include "elf.hpp"

class Mutator {
pub:

    ELF& origin;
    queue<ELFSlave> victims;

    // Mutator() = default;
    Mutator(ELF& origin);

    void add(ELFSlave slave);
    Mutator& mutate_ehdr_phoff();
    Mutator& mutate_ehdr_shoff();
    Mutator& mutate_ehdr_ehsize();
    Mutator& mutate_ehdr_phentsize();
    Mutator& mutate_ehdr_shentsize();
    Mutator& mutate_ehdr_phnum();
    Mutator& mutate_ehdr_shnum();
    Mutator& generate(u32 size);
priv:    
};


#endif
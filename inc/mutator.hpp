#ifndef __MUTATOR_H__
#define __MUTATOR_H__
#include "common.hpp"
#include "elf.hpp"
#include "elfmut.hpp"

class Mutator {
pub:

    ELF& origin;
    queue<unique_ptr<ELFMut>> victims;

    // Mutator() = default;
    Mutator(ELF& origin);
    ~Mutator();

    fn add(unique_ptr<ELFMut> slave) -> void;
    fn dumpall() -> void;
    // fn new_slave() -> ELFMut;

priv:    
};


#endif
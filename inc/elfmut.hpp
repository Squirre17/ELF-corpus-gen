#ifndef __ELF_MUT_H__
#define __ELF_MUT_H__
#include "common.hpp"
#include "elf.hpp"

/* provide elf mutate method */
class ELFMut : pub ELFSlave {
pub:
    ELFMut(ELF& origin);
    ELFMut& mutate_ehdr_phoff();
    ELFMut& mutate_ehdr_shoff();
    ELFMut& mutate_ehdr_ehsize();
    ELFMut& mutate_ehdr_phentsize();
    ELFMut& mutate_ehdr_shentsize();
    ELFMut& mutate_ehdr_phnum();
    ELFMut& mutate_ehdr_shnum();
    ELFMut  generate();
};


#endif

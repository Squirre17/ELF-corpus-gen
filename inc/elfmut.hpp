#ifndef __ELF_MUT_H__
#define __ELF_MUT_H__
#include "common.hpp"
#include "elf.hpp"

/* provide elf mutate method */
class ELFMut : pub ELFSlave {
pub:
    ELFMut(ELF& origin);
    fn mutate_ehdr_phoff() -> ELFMut&;
    fn mutate_ehdr_shoff() -> ELFMut&;
    fn mutate_ehdr_ehsize() -> ELFMut&;
    fn mutate_ehdr_phentsize() -> ELFMut&;
    fn mutate_ehdr_shentsize() -> ELFMut&;
    fn mutate_ehdr_phnum() -> ELFMut&;
    fn mutate_ehdr_shnum() -> ELFMut&;
    fn mutate_each_section() -> ELFMut&;
    fn mutate_fill_char_in_shstr(u8 chr) -> ELFMut&;
    // ELFMut   generate();
};


#endif

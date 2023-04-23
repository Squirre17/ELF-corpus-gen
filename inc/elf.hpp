#ifndef __ELF_H__
#define __ELF_H__

#include "common.hpp"
#include "fd.hpp"

class ELFBase {
pub:
    unique_ptr<u8 []> base;
    usize size;

    ELFBase() = default;
    ~ELFBase();

    void set_hdr();

    u16 num_of_seg();
    u16 num_of_sec();

    fn ehdr() -> Elf64_Ehdr*;
    fn phdr() -> Elf64_Phdr*;
    fn shdr() -> Elf64_Shdr*;
};


class ELF : pub ELFBase {
pub:
    ELF(string name);
    ~ELF();

priv:
};

/* for modification and mutate */
class ELFSlave : pub ELFBase {
pub:

    ELFSlave(const ELF& origin);
    ~ELFSlave();    

    /* only permit move oper */
    // ELFSlave(ELFSlave&& other); 
    // ELFSlave& operator=(ELFSlave&& other);

    // ELFSlave(const ELFSlave& other)            = delete;
    // ELFSlave& operator=(const ELFSlave& other) = delete;
priv:
};

#endif
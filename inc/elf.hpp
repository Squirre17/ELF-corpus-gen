#ifndef __ELF_H__
#define __ELF_H__

#include "common.hpp"
#include "fd.hpp"

class ELF {
pub:
    class fmap_t
    {
    pub:
        Fd fd;
        u8* base;
        usize size;        
        fmap_t(Fd fd, u8* base, usize size);
        fmap_t() = default; // 显式提供默认构造函数 TODO
        ~fmap_t();
    priv:
    };

    fmap_t map;
    ELF(string name);
    u16 num_of_seg();
    u16 num_of_sec();

    Elf64_Ehdr *ehdr;
    Elf64_Phdr *phdr;
    Elf64_Shdr *shdr;
    
priv:
};

#endif
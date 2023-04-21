#ifndef __ELF_H__
#define __ELF_H__

#include "common.hpp"
#include "fd.hpp"

class ELFBase {
pub:
    typedef struct {
        u8 *ptr;
        usize size;
    } buf_t;

    ELFBase() = default;
    ~ELFBase();
    buf_t buf;

    void set_hdr();

    u16 num_of_seg();
    u16 num_of_sec();

    Elf64_Ehdr *ehdr = NULL;
    Elf64_Phdr *phdr = NULL;
    Elf64_Shdr *shdr = NULL;
};


class ELF : pub ELFBase {
pub:
    class fmap_t
    {
    pub:
        Fd fd;
        u8 *base;
        usize size;
        fmap_t(Fd fd, u8* base, usize size);
        fmap_t() = default; // 显式提供默认构造函数 TODO
        ~fmap_t();
    priv:
    };

    ELF(string name);
    ~ELF();

    fmap_t map;
priv:
};

/* for modification and mutate */
class ELFSlave : pub ELFBase {
pub:

    ELFSlave(ELF& origin);
    ~ELFSlave();    
priv:
};

#endif
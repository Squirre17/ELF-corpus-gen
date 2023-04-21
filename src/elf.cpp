#include "elf.hpp"


u16 ELFBase::num_of_seg() {
    return self.ehdr->e_phnum;
}

u16 ELFBase::num_of_sec() {
    return self.ehdr->e_shnum;
}

/* adjust all hdr */
void ELFBase::set_hdr() {
    self.ehdr = reinterpret_cast<Elf64_Ehdr *>(self.buf.ptr);
    self.phdr = reinterpret_cast<Elf64_Phdr *>(self.buf.ptr + self.ehdr->e_phoff);
    self.shdr = reinterpret_cast<Elf64_Shdr *>(self.buf.ptr + self.ehdr->e_shoff);
}
/* -------------------------------------------------------- */
ELF::fmap_t::fmap_t(Fd fd, u8* base, usize size) 
    : fd(fd) ,base(base) ,size(size) {}

ELF::~ELF(){};

ELF::ELF(string name) {

    Fd fd { name };
    void* base = nullptr;

    fd.o_creat().o_rdonly().open();

    let size = fd.get_file_size();

    base = (void *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd.fd, 0);
    if (!base) 
        PANIC("Failed to map file");

    fmap_t map {fd, (u8 *)base, size};

    self.map = map;
    /* IMPORTANT : buf and ptr pointer to some area, pay attention to, but only use buf */
    self.buf.ptr  = (u8 *)base;
    self.buf.size = size;

    self.set_hdr();
    
}



ELF::fmap_t::~fmap_t() {
    if(self.base)
        munmap(self.base, self.size);
}

/* -------------------------------------------------------- */

/* deep copy construction */
ELFSlave::ELFSlave(ELF& origin) {
    
    let len = origin.buf.size;

    self.buf.ptr = new u8[len];
    self.buf.size = len;

    memcpy(self.buf.ptr, origin.buf.ptr, len);

    self.set_hdr();
}

ELFSlave::~ELFSlave() {
    if (self.buf.ptr)
        delete self.buf.ptr;
}

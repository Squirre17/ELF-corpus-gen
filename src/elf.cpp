#include "elf.hpp"

ELF::fmap_t::fmap_t(Fd fd, u8* base, usize size) 
    : fd(fd), base(base), size(size) {}

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

    self.ehdr = reinterpret_cast<Elf64_Ehdr *>(self.map.base);
    self.phdr = reinterpret_cast<Elf64_Phdr *>(self.map.base + self.ehdr->e_phoff);
    self.shdr = reinterpret_cast<Elf64_Shdr *>(self.map.base + self.ehdr->e_shoff);
    
}

u16 ELF::num_of_seg() {
    return self.ehdr->e_phnum;
}

u16 ELF::num_of_sec() {
    return self.ehdr->e_shnum;
}

ELF::fmap_t::~fmap_t() {
    if(self.base)
        munmap(self.base, self.size);
}



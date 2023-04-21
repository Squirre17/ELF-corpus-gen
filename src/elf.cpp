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

ELFBase::~ELFBase() {
    ACT("ELFBase deconstruct called");
}

/* -------------------------------------------------------- */
ELF::fmap_t::fmap_t(Fd fd, u8* base, usize size) 
    : fd(fd) ,base(base) ,size(size) {}

ELF::~ELF(){
    ACT("ELF deconstruct start");
    if(self.map.base)
        munmap(self.map.base, self.map.size);
};

ELF::ELF(string name) {
    ACT("ELF construct start");

    Fd fd {name};
    void* base = nullptr;

    fd.o_rdonly().open();

    let size = fd.get_file_size();

    base = (void *)mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd.fd, 0);
    if (!base) 
        PANIC("Failed to map file");

    const fmap_t map {fd, (u8 *)base, size};

    // question : why here map will deconstruct
    self.map      = std::move(map);
    /* IMPORTANT : buf and ptr pointer to some area, pay attention to, but only use buf */
    self.buf.ptr  = (u8 *)base;
    self.buf.size = size;

    self.set_hdr();
    ACT("EFL construct over");
}



ELF::fmap_t::~fmap_t() {
    ACT("fmap_t() deconstruct start");

}

/* -------------------------------------------------------- */

/* deep copy construction */
ELFSlave::ELFSlave(ELF& origin) {
    
    let len = origin.buf.size;

    self.buf.ptr = new u8[len];
    self.buf.size = len;

    DBG("len is %d" ,len);

    memcpy(self.buf.ptr, origin.buf.ptr, len);

    self.set_hdr();
}

ELFSlave::~ELFSlave() {
    ACT("ELFSlave deconstruct start");
    if(self.buf.ptr){
        delete self.buf.ptr;
        self.buf.ptr = nullptr;
    }
}

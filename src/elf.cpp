#include "elf.hpp"


u16 ELFBase::num_of_seg() {
    return self.ehdr()->e_phnum;
}

u16 ELFBase::num_of_sec() {
    return self.ehdr()->e_shnum;
}

/* adjust all hdr */
// void ELFBase::set_hdr() {
//     self.ehdr = reinterpret_cast<Elf64_Ehdr *>(self.base.get());
//     self.phdr = reinterpret_cast<Elf64_Phdr *>(self.base.get() + self.ehdr->e_phoff);
//     self.shdr = reinterpret_cast<Elf64_Shdr *>(self.base.get() + self.ehdr->e_shoff);
// }

/* overhead is small so not considering optimize here (i.e add a cache)*/
fn ELFBase::ehdr() -> Elf64_Ehdr* {
    return reinterpret_cast<Elf64_Ehdr *>(self.base.get());
}

fn ELFBase::phdr() -> Elf64_Phdr* {
    return reinterpret_cast<Elf64_Phdr *>(self.base.get() + self.ehdr()->e_phoff);
}

fn ELFBase::shdr() -> Elf64_Shdr* {
    return reinterpret_cast<Elf64_Shdr *>(self.base.get() + self.ehdr()->e_shoff);
}

fn ELFBase::get_addr_of_shstr() -> u8* {
    u16 idx = self.ehdr()->e_shstrndx;
    Elf64_Shdr *shdrs = self.shdr(); 
    return reinterpret_cast<u8 *>(self.base.get() + shdrs[idx].sh_offset);
}

fn ELFBase::get_offset_of_shstr() -> u64 {
    u16 idx = self.ehdr()->e_shstrndx;
    Elf64_Shdr *shdrs = self.shdr(); 
    return reinterpret_cast<u64>(shdrs[idx].sh_offset);
}


ELFBase::~ELFBase() {
    ACT("ELFBase deconstruct called");
}

/* -------------------------------------------------------- */
ELF::~ELF(){
    ACT("ELF deconstruct start");
    if(self.base)
        munmap(self.base.get(), self.size);
};

ELF::ELF(string name) {
    ACT("ELF construct start");

    Fd fd {name};
    fd.o_rdonly().open();

    let __size = fd.get_file_size();
    unique_ptr<u8 []> ptr(new u8[__size]);

    fd.read_to_buf(ptr.get(), __size);

    self.base = std::move(ptr);
    self.size = __size;

    ACT("EFL construct over");
}

/* -------------------------------------------------------- */

/* deep copy construction */ // TODO: verify
ELFSlave::ELFSlave(const ELF& origin) {
    
    let len = origin.size;

    self.base = unique_ptr<u8 []>(new u8[len]);
    self.size = len;

    memcpy(self.base.get(), origin.base.get(), len);
}

ELFSlave::~ELFSlave() {}

// ELFSlave::ELFSlave(ELFSlave&& other) {}

// ELFSlave& ELFSlave::operator=(ELFSlave&& other) {}

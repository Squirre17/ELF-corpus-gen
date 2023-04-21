#include "elfmut.hpp"

ELFMut::ELFMut(ELF& origin) : ELFSlave(origin) {}


ELFMut& ELFMut::mutate_ehdr_phoff() {
    let off = self.ehdr->e_phoff;
    self.ehdr->e_phoff = R(sizeof(off));
    return self;
}

ELFMut& ELFMut::mutate_ehdr_shoff() {
    let off = self.ehdr->e_shoff;
    self.ehdr->e_shoff = R(sizeof(off));
    return self;
}

ELFMut& ELFMut::mutate_ehdr_ehsize() {
    let sz = self.ehdr->e_ehsize;
    self.ehdr->e_ehsize = R(sizeof(sz));
    return self;
}

ELFMut& ELFMut::mutate_ehdr_phentsize() {
    let sz = self.ehdr->e_phentsize;
    self.ehdr->e_phentsize = R(sizeof(sz));
    return self;
}

ELFMut& ELFMut::mutate_ehdr_shentsize() {
    let sz = self.ehdr->e_shentsize;
    self.ehdr->e_shentsize = R(sizeof(sz));
    return self;
}

ELFMut& ELFMut::mutate_ehdr_phnum() {
    let _ = self.ehdr->e_phnum;
    self.ehdr->e_phnum = R(sizeof(_));
    return self;
}

ELFMut& ELFMut::mutate_ehdr_shnum() {
    let _ = self.ehdr->e_shnum;
    self.ehdr->e_shnum = R(sizeof(_));
    return self;
}

/* generate ELFmut instance */
ELFMut ELFMut::generate() {
    return self;
}
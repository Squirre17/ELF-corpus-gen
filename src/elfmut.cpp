#include "elfmut.hpp"

ELFMut::ELFMut(ELF& origin) : ELFSlave(origin) {}


fn ELFMut::mutate_ehdr_phoff() -> ELFMut& {
    let off = self.ehdr()->e_phoff;
    self.ehdr()->e_phoff = R(sizeof(off));
    return self;
}

fn ELFMut::mutate_ehdr_shoff() -> ELFMut& {
    let off = self.ehdr()->e_shoff;
    self.ehdr()->e_shoff = R(sizeof(off));
    return self;
}

fn ELFMut::mutate_ehdr_ehsize() -> ELFMut& {
    let sz = self.ehdr()->e_ehsize;
    self.ehdr()->e_ehsize = R(sizeof(sz));
    return self;
}

fn ELFMut::mutate_ehdr_phentsize() -> ELFMut& {
    let sz = self.ehdr()->e_phentsize;
    self.ehdr()->e_phentsize = R(sizeof(sz));
    return self;
}

fn ELFMut::mutate_ehdr_shentsize() -> ELFMut& {
    let sz = self.ehdr()->e_shentsize;
    self.ehdr()->e_shentsize = R(sizeof(sz));
    return self;
}

fn ELFMut::mutate_ehdr_phnum() -> ELFMut& {
    let _ = self.ehdr()->e_phnum;
    self.ehdr()->e_phnum = R(sizeof(_));
    return self;
}

fn ELFMut::mutate_ehdr_shnum() -> ELFMut& {
    let _ = self.ehdr()->e_shnum;
    self.ehdr()->e_shnum = R(sizeof(_));
    return self;
}

/* generate ELFmut instance */
ELFMut&& ELFMut::generate() {
    return std::move(self);
}
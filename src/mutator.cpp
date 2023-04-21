#include "mutator.hpp"

// make sure here call the copy-construct function
Mutator::Mutator(ELF& origin) : origin(origin) {}

Mutator::~Mutator() {}

void Mutator::add(ELFSlave slave) {
    self.victims.push(slave);
}


Mutator& Mutator::mutate_ehdr_phoff() {

    ELFSlave slave {self.origin};

    let off = slave.ehdr->e_phoff;
    slave.ehdr->e_phoff = R(sizeof(off));
    self.add(slave);
    
}
Mutator& mutate_ehdr_shoff() {
    unimplemented();
}
Mutator& mutate_ehdr_ehsize() {
    unimplemented();
}
Mutator& mutate_ehdr_phentsize() {
    unimplemented();
}
Mutator& mutate_ehdr_shentsize() {
    unimplemented();
}
Mutator& mutate_ehdr_phnum() {
    unimplemented();
}
Mutator& mutate_ehdr_shnum() {
    unimplemented();
}
Mutator& generate(u32 size) {
    unimplemented();
}
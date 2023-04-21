#include "mutator.hpp"
#include "uuid.hpp"
// make sure here call the copy-construct function
Mutator::Mutator(ELF& origin) : origin(origin) {}

Mutator::~Mutator() {}

ELFMut Mutator::new_slave() {
    ELFMut slave {self.origin};
    return slave;
}

void Mutator::add(ELFMut slave) {
    self.victims.push(slave);
}

/* dump all */
void Mutator::dumpall() {

    ACT("dumpall statr");
    
    while (not self.victims.empty()) {

        let victim = self.victims.front();
        self.victims.pop();

        string uuid = "corpus/" + generate_uuid();

        Fd fd {uuid};
        fd.dump(victim.buf.ptr, victim.buf.size);
    }
}
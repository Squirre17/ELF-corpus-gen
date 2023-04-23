#include "mutator.hpp"
#include "uuid.hpp"
// make sure here call the copy-construct function
Mutator::Mutator(ELF& org) : origin(org) {}

Mutator::~Mutator() {}

fn Mutator::new_slave() -> ELFMut {
    ACT("Mutator::new_slave() start");
    ELFMut slave {self.origin};
    return slave;
}

fn Mutator::add(ELFMut slave) -> void {
    self.victims.emplace(std::move(slave));
}

/* dump all */
fn Mutator::dumpall() -> void {

    ACT("dumpall start");
    system("mkdir -p ./corpus");
    
    while (not self.victims.empty()) {

        ELFMut victim = std::move(self.victims.front());
        self.victims.pop();

        string uuid = "corpus/" + uuid::generate_uuid();

        Fd fd {uuid};
        fd.dump(victim.base.get(), victim.size);
    }
}
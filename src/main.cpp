#include <iostream>
#include "common.hpp"
#include "fd.hpp"
#include "elf.hpp"
#include "mutator.hpp"

const string RESET  = "\033[0m";
const string RED    = "\033[31m";
const string GREEN  = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE   = "\033[34m";

fn help() -> void {
    cout << RED << "Usage : " << RESET << "./ELF_corpus_gen <original_elf>" << endl;
    std::exit(1);
}

fn mutator_1(Mutator& mutator) -> void {
    // BUG: copy constructor error
    auto ptr = std::make_unique<ELFMut>(mutator.origin);

    (*ptr).mutate_ehdr_ehsize()
          .mutate_ehdr_phnum()
          .mutate_ehdr_shnum();

    mutator.add(std::move(ptr));
    mutator.dumpall();
    
}

fn main(int argc, char* argv[]) -> int
{
    if(argc != 2) help();

    std::srand(std::time(nullptr));// modify here

    string origin {argv[1]};

    ELF elf {origin};
    OK("ELF loaded");

    Mutator mutator {elf};

    mutator_1(mutator);

    return 0;
}

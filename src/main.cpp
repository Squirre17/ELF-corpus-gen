#include <iostream>
#include "common.hpp"
#include "fd.hpp"
#include "elf.hpp"

const string RESET  = "\033[0m";
const string RED    = "\033[31m";
const string GREEN  = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE   = "\033[34m";

void help() {
    cout << RED << "Usage : " << RESET << "./ELF_corpus_gen <original_elf>" << endl;
    std::exit(1);
}

int main(int argc, char** argv)
{
    if(argc != 2) help();

    string origin {argv[1]};

    ELF elf {origin};
    OK("ELF loaded");

    

    return 0;
}

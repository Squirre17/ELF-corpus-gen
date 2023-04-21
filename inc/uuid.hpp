#include <iostream>
#include <string>
#include <random>
#include <iomanip>

#include "common.hpp" 

inline string generate_uuid() {
    
    std::random_device rd;
    std::mt19937_64 eng(rd());
    std::uniform_int_distribution<unsigned long long> distr;

    unsigned long long uuid1 = distr(eng);
    unsigned long long uuid2 = distr(eng);
    unsigned long long uuid3 = distr(eng);
    unsigned long long uuid4 = distr(eng);

    // format the UUID as a string
    std::stringstream ss;
    ss << std::hex << std::setw(16) << std::setfill('0') << uuid1
       << std::hex << std::setw(16) << std::setfill('0') << uuid2
       << std::hex << std::setw(16) << std::setfill('0') << uuid3
       << std::hex << std::setw(16) << std::setfill('0') << uuid4;

    return "mut-" + ss.str();
}
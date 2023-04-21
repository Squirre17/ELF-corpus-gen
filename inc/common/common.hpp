#ifndef __COMMON_H__
#define __COMMON_H__

/* costom */
#include "alloc-inc.hpp"
#include "config.hpp"
#include "types.hpp"
#include "debug.hpp"
#include "macro.hpp"
#include "hash.hpp"

/* c */
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <elf.h>

#include <stdlib.h>

/* cpp */
#include <iostream>
#include <optional>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <typeinfo>
#include <map>
#include <cstddef>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::byte;
using std::vector;

/* macro */
#define self (*this)
#define let auto
#define pub public
#define priv private
#define prot protected

/* typedef */
typedef ssize_t usize;
typedef const char conchar;
typedef const unsigned char conuchar;
#endif
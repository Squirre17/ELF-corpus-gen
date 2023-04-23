#ifndef __FD_H__
#define __FD_H__
#include "common.hpp"

/*
    O_RDONLY   : Open the file in read-only mode.
    O_WRONLY   : Open the file in write-only mode.
    O_RDWR     : Open the file in read-write mode.
    O_CREAT    : Create the file if it doesn't exist.
    O_EXCL     : When used with O_CREAT, the function will fail if the file already exists.
    O_TRUNC    : Truncate the file to zero length if it already exists.
    O_APPEND   : Append new data to the end of the file.
    O_NONBLOCK : Open the file in non-blocking mode.
    O_SYNC     : Write changes to the file synchronously.
*/
class Fd {
private:
    string name;
    int flags;
    bool is_opened;

public:
    int fd;
    Fd(string name);
    Fd() = default;// TODO
    ~Fd();
    Fd& open();
    Fd& write_to_file(vector<byte> bytes);
    Fd& write_to_file(u8 *buf, usize len);
    Fd& read_to_buf(u8 *buf, usize len);
    Fd& dump(u8 *buf, usize len);                  /* dump data from buf */
    
    u32 get_file_size();

    /* flag associated */
    Fd& clean_flags();
    Fd& o_rdonly();
    Fd& o_wronly();
    Fd& o_creat();
    Fd& o_excl();
    Fd& o_trunc();
};

#endif

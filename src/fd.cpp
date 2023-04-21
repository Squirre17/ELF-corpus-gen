#include "fd.hpp"

Fd::Fd(string name) : name(name) {
    self.fd = -1;
    self.flags = 0;
}

Fd& Fd::clean_flags() {
    self.flags = 0;
    return self;
}

Fd& Fd::open() {

    self.fd = ::open(self.name.c_str(), self.flags, 0666);
    if (self.fd == -1) {
        PANIC("open failed");
    }

    return self;
    
}   

Fd& Fd::write(vector<byte> bytes) {

    assert(self.fd != -1);
    
    conchar *__buf = reinterpret_cast<conchar *>(bytes.data());

    ck_write(self.fd, __buf, bytes.size(), self.name.c_str());

    return self;
}

Fd& Fd::write(char* buf, usize len) {

    assert(self.fd != -1);
    
    conchar *__buf = buf;

    ck_write(self.fd, __buf, len, self.name.c_str());

    return self;
}

u32 Fd::get_file_size()
{
    struct stat st;
    if (stat(self.name.c_str(), &st) < 0)
        return -1;
    return st.st_size;
}

Fd::~Fd() {
    close(self.fd);
}

/* user guarantee the flag is non-conflict */
Fd& Fd::o_rdonly() {
    self.flags |= O_RDONLY;
    return self;
}

Fd& Fd::o_wronly() {
    self.flags |= O_WRONLY;
    return self;
}

Fd& Fd::o_creat() {
    self.flags |= O_CREAT;
    return self;
}

Fd& Fd::o_excl() {
    self.flags |= O_EXCL;
    return self;
}

Fd& Fd::o_trunc() {
    self.flags |= O_TRUNC;
    return self;
}
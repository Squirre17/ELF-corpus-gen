#include "fd.hpp"

Fd::Fd(string name) : name(name) {
    self.fd = -1;
    self.flags = 0;
    self.is_opened = false;
}

Fd& Fd::clean_flags() {
    self.flags = 0;
    return self;
}

Fd& Fd::open() {

    assert(self.is_opened == false);
    self.is_opened = true;

    self.fd = ::open(self.name.c_str(), self.flags, 0666);
    if (self.fd == -1) {
        PANIC("open failed");
    }

    return self;
    
}   

Fd& Fd::write_to_file(vector<byte> bytes) {

    assert(self.fd != -1);
    assert(self.is_opened == true);
    
    conchar *__buf = reinterpret_cast<conchar *>(bytes.data());

    ck_write(self.fd, __buf, bytes.size(), self.name.c_str());

    return self;
}

/* write to fd of opened file */
Fd& Fd::write_to_file(u8 *buf, usize len) {

    assert(self.fd != -1);
    
    conuchar *__buf = static_cast<conuchar *>(buf);

    ck_write(self.fd, __buf, len, self.name.c_str());

    return self;
}

fn Fd::read_to_buf(u8 *buf, usize len) -> Fd& {

    assert(self.fd != -1);
    
    ck_read(self.fd, buf, len, self.name.c_str());

    return self;    
}

Fd& Fd::dump(u8 *buf, usize len) {

    self.clean_flags()
        .o_creat()
        .o_rdonly()
        .o_trunc()
        .open();

    self.write_to_file(buf, len);
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
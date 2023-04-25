#include "elfmut.hpp"

ELFMut::ELFMut(ELF& origin) : ELFSlave(origin) {}

//temporary 
template <typename T>
T random_number(T _) {
    std::random_device rd;  // 获取随机数种子
    std::mt19937 gen(rd()); // 创建随机数生成器

    // 定义分布范围为 [0, numeric_limits<T>::max()] 的均匀分布
    std::uniform_int_distribution<T> dist(0, std::numeric_limits<T>::max());

    // // 将 max_value 限制在 [0, numeric_limits<T>::max()] 范围内
    // max_value = std::min(max_value, std::numeric_limits<T>::max());
    // max_value = std::max(max_value, static_cast<T>(0));

    // 生成随机数并返回
    return dist(gen);
}


fn ELFMut::mutate_ehdr_phoff() -> ELFMut& {
    let off = self.ehdr()->e_phoff;
    self.ehdr()->e_phoff = R(sizeof(off));
    return self;
}

fn ELFMut::mutate_ehdr_shoff() -> ELFMut& {
    let off = self.ehdr()->e_shoff;
    self.ehdr()->e_shoff = R(sizeof(off));
    return self;
}

fn ELFMut::mutate_ehdr_ehsize() -> ELFMut& {
    let sz = self.ehdr()->e_ehsize;
    self.ehdr()->e_ehsize = R(sizeof(sz));
    return self;
}

fn ELFMut::mutate_ehdr_phentsize() -> ELFMut& {
    let sz = self.ehdr()->e_phentsize;
    self.ehdr()->e_phentsize = R(sizeof(sz));
    return self;
}

fn ELFMut::mutate_ehdr_shentsize() -> ELFMut& {
    let sz = self.ehdr()->e_shentsize;
    self.ehdr()->e_shentsize = R(sizeof(sz));
    return self;
}

fn ELFMut::mutate_ehdr_phnum() -> ELFMut& {
    
    let _ = self.ehdr()->e_phnum;
    // self.ehdr()->e_phnum = random_number(_);
    self.ehdr()->e_phnum = 0;
    DBG("mutate e_phnum is %d", self.ehdr()->e_phnum);
    
    return self;
}

fn ELFMut::mutate_ehdr_shnum() -> ELFMut& {

    let _ = self.ehdr()->e_shnum;
    // self.ehdr()->e_shnum = random_number(_);
    self.ehdr()->e_shnum = 0;
    // cout << "DBG : " << static_cast<u32>(std::pow(2 ,sizeof(_))) << endl;
    DBG("mutate e_shnum is %d", self.ehdr()->e_shnum);

    return self;
}

#define RN_ASSIGN(attr) do {             \
    attr = random_number(attr);          \
    DBG("mutate %s is %d", #attr, attr); \
}while(0);

fn ELFMut::mutate_each_section() -> ELFMut& {

    let shdrs = self.shdr();
    let num   = self.num_of_sec();

    for(let i = 0; i < num; i++) {
        cout << "DBG" << i << endl;
        RN_ASSIGN(shdrs[i].sh_link);
        RN_ASSIGN(shdrs[i].sh_name);
        RN_ASSIGN(shdrs[i].sh_offset);
    }
    // cout << "DBG : " << static_cast<u32>(std::pow(2 ,sizeof(_))) << endl;
    // DBG("mutate sh_link is %d", shdrs[i].sh_link);

    return self;
}

/* fill any chars in shstr to scramble \x00 terminated string parse */
fn ELFMut::mutate_fill_char_in_shstr(u8 chr) -> ELFMut& {

    let offset = self.get_offset_of_shstr();
    let remain_size = self.size - offset;
    let addr = self.get_addr_of_shstr();

    memset(addr, chr, remain_size);
    return self;
}

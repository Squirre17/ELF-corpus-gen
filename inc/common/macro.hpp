#ifndef __MACRO_H__
#define __MACRO_H__

#define str_temp(x) #x
#define str(x) str_temp(x)

#define concat_temp(x, y) x ## y
#define concat(x, y) concat_temp(x, y)
#define concat3(x, y, z) concat(concat(x, y), z)
#define concat4(x, y, z, w) concat3(concat(x, y), z, w)
#define concat5(x, y, z, v, w) concat4(concat(x, y), z, v, w)

#define R(x) (random() % (x))

#define MIN(_a,_b) ((_a) > (_b) ? (_b) : (_a))
#define MAX(_a,_b) ((_a) > (_b) ? (_a) : (_b))

#define TODO do {                          \
    SAYL(cPUR "TODO" cRST                  \
        " : implement %s() in %s:%u",      \
        __FUNCTION__, __FILE__, __LINE__); \
    exit(0);                               \
} while (0);

#define DEPRECATED do {                          \
    SAYL(cREDp "DEPRECATED" cRST                 \
        " : %s() have been deprecated in %s:%u", \
        __FUNCTION__, __FILE__, __LINE__);       \
    exit(-1);                                    \
} while(0);

#endif
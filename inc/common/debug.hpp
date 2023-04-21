#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "common.hpp"

#define __USE_COLOR__
#ifdef __USE_COLOR__

#define cBLK "\x1b[0;30m"  /* black  */    
#define cRED "\x1b[0;31m"  /* red    */   
#define cGRE "\x1b[0;32m"  /* green  */   
#define cORA "\x1b[0;33m"  /* orange */   
#define cBLU "\x1b[0;34m"  /* blue   */   
#define cPUR "\x1b[0;35m"  /* purple */   
#define cCYA "\x1b[0;36m"  /* cyan   */   
#define cWHI "\x1b[0;37m"  /* white  */   

#define cBLKp "\x1b[1;90m"  /* black  plus */ 
#define cREDp "\x1b[1;91m"  /* red    plus */ 
#define cGREp "\x1b[1;92m"  /* green  plus */ 
#define cORAp "\x1b[1;93m"  /* orange plus */ 
#define cBLUp "\x1b[1;94m"  /* blue   plus */ 
#define cPURp "\x1b[1;95m"  /* purple plus */ 
#define cCYAp "\x1b[1;96m"  /* cyan   plus */ 
#define cWHIp "\x1b[1;97m"  /* white  plus */ 
#define cRST  "\x1b[0m"      /* reset       */

#ifdef __BG_COLORS__ 

#define bgBLK "\x1b[40m"
#define bgRED "\x1b[41m"
#define bgGRN "\x1b[42m"
#define bgBRN "\x1b[43m"
#define bgBLU "\x1b[44m"
#define bgMGN "\x1b[45m"
#define bgCYA "\x1b[46m"
#define bgLGR "\x1b[47m"
#define bgGRA "\x1b[100m"
#define bgLRD "\x1b[101m"
#define bgLGN "\x1b[102m"
#define bgYEL "\x1b[103m"
#define bgLBL "\x1b[104m"
#define bgPIN "\x1b[105m"
#define bgLCY "\x1b[106m"
#define bgBRI "\x1b[107m"

#endif /* __BG_COLORS__ */
#endif /* __USE_COLOR__ */

// #define TERM_HOME     "\x1b[H"
// #define TERM_CLEAR    TERM_HOME "\x1b[2J"
// #define cEOL          "\x1b[0K"
// #define CURSOR_HIDE   "\x1b[?25l"
// #define CURSOR_SHOW   "\x1b[?25h"

#ifdef __FANCY_BOXES__ // not use yet

#define SET_G1   "\x1b)0"       /* Set G1 for box drawing    */
#define RESET_G1 "\x1b)B"       /* Reset G1 to ASCII         */
#define bSTART   "\x0e"         /* Enter G1 drawing mode     */
#define bSTOP    "\x0f"         /* Leave G1 drawing mode     */
#define bH       "q"            /* Horizontal line           */
#define bV       "x"            /* Vertical line             */
#define bLT      "l"            /* Left top corner           */
#define bRT      "k"            /* Right top corner          */
#define bLB      "m"            /* Left bottom corner        */
#define bRB      "j"            /* Right bottom corner       */
#define bX       "n"            /* Cross                     */
#define bVR      "t"            /* Vertical, branch right    */
#define bVL      "u"            /* Vertical, branch left     */
#define bHT      "v"            /* Horizontal, branch top    */
#define bHB      "w"            /* Horizontal, branch bottom */

#endif /* FANCY_BOXES */
/* wrap of printf */

#define SAY(x...)     printf(x) 
#define SAYL(x...)    { printf(x); puts(""); }

/* Show a prefixed warning. */

#define WARN(x...) do {                        \
    SAY(cORA "[!] " cWHIp "WARNING: " cRST x); \
    SAY(cRST "\n");                            \
  } while (0)

/* Show a prefixed "doing something" message. */

#define ACT(x...) do {                        \
    SAY(cBLU "[*] " cRST x);                  \
    SAY(cRST "\n");                           \
  } while (0)

/* Show a prefixed "success" message. */

#define OK(x...) do {                         \
    SAY(cGRE "[+] " cRST x);                  \
    SAY(cRST "\n");                           \
  } while (0)

/* Show a prefixed "debug" message. */

#define DBG(x...) do {                        \
    SAY(cPUR "[x] " cRST);                    \
    SAY("%s(), %s:%u : ",                     \
        __FUNCTION__, __FILE__, __LINE__ );   \
    SAYL(x);                                  \
  } while (0)

/* Show a prefixed fatal error message . */

#define ERR(x...) do {                        \
    SAY(cRED "\n[-] " cRST);                  \
    SAY("%s(), %s:%u : ",                     \
        __FUNCTION__, __FILE__, __LINE__ );   \
    SAYL(x);                                  \
  } while (0)
/* Die with a verbose non-OS fatal error message. */

#define FATAL(x...) do { \
    SAY(cRED "\n[-] PROGRAM ABORT : " cWHI x);                \
    SAY(cRED "\n         Location : " cRST "%s(), %s:%u\n\n", \
         __FUNCTION__, __FILE__, __LINE__);                   \
    exit(1); \
  } while (0)

/* Die by calling abort() to provide a core dump. */

#define ABORT(x...) do { \
    SAY(cREDp "\n[-] PROGRAM ABORT : " cWHI x);                \
    SAY(cREDp "\n    Stop location : " cRST "%s(), %s:%u\n\n", \
         __FUNCTION__, __FILE__, __LINE__);                    \
    abort(); \
  } while (0)

/* Die with a verbose OS fatal error message. */

#define PANIC(x...) do {                                            \
    fflush(stdout);                                                 \
    SAY(cREDp "\n[-]  SYSTEM ERROR : " cWHI x);                     \
    SAY(cREDp "\n    Stop location : " cRST "%s(), %s:%u\n",        \
         __FUNCTION__, __FILE__, __LINE__);                         \
    SAY(cREDp "       OS message : " cRST "%s\n", strerror(errno)); \
    exit(1);                                                        \
  } while (0)

/* Die with FAULT() or PFAULT() depending on the value of res (used to
   interpret different failure modes for read(), write(), etc). */

#define RPFATAL(res, x...) do {           \
    if (res < 0) PANIC(x); else FATAL(x); \
  } while (0)

/* Error-checking versions of read() and write() that call RPFATAL() as
   appropriate. */

#define ck_write(fd, buf, len, fname) do {                       \
    u32 _len = (len);                                            \
    i32 _res = ::write(fd, buf, _len);                             \
    if (_res != _len) RPFATAL(_res, "Short write to %s", fname); \
  } while (0)

#define ck_read(fd, buf, len, fname) do {                         \
    u32 _len = (len);                                             \
    i32 _res = read(fd, buf, _len);                               \
    if (_res != _len) RPFATAL(_res, "Short read from %s", fname); \
  } while (0)

/* powerful assert equal */
#define assert_eq(varl, varr) do {                             \
    if(varl != varr) {                                         \
        SAY(cREDp "\n[-] Assert failed :" cRST " %p == %p\n"   \
            ,varl, varr                                        \
        );                                                     \
        assert(varl == varr);                                  \
    }                                                          \
  } while (0)

/* powerful assert not equal */
#define assert_neq(varl, varr) do {                            \
    if(varl == varr) {                                         \
        SAY(cREDp "\n[-] Assert failed :" cRST " %p != %p\n"   \
            ,varl, varr                                        \
        );                                                     \
        assert(varl != varr);                                  \
    }                                                          \
  } while (0)


#define unimplemented() do {                                     \
    SAYL(cREDp "\n[-] Unimplamented part : " cRST "%s(), %s:%u", \
            __FUNCTION__, __FILE__, __LINE__);                   \
    exit(1);                                                     \
  } while(0);

#define unreachable() do {                                         \
    SAYL(cREDp "\n[-] Unreachable location : " cRST "%s(), %s:%u", \
            __FUNCTION__, __FILE__, __LINE__);                     \
    exit(1);                                                       \
  } while(0);
  
#endif /* __DEBUG_H__ */


#include <stddef.h>


#define lua_getlocaledecpoint() '.'

__attribute__((import_module("env"), import_name("js_write_string")))
void js_write_string(const char* s, size_t len);

#define lua_writestring(s,l) js_write_string(s, l)
#define lua_writeline() lua_writestring("\n", 1)
//#define lua_writestring(s,l) 0
//#define lua_writeline()
#define lua_writestringerror(s,p) 0

#define lua_initreadline(L)
#define lua_readline(L,b,p) 0
#define lua_saveline(L,line)
#define lua_freeline(L,b)

#define l_randomizePivot() ~0


#define LUAI_TRY(...) xxx
#define LUAI_THROW(...) xxx
typedef int luai_jmpbuf;

typedef void js_try_2_fn(void*, void*);

__attribute__((import_module("env"), import_name("js_try_2")))
void js_try_2(js_try_2_fn* f, void* a1, void* a2);

__attribute__((import_module("env"), import_name("js_throw")))
__attribute__((noreturn))
void js_throw();

/*
** Lua core, libraries, and interpreter in a single file.
** Compiling just this file generates a complete Lua stand-alone
** program:
**
** $ gcc -O2 -std=c99 -o lua onelua.c -lm
**
** or
**
** $ gcc -O2 -std=c89 -DLUA_USE_C89 -o lua onelua.c -lm
**
*/

/* default is to build the full interpreter */
#ifndef MAKE_LIB
#ifndef MAKE_LUAC
#ifndef MAKE_LUA
#define MAKE_LUA
#endif
#endif
#endif


/*
** Choose suitable platform-specific features. Default is no
** platform-specific features. Some of these options may need extra
** libraries such as -ldl -lreadline -lncurses
*/
#if 0
#define LUA_USE_LINUX
#define LUA_USE_MACOSX
#define LUA_USE_POSIX
#define LUA_ANSI
#endif


/* no need to change anything below this line ----------------------------- */

#include "lprefix.h"

#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>
//#include <locale.h>
#include <math.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


/* setup for luaconf.h */
#define LUA_CORE
#define LUA_LIB
#define ltable_c
#define lvm_c
#include "luaconf.h"

/* do not export internal symbols */
#undef LUAI_FUNC
#undef LUAI_DDEC
#undef LUAI_DDEF
#define LUAI_FUNC	static
#define LUAI_DDEC(def)	/* empty */
#define LUAI_DDEF	static

/* core -- used by all */
#include "lzio.c"
#include "lctype.c"
#include "lopcodes.c"
#include "lmem.c"
#include "lundump.c"
#include "ldump.c"
#include "lstate.c"
#include "lgc.c"
#include "llex.c"
#include "lcode.c"
#include "lparser.c"
#include "ldebug.c"
#include "lfunc.c"
#include "lobject.c"
#include "ltm.c"
#include "lstring.c"
#include "ltable.c"
#include "ldo.c"
#include "lvm.c"
#include "lapi.c"

/* auxiliary library -- used by all */
#include "lauxlib.c"

/* standard library  -- not used by luac */
#ifndef MAKE_LUAC
#include "lbaselib.c"
#include "lcorolib.c"
#include "ldblib.c"
//#include "liolib.c"
#include "lmathlib.c"
//#include "loadlib.c"
//#include "loslib.c"
#include "lstrlib.c"
#include "ltablib.c"
#include "lutf8lib.c"
#include "linit.c"
#endif

/* lua */
#ifdef MAKE_LUA
#include "lua.c"
#endif

/* luac */
#ifdef MAKE_LUAC
#include "luac.c"
#endif

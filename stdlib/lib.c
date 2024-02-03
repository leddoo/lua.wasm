#include <stddef.h>

#include "time.h"
#include "signal.h"
#include "assert.h"


__attribute__((import_module("env"), import_name("js_unimplemented")))
__attribute__((noreturn))
void js_unimplemented();


void c_call_indirect_2(void f(void*, void*), void* a1, void* a2) {
    f(a1, a2);
}


void* mi_malloc(size_t size);
void* mi_realloc(void* p, size_t newsize);
void mi_free(void* p);


void __wasm_call_ctors();

void _start() {
    __wasm_call_ctors();
}



// ctype.h

int isalnum(int c) { js_unimplemented(); }
int isalpha(int c) { return ((unsigned)c|32)-'a' < 26; }
int isblank(int c) { js_unimplemented(); }
int iscntrl(int c) { js_unimplemented(); }
int isdigit(int c) { return (unsigned)c-'0' < 10; }
int isgraph(int c) { js_unimplemented(); }
int islower(int c) { return (unsigned)c-'a' < 26; }
int isprint(int c) { js_unimplemented(); }
int ispunct(int c) { js_unimplemented(); }
int isspace(int c) { js_unimplemented(); }
int isupper(int c) { return (unsigned)c-'A' < 26; }
int isxdigit(int c) { js_unimplemented(); }
int tolower(int c) { return islower(c) ? (c & 0x5f) : c; }
int toupper(int c) { return isupper(c) ? (c | 32) : c; }



// errno.h

int errno = 0;



// math.

double floor(double x) { js_unimplemented(); }
double ceil(double x) { js_unimplemented(); }
double sqrt(double x) { js_unimplemented(); }
double pow(double x, double y) { js_unimplemented(); }
double fmod(double x, double y) { js_unimplemented(); }
double fabs(double x) { js_unimplemented(); }
double sin(double x) { js_unimplemented(); }
double cos(double x) { js_unimplemented(); }
double tan(double x) { js_unimplemented(); }
double asin(double x) { js_unimplemented(); }
double acos(double x) { js_unimplemented(); }
double atan2(double x, double y) { js_unimplemented(); }
double log(double x) { js_unimplemented(); }
double log2(double x) { js_unimplemented(); }
double log10(double x) { js_unimplemented(); }
double exp(double x) { js_unimplemented(); }
double ldexp(double num, int exp) { js_unimplemented(); }
double frexp(double value, int* exp) { js_unimplemented(); }



// signal.h

signal_handler_t* signal(int sig, signal_handler_t* handler) { js_unimplemented(); }



// stdio.h

//int snprintf(char* buffer, size_t bufsz, const char* format, ...) { js_unimplemented(); }



// stdlib.h

int abs(int n) {
    return n < 0 ? -n : n;
}

long strtol(const char* str, char** str_end, int base) { js_unimplemented(); }
double strtod(const char* str, char** str_end) { js_unimplemented(); }

void abort() { js_unimplemented(); }

char* getenv(const char* env_var) { js_unimplemented(); }


void* malloc(size_t size) {
    return mi_malloc(size);
}

void* realloc(void* ptr, size_t size) {
    return mi_realloc(ptr, size);
}

void free(void* ptr) {
    return mi_free(ptr);
}



// string.h

void* memset(void* ptr, int value, size_t n) {
    unsigned char* bytes = ptr;
    for(size_t i = 0; i < n; i += 1) {
        bytes[i] = value;
    }
    return ptr;
}

void* memcpy(void* dst, const void* src, size_t n) {
    unsigned char* dst_bytes = dst;
    const unsigned char* src_bytes = src;
    for(size_t i = 0; i < n; i += 1) {
        dst_bytes[i] = src_bytes[i];
    }
    return dst;
}

void* memmove(void* dst, const void* src, size_t n) {
    unsigned char* dst_bytes = dst;
    const unsigned char* src_bytes = src;
    if(dst_bytes < src_bytes) {
        for(size_t i = 0; i < n; i += 1) {
            dst_bytes[i] = src_bytes[i];
        }
    }
    else {
        while(n > 0) {
            n -= 1;
            dst_bytes[n] = src_bytes[n];
        }
    }
    return dst;
}

int memcmp(const void* s1, const void* s2, size_t n) {
    const unsigned char* s1_bytes = s1;
    const unsigned char* s2_bytes = s2;
    for(size_t i = 0; i < n; i += 1) {
        unsigned char diff = s1_bytes[i] - s2_bytes[i];
        if(diff != 0) {
            return diff;
        }
    }
    return 0;
}

void* memchr(const void* s, int c, size_t n) {
    const unsigned char* s_bytes = s;
    while(n > 0 && *s_bytes != c) {
        n -= 1;
        s_bytes += 1;
    }
    return n ? (void*)s_bytes : NULL;
}

size_t strlen(const char* s) {
    size_t len = 0;
    while(*s) {
        s += 1;
        len += 1;
    }
    return len;
}

int strcmp(const char* s1, const char* s2) {
    while(*s1 && (*s1 == *s2)) {
        s1 += 1;
        s2 += 1;
    }
    return *s1 - *s2;
}

int strncmp(const char* s1, const char* s2, size_t n) {
    while(n && *s1 && *s2 && *s1 == *s2) {
        n -= 1;
        s1 += 1;
        s2 += 1;
    }
    return *s1 - *s2;
}

char* strchr(const char* s, int c) {
    while(1) {
        if(*s == c) {
            return (char*)s;
        }
        if(*s == 0) {
            return NULL;
        }
        s += 1;
    }
}

char* strstr(const char* s1, const char* s2) { js_unimplemented(); }

char* strcpy(char* s1, const char* s2) {
    char* orig = s1;
    while((*s1 = *s2)) { s1 += 1; s2 += 1; }
	return orig;
}

char* strpbrk(const char* dest, const char* breakset) { js_unimplemented(); }

size_t strspn(const char *s, const char *c) {
	const char *a = s;
	size_t byteset[32/sizeof(size_t)] = { 0 };

	if (!c[0]) return 0;
	if (!c[1]) {
		for (; *s == *c; s++);
		return s-a;
	}

    #define STRSPN_BITOP(a,b,op) \
        ((a)[(size_t)(b)/(8*sizeof *(a))] op (size_t)1<<((size_t)(b)%(8*sizeof *(a))))
	for (; *c && STRSPN_BITOP(byteset, *(unsigned char *)c, |=); c++);
	for (; *s && STRSPN_BITOP(byteset, *(unsigned char *)s, &); s++);
    #undef STRSPN_BITOP
	return s-a;
}

int strcoll(const char* lhs, const char* rhs) {
    return strcmp(lhs, rhs);
}

char* strerror(int errnum) { js_unimplemented(); }



// time.h
time_t time(time_t* timer) {
    time_t time = 0;
    if(timer) { *timer = time; }
    return time;
}



__attribute__((import_module("env"), import_name("js_write_string")))
void js_write_string(const char* s, size_t len);


#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>
#include <stdlib.h>
#include <stdio.h>


static int c_write_string(lua_State *L) {
    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting exactly 1 argument");
    }

    size_t len;
    const char* ptr = lua_tolstring(L, 1, &len);
    js_write_string(ptr, len);
    return 0;
}

__attribute__((import_module("env"), import_name("js_delete_value")))
void js_delete_value(double id);

static int c_delete_value(lua_State *L) {
    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting exactly 1 argument");
    }

    double id = lua_tonumber(L, 1);

    js_delete_value(id);

    return 0;
}

__attribute__((import_module("env"), import_name("js_alloc_string")))
void js_alloc_string(double dst, const char* ptr, size_t len);

static int c_alloc(lua_State *L) {
    if (lua_gettop(L) != 2) {
        return luaL_error(L, "expecting exactly 2 arguments");
    }

    double dst = lua_tonumber(L, 1);
    size_t len;
    const char* ptr = lua_tolstring(L, 2, &len);
    js_alloc_string(dst, ptr, len);
    return 0;
}

__attribute__((import_module("env"), import_name("js_create_element")))
void js_create_element(double dst, const char* kind, size_t kind_len);

static int c_create_element(lua_State *L) {
    if (lua_gettop(L) != 2) {
        return luaL_error(L, "expecting exactly 2 arguments");
    }

    double dst = lua_tonumber(L, 1);
    size_t kind_len;
    const char* kind = lua_tolstring(L, 2, &kind_len);
    js_create_element(dst, kind, kind_len);
    return 0;
}

__attribute__((import_module("env"), import_name("js_create_text_node")))
void js_create_text_node(double dst, const char* value, size_t value_len);

static int c_create_text_node(lua_State *L) {
    if (lua_gettop(L) != 2) {
        return luaL_error(L, "expecting exactly 2 arguments");
    }

    double dst = lua_tonumber(L, 1);
    size_t value_len;
    const char* value = lua_tolstring(L, 2, &value_len);
    js_create_text_node(dst, value, value_len);
    return 0;
}

__attribute__((import_module("env"), import_name("js_insert_before")))
void js_insert_before(double parent, double node, double ref);

static int c_insert_before(lua_State *L) {
    if (lua_gettop(L) != 3) {
        return luaL_error(L, "expecting exactly 3 arguments");
    }

    double parent = lua_tonumber(L, 1);
    double node = lua_tonumber(L, 2);
    double ref = lua_tonumber(L, 3);
    js_insert_before(parent, node, ref);
    return 0;
}

__attribute__((import_module("env"), import_name("js_replace_node")))
void js_replace_node(double node, double with);

static int c_replace_node(lua_State *L) {
    if (lua_gettop(L) != 2) {
        return luaL_error(L, "expecting exactly 2 arguments");
    }

    double node = lua_tonumber(L, 1);
    double with = lua_tonumber(L, 2);
    js_replace_node(node, with);
    return 0;
}

__attribute__((import_module("env"), import_name("js_remove_node")))
void js_remove_node(double node);

static int c_remove_node(lua_State *L) {
    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting exactly 1 argument");
    }

    double node = lua_tonumber(L, 1);
    js_remove_node(node);
    return 0;
}

__attribute__((import_module("env"), import_name("js_set_data")))
void js_set_data(double id, const char* value, size_t value_len);

static int c_set_data(lua_State *L) {
    if (lua_gettop(L) != 2) {
        return luaL_error(L, "expecting exactly 2 arguments");
    }

    double id = lua_tonumber(L, 1);
    size_t value_len;
    const char* value = lua_tolstring(L, 2, &value_len);
    js_set_data(id, value, value_len);
    return 0;
}

__attribute__((import_module("env"), import_name("js_set_prop_string")))
void js_set_prop_string(double id, const char* key, size_t key_len, const char* value, size_t value_len);

static int c_set_prop(lua_State *L) {
    if (lua_gettop(L) != 3) {
        return luaL_error(L, "expecting exactly 3 arguments");
    }

    double id = lua_tonumber(L, 1);
    size_t key_len;
    const char* key = lua_tolstring(L, 2, &key_len);
    size_t value_len;
    const char* value = lua_tolstring(L, 3, &value_len);
    js_set_prop_string(id, key, key_len, value, value_len);
    return 0;
}

__attribute__((import_module("env"), import_name("js_set_propk_string")))
void js_set_propk_string(double id, double key, const char* value, size_t value_len);

static int c_set_propk(lua_State *L) {
    if (lua_gettop(L) != 3) {
        return luaL_error(L, "expecting exactly 3 arguments");
    }

    double id = lua_tonumber(L, 1);
    double key = lua_tonumber(L, 2);
    size_t value_len;
    const char* value = lua_tolstring(L, 3, &value_len);
    js_set_propk_string(id, key, value, value_len);
    return 0;
}

__attribute__((import_module("env"), import_name("js_push_prop")))
int js_push_prop(lua_State* L, double dst, double id, const char* key, size_t key_len);

static int c_get_prop(lua_State *L) {
    if (lua_gettop(L) != 3) {
        return luaL_error(L, "expecting exactly 3 arguments");
    }

    double dst = lua_tonumber(L, 1);
    double id = lua_tonumber(L, 2);
    size_t key_len;
    const char* key = lua_tolstring(L, 3, &key_len);

    int is_object = js_push_prop(L, dst, id, key, key_len);
    if (is_object) {
        lua_pushnil(L);
    }
    if (lua_gettop(L) != 4) {
        return luaL_error(L, "bug: no value received from js");
    }
    lua_pushboolean(L, is_object);
    return 2;
}

__attribute__((import_module("env"), import_name("js_set_attr_string")))
void js_set_attr_string(double id, const char* key, size_t key_len, const char* value, size_t value_len);

__attribute__((import_module("env"), import_name("js_set_attr_number")))
void js_set_attr_number(double id, const char* key, size_t key_len, double value);

__attribute__((import_module("env"), import_name("js_del_attr")))
void js_del_attr(double id, const char* key, size_t key_len);

static int c_set_attr(lua_State *L) {
    if (lua_gettop(L) != 3) {
        return luaL_error(L, "expecting exactly 3 arguments");
    }

    double id = lua_tonumber(L, 1);

    size_t key_len;
    const char* key = lua_tolstring(L, 2, &key_len);

    int value_ty = lua_type(L, 3);
    if(value_ty == LUA_TSTRING) {
        size_t value_len;
        const char* value = lua_tolstring(L, 3, &value_len);
        js_set_attr_string(id, key, key_len, value, value_len);
    }
    else if(value_ty == LUA_TNUMBER) {
        double value = lua_tonumber(L, 3);
        js_set_attr_number(id, key, key_len, value);
    }
    else if(value_ty == LUA_TBOOLEAN) {
        int value = lua_toboolean(L, 3);
        js_set_attr_number(id, key, key_len, value);
    }
    else if(value_ty == LUA_TNIL) {
        js_del_attr(id, key, key_len);
    }
    else {
        js_unimplemented();
    }

    return 0;
}

__attribute__((import_module("env"), import_name("js_push_attr")))
void js_push_attr(lua_State* L, double id, const char* key, size_t key_len);

static int c_get_attr(lua_State *L) {
    if (lua_gettop(L) != 2) {
        return luaL_error(L, "expecting exactly 2 arguments");
    }

    double id = lua_tonumber(L, 1);
    size_t key_len;
    const char* key = lua_tolstring(L, 2, &key_len);

    js_push_attr(L, id, key, key_len);
    if (lua_gettop(L) != 3) {
        return luaL_error(L, "bug: no value received from js");
    }
    return 1;
}

__attribute__((import_module("env"), import_name("js_first_child")))
void js_first_child(double dst, double node);

static int c_first_child(lua_State *L) {
    if (lua_gettop(L) != 2) {
        return luaL_error(L, "expecting exactly 2 arguments");
    }

    double dst = lua_tonumber(L, 1);
    double node = lua_tonumber(L, 2);
    js_first_child(dst, node);
    return 0;
}

__attribute__((import_module("env"), import_name("js_next_sibling")))
void js_next_sibling(double dst, double node);

static int c_next_sibling(lua_State *L) {
    if (lua_gettop(L) != 2) {
        return luaL_error(L, "expecting exactly 2 arguments");
    }

    double dst = lua_tonumber(L, 1);
    double node = lua_tonumber(L, 2);
    js_next_sibling(dst, node);
    return 0;
}

__attribute__((import_module("env"), import_name("js_create_template")))
void js_create_template(double dst, const char* html, size_t html_len, const char* elems, size_t elem_len);

static int c_create_template(lua_State *L) {
    if (lua_gettop(L) != 3) {
        return luaL_error(L, "expecting exactly 3 arguments");
    }

    double dst = lua_tonumber(L, 1);
    size_t html_len;
    const char* html = lua_tolstring(L, 2, &html_len);
    size_t elems_len;
    const char* elems = lua_tolstring(L, 3, &elems_len);
    js_create_template(dst, html, html_len, elems, elems_len);
    return 0;
}

__attribute__((import_module("env"), import_name("js_call_i_v")))
void js_call_i_v(double func, double arg);

static int c_call_i_v(lua_State *L) {
    if (lua_gettop(L) != 2) {
        return luaL_error(L, "expecting exactly 2 arguments");
    }

    double func = lua_tonumber(L, 1);
    double arg0 = lua_tonumber(L, 2);
    js_call_i_v(func, arg0);
    return 0;
}

__attribute__((import_module("env"), import_name("js_call_method")))
int js_call_method(lua_State* L, double dst, double obj, const char* name_ptr, size_t name_len);

static int c_call_method(lua_State *L) {
    if (lua_gettop(L) < 3) {
        return luaL_error(L, "expecting at least 3 arguments");
    }

    double dst = lua_tonumber(L, 1);
    double obj = lua_tonumber(L, 2);
    size_t name_len;
    const char* name_ptr = lua_tolstring(L, 3, &name_len);

    lua_settop(L, 0);

    int is_object = js_call_method(L, dst, obj, name_ptr, name_len);
    if (is_object) {
        lua_pushnil(L);
    }
    if (lua_gettop(L) != 1) {
        return luaL_error(L, "bug: no value received from js");
    }
    lua_pushboolean(L, is_object);
    return 2;
}

__attribute__((import_module("env"), import_name("js_delegate_event")))
void js_delegate_event(const char* name_ptr, size_t name_len);

int c_delegate_event(lua_State* L) {
    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting exactly 1 argument");
    }

    size_t name_len;
    const char* name = lua_tolstring(L, 1, &name_len);

    char* buffer = malloc(name_len);
    memcpy(buffer, name, name_len);

    js_delegate_event(buffer, name_len);
    return 0;
}

__attribute__((import_module("env"), import_name("js_copy_value")))
void js_copy_value(double dst, double src);

int c_copy_value(lua_State* L) {
    if (lua_gettop(L) != 2) {
        return luaL_error(L, "expecting exactly 2 arguments");
    }

    double dst = lua_tonumber(L, 1);
    double src = lua_tonumber(L, 2);
    js_copy_value(dst, src);
    return 0;
}

static lua_State* get_state() {
    static lua_State* L = NULL;
    if(!L) {
        L = luaL_newstate();
        luaL_openlibs(L);
        lua_register(L, "js_write_string", c_write_string);
        lua_register(L, "js_delete_value", c_delete_value);
        lua_register(L, "js_alloc", c_alloc);
        lua_register(L, "js_create_element", c_create_element);
        lua_register(L, "js_create_text_node", c_create_text_node);
        lua_register(L, "js_insert_before", c_insert_before);
        lua_register(L, "js_replace_node", c_replace_node);
        lua_register(L, "js_remove_node", c_remove_node);
        lua_register(L, "js_set_data", c_set_data);
        lua_register(L, "js_set_prop", c_set_prop);
        lua_register(L, "js_set_propk", c_set_propk);
        lua_register(L, "js_get_prop", c_get_prop);
        lua_register(L, "js_set_attr", c_set_attr);
        lua_register(L, "js_get_attr", c_get_attr);
        lua_register(L, "js_first_child", c_first_child);
        lua_register(L, "js_next_sibling", c_next_sibling);
        lua_register(L, "js_create_template", c_create_template);
        lua_register(L, "js_call_i_v", c_call_i_v);
        lua_register(L, "js_call_method", c_call_method);
        lua_register(L, "js_delegate_event", c_delegate_event);
        lua_register(L, "js_copy_value", c_copy_value);

        luaL_getsubtable(L, LUA_REGISTRYINDEX, LUA_LOADED_TABLE);
        lua_setglobal(L, "_LOADED");
    }
    return L;
}

void push_string(lua_State* L, const char* string, size_t len) {
    if(!L) { L = get_state(); }
    lua_pushlstring(L, string, len);
    free((void*)string);
}

void push_number(lua_State* L, double value) {
    if(!L) { L = get_state(); }
    lua_pushnumber(L, value);
}

void push_boolean(lua_State* L, int value) {
    if(!L) { L = get_state(); }
    lua_pushboolean(L, value);
}

void push_nil(lua_State* L) {
    if(!L) { L = get_state(); }
    lua_pushnil(L);
}

__attribute__((import_module("env"), import_name("js_set_ret_string")))
void js_set_ret_string(const char* ptr, size_t len);

int resume(int from, int status);

int do_string(const char* code) {
    int status;

    lua_State* L = get_state();
    if(lua_gettop(L) != 0) {
        return -2;
    }

    lua_State* co = lua_newthread(L);

    status = luaL_loadstring(L, code);
    if(status != LUA_OK) {
        const char* error = lua_tostring(L, -1);
        js_write_string(error, strlen(error));
        lua_pop(L, 1);
        return -1;
    }

    assert(lua_gettop(L) == 2 && lua_isthread(L, 1) && lua_isfunction(L, 2));

    lua_xmove(L, co, 1); // move function to new thread.

    return resume(0, 0);
}

int resume(int from, int status) {
    lua_State* L = get_state();
    assert(lua_gettop(L) >= 1 && lua_isthread(L, 1));

    lua_State* co = lua_tothread(L, 1);
    if(from == 0) {
        assert(lua_gettop(co) == 1 && lua_isfunction(co, 1));
    }
    else {
        assert(lua_gettop(co) == 0);
    }

    int nargs = 0;
    if(from == 0) {
        assert(lua_gettop(L) >= 1 && lua_isthread(L, 1));
        nargs = lua_gettop(L) - 1;
        if(nargs != 0) {
            lua_xmove(L, co, nargs);
        }
    }
    else if(from == 10) {
        nargs = 1;
        if(status) {
            assert(lua_gettop(L) == 2 && lua_isstring(L, 2));
            lua_xmove(L, co, 1);
        }
        else {
            lua_pushnil(co);
        }
    }
    else {
        js_unimplemented();
    }

    assert(lua_gettop(L) == 1);
    assert(lua_gettop(co) == (from==0) + nargs);

    int nrets;
    status = lua_resume(co, NULL, nargs, &nrets);

    if(status == LUA_OK) {
        lua_settop(L, 0);
        return 0;
    }
    else if(status == LUA_YIELD) {
        if(nrets > 0) {
            lua_xmove(co, L, nrets);

            if(lua_isstring(L, -2)) {
                const char* string = lua_tostring(L, -2);
                if(strcmp(string, "fetch") == 0) {
                    size_t uri_len;
                    const char* uri = lua_tolstring(L, -1, &uri_len);
                    js_set_ret_string(uri, uri_len);
                    lua_settop(L, 1);
                    return 10;
                }
            }
        }

        lua_settop(L, 0);
        return 1;
    }
    else {
        const char* error = lua_tostring(co, -1);
        js_write_string(error, strlen(error));

        lua_settop(L, 0);
        return -1;
    }
}

int on_event(const char* name_ptr, size_t name_len, double lua_id) {
    lua_State* L = get_state();
    assert(lua_gettop(L) == 0);

    lua_State* co = lua_newthread(L);
    lua_getglobal(L, "on_event");
    lua_xmove(L, co, 1);

    // args.
    lua_pushlstring(L, name_ptr, name_len);
    lua_pushnumber(L, lua_id);

    return resume(0, 0);
}


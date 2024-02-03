#include <stdarg.h>

#define stdin 0
#define stdout 1
#define stderr 2

int snprintf(char* buffer, size_t bufsz, const char* format, ...);
int vsnprintf(char* s, size_t n, const char* format, va_list arg);


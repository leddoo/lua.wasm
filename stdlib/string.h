void* memset(void* ptr, int value, size_t n);
void* memcpy(void* dest, const void* src, size_t n);
void* memmove(void* s1, const void* s2, size_t n);
int memcmp(const void* s1, const void* s2, size_t n);
void* memchr(const void* s, int c, size_t n);

size_t strlen(const char* str);
int strcmp(const char* s1, const char* s2);
int strncmp(const char* s1, const char* s2, size_t n);
char* strchr(const char* s, int c);
char* strstr(const char* s1, const char* s2);
char* strcpy(char* s1, const char* s2);

char* strpbrk(const char* dest, const char* breakset);
size_t strspn(const char* s1, const char* s2);
int strcoll(const char* lhs, const char* rhs);

char* strerror(int errnum);


int abs(int n);

long strtol(const char* str, char** str_end, int base);
double strtod(const char* str, char** str_end);

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

void abort();

char* getenv(const char* env_var);


void* malloc(size_t size);
void* realloc(void* ptr, size_t size);
void free(void* ptr);


#ifndef H1_KERNEL_STDARG
#define H1_KERNEL_STDARG

typedef char* va_list;

#define va_start(p, count) (p = (va_list)&count + sizeof(char*))
#define va_arg(p, t) (*(t*)((p += sizeof(char*)) - sizeof(char *)))
#define va_end(p) (p = 0)

#endif
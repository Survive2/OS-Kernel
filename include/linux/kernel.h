#include "../stdarg.h"

#ifndef H1_KERNEL_KERNEL
#define H1_KERNEL_KERNEL

int vsprintf(char *buf, const char *fmt, va_list args);

int printk(const char * fmt, ...);

unsigned int get_cr3();
void set_cr3(unsigned int v);
void enable_page();
 #endif
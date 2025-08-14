#include "types.h"

#ifndef H1_KERNEL_TTY
#define H1_KERNEL_TTY

void console_init(void);
void console_write(char *buf, u32 count);

#endif
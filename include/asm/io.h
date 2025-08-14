#ifndef H1_KERNEL_IO
#define H1_KERNEL_IO

char in_byte(int port);
short in_word(int port);

void out_byte(int port, int v);
void out_word(int port, int v);

#endif
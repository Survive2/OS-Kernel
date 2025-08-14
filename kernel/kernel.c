#include "../include/linux/kernel.h"

inline unsigned int get_cr3(){
    asm volatile("mov eax, cr3;");
}

inline void set_cr3(unsigned int v){
    asm volatile("mov cr3, eax;" ::"a"(v));
}

inline void enable_page(){
    asm volatile(
        "mov eax, cr0;"
        "or eax, 0x80000000;"
        "mov cr0, eax;"
    );
}
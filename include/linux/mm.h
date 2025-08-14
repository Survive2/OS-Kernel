#ifndef H1_KERNEL_MM
#define H1_KERNEL_MM


#include "types.h"

#define PAGE_SIZE 4096

typedef struct check_memory_item_t{

    unsigned int base_addr_low;
    unsigned int base_addr_high;
    unsigned int length_low;
    unsigned int length_high;
    unsigned int type;

}check_memory_item_t;

typedef struct check_memory_info_t{

    unsigned int times;
    check_memory_item_t* data;

}check_memory_info_t;

typedef struct physics_memory_info_t{

    unsigned int addr_start;
    unsigned int addr_end;
    unsigned int valid_mem_size;
    unsigned int pages_total;
    unsigned int pages_free;
    unsigned int pages_used;

}physics_memory_info_t;

typedef struct physics_memory_map_t{

    unsigned int addr_base;
    unsigned int pages_total;
    unsigned int bitmap_item_used;
    unsigned char* map;

}physics_memory_map_t;

void memory_init();
void memory_map_init();
void* get_free_page();
void free_page();
void print_check_memory_info();
void* virtual_memory_init();

void* kmalloc(size_t size);
void kfree_s(void *obj, int size);


#endif
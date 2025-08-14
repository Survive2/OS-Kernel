#include "../include/asm/system.h"
#include "../include/linux/kernel.h"
#include "../include/linux/mm.h"
// #include "../include/linux/task.h"
#include "../include/string.h"

#define PDT_START_ADDR 0x20000

#define VIRTUAL_MEM_START 0x200000

void* virtual_memory_init(){
        printk("Setting pages...\n");
    int *page_dir_table = (int* )PDT_START_ADDR;

    for(int i = 0; i < 4; ++i){
        int page_table = (int)PDT_START_ADDR + ((i + 1) * 0x1000);
        int page_dir_elem = page_table | 7;
        page_dir_table[i] = page_dir_elem;

        int *page_table_array = (int*) page_table;
        printk("Page table: no.%d, mapping to memory: %p\n", i, page_table_array);

        if(i == 0){
            for(int j = 0; j < 0x400; j++){
                int* ptr = &page_table_array[j];
                *ptr = (j * 0x1000) | 7;
            }
        }else{
            for(int j = 0; j < 0x400; j++){
                int* ptr = &page_table_array[j];
                *ptr = ((i * 0x1000 * 0x400) + j * 0x1000) | 7;
            }
        }
    }
    set_cr3((unsigned int)page_dir_table);

    enable_page();

    printk("Page Dir Table addr: 0x%p\n", page_dir_table);
    printk("Page settings done...\n");

    return page_dir_table;
}
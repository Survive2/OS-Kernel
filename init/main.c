#include "../include/linux/tty.h"
#include "../include/linux/kernel.h"
#include "../include/linux/traps.h"
#include "../include/linux/mm.h"
#include "../include/linux/sched.h"
#include "../include/linux/task.h"

extern void clock_init();

void kernel_main(void) {   
    console_init();
    gdt_init();
    idt_init();
    clock_init();
    
    print_check_memory_info();
    memory_init();
    memory_map_init();

    printk("Testing Page...\n");
    for(int i = 0; i < 3; ++i){
        void *p = get_free_page();
        printk("%p\n", p);
        
        free_page(p);
    }
    printk("Test done...\n");

    virtual_memory_init();
    
    printk("Testing allocate memory...\n");
    int* ptr = kmalloc(0x100);
    kfree_s(ptr,0x100);
    printk("Memory allocate testing done...\n");

    task_init();
    // sched();


    char *s = "h1j4cker'os booting up...";
    printk("%s\n",s);

    __asm__("sti;");

    while (true);
    

}
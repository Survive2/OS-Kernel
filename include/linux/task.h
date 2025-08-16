#ifndef H1_KERNEL_TASK
#define H1_KERNEL_TASK

#define NR_TASKS 64
typedef enum task_state_t{

    TASK_INIT,
    TASK_RUNNING,
    TASK_READY,
    TASK_BLOCKED,
    TASK_SLEEPING,
    TASK_WAITING,
    TASK_DIED,

}task_state_t;

typedef void* (*task_fun_t)(void*);

typedef struct tss_t{

    unsigned int backlink;
    unsigned int esp0;
    unsigned int ss0;
    unsigned int esp1;
    unsigned int ss1;
    unsigned int esp2;
    unsigned int ss2;
    unsigned int cr3;
    unsigned int eip;
    unsigned int flags;
    unsigned int eax;
    unsigned int ebx;
    unsigned int ecx;
    unsigned int edx;
    unsigned int esp;
    unsigned int ebp;
    unsigned int esi;
    unsigned int edi;
    unsigned int es;
    unsigned int cs;
    unsigned int ds;
    unsigned int ss;
    unsigned int fs;
    unsigned int gs;
    unsigned int ldtr;
    unsigned short trace : 1;
    unsigned short reserved : 15;
    unsigned short iobase;
    unsigned int ssp;


}__attribute__((packed)) tss_t;

typedef struct task_t{

    tss_t context;
    char name[16];
    int pid;
    int parent_pid;
    task_state_t state;
    int esp;
    task_fun_t function;
    int sched_times;

}__attribute__((packed)) task_t;

task_t* create_task(char* name, task_fun_t function);
void task_init();

int inc_sched_times(task_t* task);

task_fun_t get_task_function(task_t* task);

#endif
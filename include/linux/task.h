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

typedef struct task_t{

    char name[16];
    int pid;
    int parent_pid;
    task_state_t state;
    int esp;
    task_fun_t function;

}__attribute__((packed)) task_t;

task_t* create_task(char* name, task_fun_t function);
void task_init();

task_fun_t get_task_function(task_t* task);

#endif
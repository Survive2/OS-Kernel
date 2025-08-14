#include "../include/linux/kernel.h"
#include "../include/linux/task.h"
// #include "../include/linux/sched.h"
#include "../include/linux/mm.h"
#include "../include/string.h"

task_t* tasks[NR_TASKS] = {0};

static int find_empty_process(){
    int pid_num = 0;

    int is_find = 0;

    for(int i = 0; i < NR_TASKS; i++){
        if(tasks[i] == 0){
            pid_num = i;
            is_find = 1;
            break;
        }
    }

    if(is_find == 0){
        printk("No valid pid!");
        return -1;
    }
    return pid_num;
}

task_t* create_task(char* name, task_fun_t function){
    task_t* task = kmalloc(4096);

    task->state = TASK_INIT;
    memcpy(task->name, name, strlen(task->name));
    task->pid = find_empty_process();
    task->parent_pid = 0;
    task->function = function;
    task->esp = (int)(task) + 0x1000;

    tasks[task->pid] = task;

    task->state = TASK_READY;
    return task;

}

task_fun_t func(){
    for(int i = 0; i < 10000; i++){
        printk("func: %d\n", i);
    }
}

task_fun_t get_task_function(task_t* task){
    // printk("Getting task [%p]...\n", task);
    // printk("Getting function [%p]...\n", task->function);
    return task->function;
}

void task_init(){
    task_t* task = create_task("init_t",func);
}
#include "../include/linux/sched.h"
#include "../include/linux/task.h"
#include "../include/linux/kernel.h"
#include "../include/asm/system.h"

extern task_t* tasks[NR_TASKS];
extern void switch_task();

task_t* current = NULL;

task_t* find_ready_task(){
    task_t* next = NULL;

    for(int i = 0; i < NR_TASKS; i++){
        task_t* task = tasks[i];

        if(task == NULL) continue;
        if(task->state != TASK_READY) continue;
        // if (current == task && TASK_RUNNING == task->state) {
        //     task->state = TASK_READY;
        // }

        next = task;
    }

    if(next != NULL){
        printk("Task found, pid[%d], PCB postion[%p]\n", next->pid, next);
    }
    return next;
}

void sched(){
    task_t* next = find_ready_task();

    current = next;
    next->state = TASK_RUNNING;
    if(current == NULL){
        printk("No tasks found!");
        while(true);
    }
    printk("current is %p\n",current);
    // printk("function is %p\n",current->function);

    switch_task();
}
[SECTION .data]

msg: db "current is %p\n", 10, 13, 0

[SECTION .text]
[BITS 32]

extern printk
extern get_task_function
extern current
extern inc_sched_times


global switch_task
switch_task:
    mov ecx, [current]
    push ecx
    call inc_sched_times
    cmp eax, 0
    je .get_task_func

.restore_task_context:
    mov ecx, [current]
    mov eax, [ecx + 4 * 10]
    mov ebx, [ecx + 4 * 11]
    ; mov [ecx + 4 * 12], ecx
    mov edx, [ecx + 4 * 13]
    mov esp, [ecx + 4 * 14]
    mov ebp, [ecx + 4 * 15]
    mov esi, [ecx + 4 * 16]
    mov edi, [ecx + 4 * 17]

    ;eflags

    sti

    ;eip
    mov ecx, [ecx + 4 * 8]
    jmp ecx

.get_task_func:
    mov eax, [current]
    push eax
    call get_task_function

    sti
    call eax

.end:
    jmp $
    ret
[BITS 32]
[SECTION .text]

extern printk
extern keymap_handler

global interrupt_handler_entry
interrupt_handler_entry:
    push msg
    call printk
    add esp, 4

    iret

; 键盘中断
global keymap_handler_entry
keymap_handler_entry:
    push 0x21
    call keymap_handler
    add esp, 4

    iret

; eax = 调用号
; ebx = 第一个参数
; ecx = 第二个参数
; edx = 第三个参数

msg:
    db "interrupt_handler", 10, 0
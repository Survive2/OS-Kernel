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

msg:
    db "interrupt_handler", 10, 0
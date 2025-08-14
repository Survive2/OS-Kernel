#ifndef H1_KERNEL_HEAD
#define H1_KERNEL_HEAD

typedef struct gdt_item_t {
    unsigned short limit_low;      
    unsigned int base_low : 24;    
    unsigned char type : 4;        
    unsigned char segment : 1;     
    unsigned char DPL : 2;         
    unsigned char present : 1;     
    unsigned char limit_high : 4;  
    unsigned char available : 1;   
    unsigned char long_mode : 1;  
    unsigned char big : 1;         
    unsigned char granularity : 1; 
    unsigned char base_high;      
} __attribute__((packed)) gdt_item_t;

typedef struct interrupt_gate_t{

    short offset_0;
    short selector;
    char reserved;
    char type : 4;
    char segment : 1;
    char DPL : 2;
    char present : 1;
    short offset_1;

}__attribute__((packed)) interrupt_gate_t;

typedef struct gdt_selector_t {
    char RPL : 2;
    char TI : 1;
    short index : 13;
} __attribute__((packed)) gdt_selector_t;

#pragma pack(2)
typedef struct xdt_ptr_t {
    short   limit;
    int     base;
} xdt_ptr_t;
#pragma pack()

#endif
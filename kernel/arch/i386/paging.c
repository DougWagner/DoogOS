#include <stdint.h>
#include <kernel/kernel.h>
#include <string.h>
#include "mem.h"

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t kernel_page_table[1024] __attribute__((aligned(4096)));
ptable_t kernel_heap[255] __attribute__((aligned(4096))); // index 0 is the heap header, 1-254 is the actual heap (size: 1 GiB - 8 MiB)
// ptable_t usr_memory[768] __attribute__((aligned(4096))); // i dunno but this might need to be kmalloc'd later..'

static void init_page_directory(void) {
    for (size_t i = 0; i < 1024; i++) { // initialize page directory entries
        page_directory[i] = 0x00000002; // read/write bit set to 1, all other bits 0
    }
}

static void init_kernel_page_table(void) {
    for (size_t i = 0; i < 1024; i++) {
        kernel_page_table[i] = (i * 0x1000) | 3;
    }
    page_directory[0] = (uint32_t)kernel_page_table | 3;
}

// i'm giving the kernel almost 1 GiB of heap space. i probably don't need that much but whatever, this is a learning experience
static void init_kernel_heap(void) {
    uint32_t mem_loc = KERNEL_HEAP_HEAD;
    memset((void*)KERNEL_HEAP_HEAD, 0, KERNEL_HEAP_BEGIN - KERNEL_HEAP_HEAD); // guarantee heap head is set to 0
    for (size_t i = 0; i < 255; i++) {
        for (size_t j = 0; j < 1024; j++, mem_loc += 4096) {
            kernel_heap[i].table[j] = mem_loc | 3;
        }
        page_directory[i+1] = (uint32_t)kernel_heap[i].table | 3;
    }
}

extern void load_page_directory(uint32_t*);
extern void enable_paging();

void setup_paging(void) {
    //printk("init page directory...");
    init_page_directory();
    //printk("DONE\n");
    //printk("init kernel page table...");
    init_kernel_page_table();
    //printk("DONE\n");
    //printk("init kernel heap...");
    init_kernel_heap();
    //printk("DONE\n");
    //printk("page_directory addr: %x\n", page_directory);
    //printk("kernel_page_table addr: %x\n", kernel_page_table);
    //printk("kernel_page_table | 3: %x\n", (uint32_t)kernel_page_table | 3);
    load_page_directory(page_directory);
    enable_paging();
}


#include <stdint.h>
#include <kernel/kernel.h>
#include <string.h>

uint32_t page_directory[1024] __attribute__((aligned(4096)));
uint32_t kernel_page_table[1024] __attribute((aligned(4096))); // table where (hopefully) the kernel memory will be stored - look it up later to make sure this is happening properly

extern void load_page_directory(uint32_t*);
extern void enable_paging();
void setup_paging(void) {
    for (size_t i = 0; i < 1024; i++) { // initialize page directory entries
        page_directory[i] = 0x00000002; // read/write bit set to 1, all other bits 0
    }
    for (size_t i = 0; i < 1024; i++) {
        kernel_page_table[i] = (i * 0x1000) | 3;
    }
    //printk("page_directory addr: %x\n", page_directory);
    //printk("kernel_page_table addr: %x\n", kernel_page_table);
    //printk("kernel_page_table | 3: %x\n", (uint32_t)kernel_page_table | 3);
    page_directory[0] = (uint32_t)kernel_page_table | 3;
    load_page_directory(page_directory);
    enable_paging();
}

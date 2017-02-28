#ifndef MEM_H
#define MEM_H

#include <stddef.h>
#include <stdint.h>

// kernel mem space
#define KERNEL_BEGIN        0x00000000
#define KERNEL_END          0x003FFFFF

// kernel heap space
#define KERNEL_HEAP_HEAD    0x00400000
#define KERNEL_HEAP_BEGIN   0x00800000 
#define KERNEL_HEAP_END     0x3FFFFFFF

// userspace gets rest of memory - processes will manage local virtual memory
#define USR_BEGIN           0x40000000
#define USR_END             0xFFFFFFFF

typedef struct _ptable_t {
    uint32_t table[1024] __attribute__((aligned(4096)));
} ptable_t;

/* I'm not sure if these will be used or not yet... will probably need to change them
typedef struct _kmem_obj {
    uint32_t size;
    void* mem;
} kmem_t;

typedef struct _klist_node {
    struct _klist_node* next;
    struct _klist_node* prev;
    kmem_t memobj;
} knode_t;

typedef struct _kheap_list {
    knode_t* head;
    knode_t* tail;
    int size; 
} kheap_t;
*/

void* kmalloc(size_t); // allocate memory within kernel heap
void kfree(void*); // free memory allocated within kernel heap

#endif
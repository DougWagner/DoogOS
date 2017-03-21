#ifndef MEM_H
#define MEM_H

#include <stddef.h>
#include <stdint.h>

#ifdef ARCH_I386
// kernel mem space
#define KERNEL_BEGIN        0x00000000
#define KERNEL_END          0x003FFFFF

// kernel heap space
#define KERNEL_HEAP_HEAD    0x00400000
#define KERNEL_HEAP_BEGIN   0x00800000 
#define KERNEL_HEAP_END     0x3FFFFFFF

#define KERNEL_HEAP_SIZE    KERNEL_HEAP_END - KERNEL_HEAP_BEGIN

// userspace gets rest of memory - processes will manage local virtual memory
#define USR_BEGIN           0x40000000
#define USR_END             0xFFFFFFFF

typedef struct _ptable_t {
    uint32_t table[1024] __attribute__((aligned(4096)));
} ptable_t;

typedef struct _flist_node { // free list node
    size_t size;
    struct _flist_node * next;
} flnode_t;

typedef struct _memobj_header { // allocated memory header
    size_t allocated;
    void * blank;
} memobj_t;

#endif

void init_heap(void);

void* kmalloc(size_t); // allocate memory within kernel heap
void* kcalloc(size_t, size_t); // allocate and initialize memory within kernel heap
void* krealloc(void*, size_t); // reallocate memory within kernel heap
void kfree(void*); // free memory allocated within kernel heap

void debug_print_heap(void);

#endif
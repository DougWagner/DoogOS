#include <kernel/mem.h>
#include <kernel/kernel.h>
#include <string.h>

//const uintptr_t kernel_head = KERNEL_HEAP_HEAD;
const uintptr_t kernel_heap_begin = KERNEL_HEAP_BEGIN;
const uintptr_t kernel_heap_end = KERNEL_HEAP_END;

const size_t kernel_heap_size = KERNEL_HEAP_SIZE;

static void * kernel_heap = ( void * ) KERNEL_HEAP_BEGIN;
static flnode_t * head = NULL;

static flnode_t * fl_insert_new_node( flnode_t * oldnode, size_t memsize, size_t oldsize ) {
    void * newnodeloc = ( void * ) oldnode + memsize;
    flnode_t * newnode = newnodeloc;
    if ( oldsize - memsize <= sizeof( flnode_t ) && oldnode->next != NULL ) {
        return oldnode->next;
    }
    newnode->next = oldnode->next;
    newnode->size = oldsize - memsize;
    oldnode->next = newnode;
    return newnode;
}

static flnode_t * fl_get_next_free( flnode_t * head, size_t n ) {
    flnode_t * tmp;
    for ( tmp = head; tmp->size < n + sizeof( memobj_t ) && tmp->next != NULL; tmp = tmp->next );
    if ( tmp->next == NULL ) {
        if ( tmp->size < n + sizeof( memobj_t ) ) {
            return NULL;
        }
    }
    return tmp;
}

static memobj_t * fl_allocate_at_node( flnode_t * node, size_t n ) {
    if ( node == NULL ) {
        return NULL;
    }
    memobj_t * obj = ( memobj_t * ) node;
    obj->allocated = n + sizeof( memobj_t );
    return obj;
}

static void fl_unlink_node( flnode_t * target, flnode_t * head, flnode_t * next ) {
    for ( ; head != NULL && head->next != target; head = head->next );
    if ( head == NULL ) {
        printk( "something very very bad happened\nthings are definitely broken. good luck.\n" );
    }
    head->next = next;
}

static memobj_t * fl_get_block_memobj( void * ptr ) {
    void * memobj_loc = ptr - sizeof( memobj_t );
    return ( memobj_t * ) memobj_loc;
}

static int fl_merge_contiguous_blocks( flnode_t * node ) {
    int merged = 0;
    for ( ; node != NULL; node = node->next ) {
        uintptr_t nodeloc = ( uintptr_t ) node;
        uintptr_t nextloc = ( uintptr_t ) node->next;
        if ( nodeloc + node->size <= nextloc && nodeloc + node->size > nextloc - sizeof( memobj_t ) ) {
            size_t fragment = nextloc - ( nodeloc + node->size );
            node->size = node->size + node->next->size + fragment;
            node->next = node->next->next;
            merged = 1;
        }
    }
    return merged;
}

void init_heap( void ) {
    if ( head == NULL ) { // function does nothing if heap is already installed
        head = kernel_heap;
        head->next = NULL;
        head->size = kernel_heap_size;
    }
}

void * kmalloc( size_t size ) {
    if ( size == 0 ) {
        return NULL;
    }
    flnode_t * tmp = fl_get_next_free( head, size );
    size_t extra = 0;
    if ( tmp != NULL ) {
        size_t memsize = sizeof( memobj_t ) + size;
        size_t oldsize = tmp->size;
        if ( tmp == head ) { // block found at head
            if ( head->next == NULL || head->size >= oldsize - memsize ) {
                head = fl_insert_new_node( head, memsize, oldsize );
            }
            else {
                head = head->next;
            }
        }
        else if ( tmp->next == NULL ) { // block found at list end
            flnode_t * newnode = fl_insert_new_node( tmp, memsize, oldsize );
            fl_unlink_node( tmp, head, newnode );
        }
        else { // block found in middle of list
            if ( memsize == tmp->size || memsize + sizeof( flnode_t ) > tmp->size ) {
                // holy crap we found an exact match :O
                fl_unlink_node( tmp, head, tmp->next );
            }
            else {
                flnode_t * newnode = fl_insert_new_node( tmp, memsize, oldsize );
                fl_unlink_node( tmp, head, newnode );
            }
        }
        if ( oldsize - memsize <= sizeof( flnode_t ) && tmp->next->next != NULL ) {
            extra = oldsize - memsize;
        }
    }
    memobj_t * obj = fl_allocate_at_node( tmp, size + extra );
    #ifdef DEBUG_HEAP
    debug_print_heap();
    #endif
    return obj != NULL ? ( void * ) obj + sizeof( memobj_t ) : NULL;
}

void * kcalloc( size_t nmemb, size_t size ) {
    void * ptr = kmalloc( nmemb * size );
    if ( ptr != NULL ) {
        memset( ptr, 0, nmemb * size );
    }
    return ptr;
}
/*
void * krealloc( void * ptr, size_t size ) {

}
*/
void kfree( void * ptr ) {
    uintptr_t ptr_loc = ( uintptr_t ) ptr;
    flnode_t * node;
    for ( node = head; node->next != NULL && ptr_loc > ( uintptr_t ) node->next; node = node->next ); // loop to last node before ptr_loc
    memobj_t * obj = fl_get_block_memobj( ptr );
    flnode_t * freenode = ( flnode_t * ) obj; // obj->allocated should be in the same memory location as freenode->size
    if ( ptr_loc < ( uintptr_t ) head ) { // block to free is before head
        freenode->next = head;
        head = freenode;
    }
    else {
        freenode->next = node->next;
        node->next = freenode;
    }
    while ( fl_merge_contiguous_blocks( head ) );
    #ifdef DEBUG_HEAP
    debug_print_heap();
    #endif
}

void debug_print_heap( void ) {
    printk("printing list\n");
    flnode_t * tmp = head;
    for ( size_t i = 0; tmp != NULL; i++, tmp = tmp->next ) {
        char * node = ( i == 0 ) ? "head" : "node";
        printk("%s: %p - %s->size: %x - %s->next: %p\n", node, tmp, node, tmp->size, node, tmp->next );
    }
    printk("\n");
}
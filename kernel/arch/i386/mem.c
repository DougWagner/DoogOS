#include <kernel/mem.h>
#include <kernel/kernel.h>

const uintptr_t kernel_heap_begin = KERNEL_HEAP_BEGIN;
const uintptr_t kernel_heap_end = KERNEL_HEAP_END;
const size_t kernel_heap_size = KERNEL_HEAP_SIZE;
//const uintptr_t kernel_head = KERNEL_HEAP_HEAD;

static void * kernel_heap = ( void * ) KERNEL_HEAP_BEGIN;
static flnode_t * head = NULL;

static flnode_t * fl_init( void * ptr, size_t heap_size ) {
    flnode_t * node = ptr;
    node->next = NULL;
    node->size = heap_size;
    return node;
}

static flnode_t * fl_insert_new_node( flnode_t * oldnode, size_t memsize, size_t oldsize ) {
    void * newnodeloc = ( void * ) oldnode + memsize;
    flnode_t * newnode = newnodeloc;
    newnode->next = oldnode->next;
    newnode->size = oldsize - memsize;
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

static void fl_merge_contiguous_blocks( flnode_t * node ) {
    for ( ; node != NULL; node = node->next ) {
        if ( ( uintptr_t ) node + node->size == ( uintptr_t ) node->next ) {
            node->size = node->size + node->next->size;
            node->next = node->next->next;
        }
    }
}

void init_heap(void) {
    head = (flnode_t*) kernel_heap_begin;
    head->next = NULL;
    head->size = kernel_heap_size;
}

void * kmalloc( size_t size ) {
    flnode_t * tmp = fl_get_next_free( head, size );
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
    }
    memobj_t * obj = fl_allocate_at_node( tmp, size );
    return obj != NULL ? ( void * ) obj + sizeof( memobj_t ) : NULL;
}

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
    fl_merge_contiguous_blocks( head );
}
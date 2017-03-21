#include <kernel/tty.h>
#include <kernel/kernel.h>
#include <kernel/mem.h>
#include <stdlib.h>
#include <string.h>

// THIS FUNCTION IS TEMPORARY
void delay(size_t x) {
    for(volatile size_t i = 0; i < x; i++) {
        for(volatile size_t j = 0; j < 1000000; j++)
            ;
    }
}

#define NUM_POINTERS_STORED 2048

void heap_test(void) {
    printk("testing kmalloc\n");
    void * _pointers_stored[NUM_POINTERS_STORED];

        size_t i = 0;
    for( i = 0; i < NUM_POINTERS_STORED; ++i )
    {
        _pointers_stored[i] = NULL;
    }

    // same size worst case
    if( 1 )
    {
        printk( "same size worst case - press enter to start\n" );
        //getchar();
        size_t i = 0;
        for( i = 0; i < NUM_POINTERS_STORED; ++i )
        {
            size_t malloc_size = (1024*1024) / NUM_POINTERS_STORED - sizeof( memobj_t );
            _pointers_stored[i] = kmalloc( malloc_size ); // (1024*1024) is the 1MB magic number
            if ( _pointers_stored[i] != NULL ) memset( _pointers_stored[i], 42, malloc_size );
        }


        for( i = NUM_POINTERS_STORED - 1; i < NUM_POINTERS_STORED; --i ) // uses unsigned integer rollover to stop, may break if size_t is signed.
        //for( i = 0; i < NUM_POINTERS_STORED; i++ ) // either loop works
        {
            kfree( _pointers_stored[i] );
            _pointers_stored[i] = NULL;
        }
        printk( "Test complete\n\n" );
        debug_print_heap();
    }

    delay(10);
    // random size allocation and random order deallocations
    if( 1 )
    {
        printk( "random size allocation and deallocation - press enter to start\n" );
        //getchar();
        size_t numallocatons = 0;
        size_t i = 0;
        for( i = 0; i < 1024; ++i )
        {
            size_t malloc_size = rand() % 512 + 1;
            _pointers_stored[numallocatons] = kmalloc( malloc_size ); // random size is capped at 1024
            if ( _pointers_stored[numallocatons] != NULL ) memset( _pointers_stored[numallocatons], 42, malloc_size );
            numallocatons++;
        }

        // randomize the allocations order
        i = 0;
        while( i < 8192 )
        {
            size_t a = rand()%numallocatons;
            size_t b = rand()%numallocatons;
            void * tmp = _pointers_stored[a];
            _pointers_stored[a] = _pointers_stored[b];
            _pointers_stored[b] = tmp;
            ++i;
        }

        for( i = 0; i < numallocatons; ++i ) 
        {
            if ( rand() % 2 == 0 && numallocatons < NUM_POINTERS_STORED ) { // dice roll
                size_t malloc_size = rand() % 512 + 1;
                _pointers_stored[numallocatons] = kmalloc( malloc_size ); 
                //if ( _pointers_stored[numallocatons] != NULL ) memset( _pointers_stored[numallocatons], 42, malloc_size );
                size_t a = numallocatons;
                size_t b = rand() % ( numallocatons - i );
                void * tmp = _pointers_stored[a];
                _pointers_stored[a] = _pointers_stored[i + b];
                _pointers_stored[i + b] = tmp;
                numallocatons++;
            }
            //printk( "number deallocated: %lu\n", i );
            if ( _pointers_stored[i] != NULL ) {
                kfree( _pointers_stored[i] );
                _pointers_stored[i] = NULL;
            }
        }
        printk( "Test complete\n\n" );
        debug_print_heap();
        printk( "total allocated: %d\n", numallocatons );
        printk( "total deallocated: %d\n\n", i );
    }

    // same size random allocation and deallocation
    if ( 1 )
    {
        printk( "same size random allocation and deallocation - press enter to start\n" );
        //getchar();
        size_t numallocatons = 0;
        size_t i = 0;
        for( i = 0; i < 1024; ++i )
        {
            _pointers_stored[numallocatons] = kmalloc( 0x80 ); // random size is capped at 1024
            if ( _pointers_stored[numallocatons] != NULL ) memset( _pointers_stored[numallocatons], 42, 0x80 );
            numallocatons++;
        }

        // randomize the allocations order
        i = 0;
        while( i < 8192 )
        {
            size_t a = rand()%numallocatons;
            size_t b = rand()%numallocatons;
            void * tmp = _pointers_stored[a];
            _pointers_stored[a] = _pointers_stored[b];
            _pointers_stored[b] = tmp;
            ++i;
        }

        for( i = 0; i < numallocatons; ++i ) 
        {
            if ( rand() % 2 == 0 && numallocatons < NUM_POINTERS_STORED ) { // dice roll
                _pointers_stored[numallocatons] = kmalloc( 0x80 ); 
                if ( _pointers_stored[numallocatons] != NULL ) memset( _pointers_stored[numallocatons], 42, 0x80 );
                size_t a = numallocatons;
                size_t b = rand() % ( numallocatons - i );
                void * tmp = _pointers_stored[a];
                _pointers_stored[a] = _pointers_stored[i + b];
                _pointers_stored[i + b] = tmp;
                numallocatons++;
            }
            //printk( "number deallocated: %lu\n", i );
            if ( _pointers_stored[i] != NULL ) {
                kfree( _pointers_stored[i] );
                _pointers_stored[i] = NULL;
            }
        }
        printk( "Test complete\n\n" );
        debug_print_heap();
        printk( "total allocated: %d\n", numallocatons );
        printk( "total deallocated: %d\n\n", i );
    }

    // rolling size increase allocation
    if( 1 )
    {
        printk( "rolling size increase allocation - press enter to start\n" );
        //getchar();
        size_t current_size = 1;

        size_t numallocatons = 0;
        size_t i = 0;

        for( i = 0; i < 0x3fff; ++i )
        {
            if( _pointers_stored[numallocatons%2] != NULL )
            {
                kfree( _pointers_stored[numallocatons%2] );

                _pointers_stored[numallocatons%2] = NULL;
            }

            _pointers_stored[numallocatons%2] = kmalloc( current_size );
            memset( _pointers_stored[numallocatons%2], 42, current_size++ );
            ++numallocatons;
        }

        for( i = 0; i < NUM_POINTERS_STORED; ++i ) 
        {
            if( _pointers_stored[i] == NULL )
            {
                continue;
            }
            kfree( _pointers_stored[i] );
            _pointers_stored[i] = NULL;
        }
        printk( "Test complete\n\n" );
        debug_print_heap();
    }

    for( i = 0; i < NUM_POINTERS_STORED; ++i )
    {
        if( _pointers_stored[i] == NULL )
        {
            continue;
        }
        kfree( _pointers_stored[i] );
        _pointers_stored[i] = NULL;
    }
}

void kernel_main(void) {
    init_heap();
    heap_test();
    printk("Welcome to DoogOS! Have fun doing nothing!\n");

    for (;;);
}

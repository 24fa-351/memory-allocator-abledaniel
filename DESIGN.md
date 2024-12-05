#MALLOC

*  allocates memory from
* we have a bunch fo rwe know about
* We store it (from some reason) on a heap
* reserving space for who called us
* from our (min)heap


## HEAP

* a bunch of chunsk of memory
* struct chunk_on_heap {int size; char* pointer_to_start};

* add a chunk back (on free)
 create the chunk_on_heap; heap_insert();

* get a chunk out (it's not our any more, its the users)

    try to find this size or bigger;
    if found a chunk : cut it into two (acutal size, and leftover)
    return the actual size
    heap_insert(leftover)

    if no find:
        get more memory system (sbrk)
        split that, and the rest to heap

* MINheap based on size of chunk -- sorted from smallest to largest
* small chunks are more frequently requested

* what do we do when the heap is empty?
* what do we do when the user requests a larger thing than is in the heap

# FREE

* deallocating memory
* user gives us memory back 
*add that into what we know about (and user is supposed to forget about)


## sbrk()

* Ask linux for a HUGE chunk of memory
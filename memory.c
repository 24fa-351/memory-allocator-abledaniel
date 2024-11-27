#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define HEAP_SIZE 1024 * 1024 

typedef struct Block {
    size_t size;
    int free;
    struct Block* next;
} Block;

static char heap[HEAP_SIZE];
static Block* free_list = NULL;
static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void initialize() {
    free_list = (Block*)heap;
    free_list->size = HEAP_SIZE - sizeof(Block);
    free_list->free = 1;
    free_list->next = NULL;
}

void* malloc(size_t size) {
    pthread_mutex_lock(&lock);

    if (!free_list) {
        initialize();
    }

    size = (size + 7) & ~7;
    Block* current = free_list;

    while (current && !(current->free && current->size >= size)) {
        current = current->next;
    }

    if (!current) {
        pthread_mutex_unlock(&lock);
        return NULL;
    }

    if (current->size > size + sizeof(Block)) {
        Block* new_block = (Block*)((char*)current + sizeof(Block) + size);
        new_block->size = current->size - size - sizeof(Block);
        new_block->free = 1;
        new_block->next = current->next;

        current->size = size;
        current->next = new_block;
    }

    current->free = 0;
    pthread_mutex_unlock(&lock);
    return (void*)(current + 1);
}

void free(void* ptr) {
    if (!ptr) return;

    pthread_mutex_lock(&lock);

    Block* block = (Block*)ptr - 1;
    block->free = 1;

    Block* current = free_list;
    while (current) {
        if (current->free && current->next && current->next->free) {
            current->size += current->next->size + sizeof(Block);
            current->next = current->next->next;
        }
        current = current->next;
    }

    pthread_mutex_unlock(&lock);
}

void* realloc(void* ptr, size_t size) {
    if (!ptr) {
        return malloc(size);
    }
    Block* block = (Block*)ptr - 1;

    if (block->size >= size) {
        return ptr;
    }

    void* new_ptr = malloc(size);
    if (new_ptr) {
        memcpy(new_ptr, ptr, block->size);
        free(ptr);
    }
    return new_ptr;
}

#include "memory.h"
#include <stdio.h>

void test_small_alloc() {
    void* ptr = malloc(32);
    if (ptr) {
        printf("Test small alloc: PASS\n");
        free(ptr);
    } else {
        printf("Test small alloc: FAIL\n");
    }
}

int main() {
    test_small_alloc();
    return 0;
}

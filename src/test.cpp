#include <stdio.h>
#include <stdlib.h>

int main() {
    int* ptr = (int*)malloc(sizeof(int) * 5);
    if (ptr == NULL) {
        printf("Memory allocation failed\n");
    } else {
        printf("Memory allocated successfully\n");
        free(ptr);
    }
    return 0;
}

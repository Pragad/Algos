#include <stdio.h>
#include <stdlib.h> // malloc

struct Node {
    int value;
    struct Node* next;
};

int main() {
    printf("Hello World\n");
    int* a = (int *)malloc(sizeof(int) * 5);
    if (a != NULL) {
        a[0] = 1;
        a[1] = 2;
        a[2] = 3;
        a[3] = 4;
        a[4] = 5;
    } else {
        return 0;
    }
    for (int i = 0; i < 5; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    free(a);
    return 0;
}

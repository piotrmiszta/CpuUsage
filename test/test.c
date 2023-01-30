#include <stdio.h>
#include "../include/Queque.h"
#include <assert.h>
#include <stdlib.h>
#define MAX 10000
int main() {

    Node *head = malloc(sizeof(Node));
    head->data = NULL;
    head->next = NULL;

    //pushing value to Que
    for (int i = 0; i < MAX; i++) {
        double *x = malloc(sizeof(double));
        *x = (double) i;
        pushBack(head, x);
    }
    int z = elements(head);
    assert(z == MAX);
    //getting value from que
    for (int i = 0; i < MAX; i++) {
        double *x = (double *) (pop(&head));
        assert(*x == i);
        free(x);
    }
    free(head);
    head = NULL;
    int y = elements(head);
    assert(y == 0);
    printf("OK\n");
    return 0;

}

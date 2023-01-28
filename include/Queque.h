//
// Created by programowanie on 27.01.23.
//

#ifndef PROCSTAT_QUEQUE_H
#define PROCSTAT_QUEQUE_H
#include "defs.h"

typedef struct Node{

    struct Node* next;
    void* data;

}Node;

void pushBackCpu(Node* head, void* data);
void* popFirstCpu(Node** head);
void printAll(Node* head);
int elements(Node* head);

#endif //PROCSTAT_QUEQUE_H

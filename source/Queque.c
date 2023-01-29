///
// Created by programowanie on 27.01.23.
//
#include "../include/Queque.h"
#include <stdio.h>
#include <stdlib.h>
void pushBack(Node* head, void* data) {
    if(head == NULL) {
        perror("head is null pointer");
        return;
    }
    if(head->data == NULL) {
        head->data = data;
        return;
    }
    Node* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    Node * newNode = malloc(sizeof(Node));
    newNode->data = data;
    temp->next = newNode;
    newNode->next = NULL;
}
void* pop(Node** head) {
    if(head == NULL) {
        return NULL;
    }
    Node* temp = (*head);
    if(temp == NULL) {
        return NULL;
    }
    if(temp ->data == NULL) {
        return NULL;
    }
    if(temp ->next == NULL) {
        return temp->data;
    }
    temp = (*head)->next;
    void* retVal = ((*head)->data);
    free((*head));
    (*head) = temp;
    return retVal;
}
void printAll(Node* head) {
    while(1) {
        int y = (*(int*)(head->data));
        printf("%d\n", y);
        if(head->next == NULL) {
            return;
        }
        else {
            head = head->next;
        }
    }
}

int elements(Node* _head) {
    Node* head = _head;
    if(head == NULL) {return 0;}
    int i = 0;
    while(head->next != NULL) {
        i++;
    }
    return i;
}
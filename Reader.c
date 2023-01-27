//
// Created by programowanie on 27.01.23.
//
#include "Reader.h"
#include "unistd.h"
void* readerThread(void* args) {
    Data* data = (Data*)(args);
    while (1) {
        int x = rand() % 100;
        sem_wait(&data->semReadEmpty);
        pthread_mutex_lock(&data->mutexReadBuffer);
        pushBackCpu(data->readerTab, (void*)(&x));
        data->count++;
        pthread_mutex_unlock(&data->mutexReadBuffer);
        sem_post(&data->semReadFull);
    }
    return NULL;
}
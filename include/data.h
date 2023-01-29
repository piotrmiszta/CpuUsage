//
// Created by programowanie on 27.01.23.
//

#ifndef STATCPU_DATA_H
#define STATCPU_DATA_H
#include <pthread.h>
#include <semaphore.h>
#include "Queque.h"
#include "defs.h"


typedef struct Data {
    sem_t semReadEmpty;
    sem_t semReadFull;
    sem_t semAnalyzeEmpty;
    sem_t semAnalyzeFull;
    sem_t semLogEmpty;
    sem_t semLogFull;

    pthread_mutex_t mutexReadBuffer;
    pthread_mutex_t mutexAnalyzeBuffer;
    pthread_mutex_t mutexLogBuffer;

    Node* readerTab; //buffer for reading values
    Node* analyzerTab;  //buffer for cpu percent

    void* logger;
    int amountCpu;
    int end, readerEnd, analyzerEnd, printerEnd,loggerEnd;
}Data;
Data* createData();
void closeData(Data* data);
#endif //STATCPU_DATA_H

//
// Created by programowanie on 27.01.23.
//

#ifndef STATCPU_DATA_H
#define STATCPU_DATA_H
#include <pthread.h>
#include <semaphore.h>
#include "Queque.h"
#define SUCCESS     (0)
#define FAIL        (-1)
#define E_FILE      (-2) //Error file
#define E_MALL      (-3) //Error malloc
#define EOC         (-4) //End of cpus
#define E_ARG       (-5)

typedef struct Data {
    sem_t semReadEmpty;
    sem_t semReadFull;
    sem_t semAnalyzeEmpty;
    sem_t semAnalyzeFull;

    pthread_mutex_t mutexReadBuffer;
    pthread_mutex_t mutexAnalyzeBuffer;

    Node* readerTab; //buffer for reading values
    Node* analyzerTab;  //buffer for cpu percent

    int buffer[10];
    int count;

    int end;
}Data;

#endif //STATCPU_DATA_H

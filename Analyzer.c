//
// Created by programowanie on 27.01.23.
//

#include "Analyzer.h"
#include "unistd.h"

void* analyzerThread(void* args) {
    Data* data = (Data*)(args);
    int y = -1;
    int z = -1;
    while (1) {
        // Remove from the buffer
        sleep(1);
        sem_wait(&data->semReadFull);
        pthread_mutex_lock(&data->mutexReadBuffer);
        y = *((int*)(popFirstCpu(&data->readerTab)));
        data->count--;
        pthread_mutex_unlock(&data->mutexReadBuffer);
        sem_post(&data->semReadEmpty);
        if(z == -1) {
            z = y;
            y = -1;
        }
        else { //%cpu
            int k = z*y;
            sem_wait(&data->semAnalyzeEmpty);
            pthread_mutex_lock(&data->mutexAnalyzeBuffer);
            pushBackCpu(data->analyzerTab, (void*)(&k));
            pthread_mutex_unlock(&data->mutexAnalyzeBuffer);
            sem_post(&data->semAnalyzeFull);
            //free(z)
            z = y;
            y = -1;
        }

    }
    return NULL;
}
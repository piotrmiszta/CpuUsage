//
// Created by programowanie on 27.01.23.
//

#include "Printer.h"
void* printerThread(void* arg) {
    Data* data = (Data*)(arg);
    while(1) {

        sem_wait(&data->semAnalyzeFull);
        pthread_mutex_lock(&data->mutexAnalyzeBuffer);
        int cpuUsage = getDouble(data);
        pthread_mutex_unlock(&data->mutexAnalyzeBuffer);
        sem_post(&data->semAnalyzeEmpty);

        fprintf(stdout, "%d\n", cpuUsage);
    }
    return NULL;
}

int getDouble(void* arg) {
    Data* data = (void*)(arg);
    return (*(int*)(popFirstCpu(&data->analyzerTab)));
}

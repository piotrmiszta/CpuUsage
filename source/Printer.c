//
// Created by programowanie on 27.01.23.
//

#include "../include/Printer.h"

void* printerThread(void* arg) {
    Data* data = (Data*)(arg);
    while(1) {
        sem_wait(&data->semAnalyzeFull);
        if(data->analyzerEnd == 1)
            break;
        pthread_mutex_lock(&data->mutexAnalyzeBuffer);
        double* cpuUsage = getDouble(data);
        LOG_DEBUG(data, "cpu usage is: ", cpuUsage, PDOUBLE);
        pthread_mutex_unlock(&data->mutexAnalyzeBuffer);
        sem_post(&data->semAnalyzeEmpty);
#ifdef DEBUG
        FILE* file;
        file= fopen("test.txt", "a");
#endif
        for(int i = 0; i < data->amountCpu-1; i++) {
            fprintf(stdout, "cpu%d: %f\n",i , cpuUsage[i]);
        }
#ifdef DEBUG
        fclose(file);
#endif

    }
    sem_post(&data->semLogFull);
    data->printerEnd = 1;
    return NULL;
}

double* getDouble(void* arg) {
    Data* data = (void*)(arg);
    return (double*)(pop(&data->analyzerTab));
}

//
// Created by programowanie on 27.01.23.
//

#include "../include/Printer.h"

void* printerThread(void* arg) {
    Data* data = (Data*)(arg);
    while(1) {
        sem_wait(&data->semAnalyzeFull);
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
    return NULL;
}

double* getDouble(void* arg) {
    Data* data = (void*)(arg);
    return (double*)(popFirstCpu(&data->analyzerTab));
}

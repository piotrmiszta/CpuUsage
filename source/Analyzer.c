//
// Created by programowanie on 27.01.23.
//

#include "../include/Analyzer.h"
#include "unistd.h"
void* analyzerThread(void* args) {
    Data* data = (Data*)(args);
    cpu* prev = NULL;
    cpu* this = NULL;
    while (1) {
        // Remove from the buffer

        //sleep(1);
        sem_wait(&data->semReadFull);
        pthread_mutex_lock(&data->mutexReadBuffer);
        this = (cpu*)(popFirstCpu(&data->readerTab));
        LOG_DEBUG(data, "Get from READER is cpu: ", this, CPU);
        pthread_mutex_unlock(&data->mutexReadBuffer);
        sem_post(&data->semReadEmpty);
        //sleep(2);
        if(prev == NULL) {
            prev = this;
            this = NULL;
            LOG_DEBUG(data, "IF CASE PREV NULL", NULL, NONE);
        }
        else { //%cpu
            double* k = getPercent(prev, this);
            sem_wait(&data->semAnalyzeEmpty);
            pthread_mutex_lock(&data->mutexAnalyzeBuffer);
            pushBackCpu(data->analyzerTab, (void*)(k));
            pthread_mutex_unlock(&data->mutexAnalyzeBuffer);
            sem_post(&data->semAnalyzeFull);
            //free(prev);
            LOG_DEBUG(data, "else case: ", this, CPU);
            LOG_DEBUG(data, "else case: ", prev, CPU);
            prev = this;
            this = NULL;
        }

    }
    return NULL;
}

double* getPercent(cpu* prev, cpu* next) {
    double* tab = malloc(sizeof(double ) *prev->size);
    for(int i = 0; i < prev->size; i++) {
        ui prevIdle = prev->tab[i].idle+prev->tab[i].iowait;
        ui prevNonIdle = prev->tab[i].user + prev->tab[i].nice + prev->tab[i].system + prev->tab[i].irq + prev->tab[i].steal;
        ui idle = next->tab[i].idle+next->tab[i].iowait;
        ui nonIdle = next->tab[i].user + next->tab[i].nice + next->tab[i].system + next->tab[i].irq + next->tab[i].steal;
        ui prevTotal = prevIdle + prevNonIdle;
        ui total = idle+nonIdle;
        double totald = (double)total - (double)prevTotal;
        double idled = (double)idle-(double)prevIdle;
        double cpuUsage;
            cpuUsage = (1000*(totald - idled) / (totald) + 1)/10;

        tab[i] = cpuUsage;
    }

    return tab;
}












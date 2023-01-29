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
        sem_wait(&data->semReadFull);
        if(data->readerEnd == 1)
            break;
        pthread_mutex_lock(&data->mutexReadBuffer);
        this = (cpu*)(pop(&data->readerTab));
        LOG_DEBUG(data, "Get from READER is cpu: ", this, CPU);
        pthread_mutex_unlock(&data->mutexReadBuffer);
        sem_post(&data->semReadEmpty);
        if(prev == NULL) {
            prev = this;
            this = NULL;
            LOG_DEBUG(data, "IF CASE PREV NULL", NULL, NONE);
        }
        else {
            double* k = getPercent(prev, this);
            if(k != NULL) {
                sem_wait(&data->semAnalyzeEmpty);
                if(data->readerEnd == 1) {
                    break;
                }
                pthread_mutex_lock(&data->mutexAnalyzeBuffer);
                pushBack(data->analyzerTab, (void*)(k));
                pthread_mutex_unlock(&data->mutexAnalyzeBuffer);
                sem_post(&data->semAnalyzeFull);
                LOG_DEBUG(data, "else case: ", this, CPU);
                LOG_DEBUG(data, "else case: ", prev, CPU);
                cpu *temp = prev;
                freeCpu((void**)&temp);
                prev = this;
                this = NULL;
            }

        }
    }
    data->analyzerEnd = 1;
    sem_post(&data->semAnalyzeFull);
    return NULL;
}

double* getPercent(cpu* prev, cpu* next) {
    int k = 0;
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
        if(totald != 0) {
            cpuUsage = (1000*(totald - idled) / (totald) + 1)/10;
            tab[i] = cpuUsage;
            k = 1;
        }
    }
    if(k == 0) {
        free(tab);
        tab=NULL;
        return NULL;
    }
    else{
        return tab;
    }
}












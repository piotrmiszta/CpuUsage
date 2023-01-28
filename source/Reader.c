//
// Created by programowanie on 27.01.23.
//
#include "../include/Reader.h"
#include "unistd.h"
void* readerThread(void* args) {
    Data* data = (Data*)(args);
    while (1) {
        cpu* _cpu = malloc(sizeof (cpu));
        //sleep(1);
        getStats(_cpu, data->amountCpu);
        LOG_DEBUG(data,"Readed cpu is: ", _cpu, CPU);
        sem_wait(&data->semReadEmpty);
        pthread_mutex_lock(&data->mutexReadBuffer);
        pushBackCpu(data->readerTab, (void*)(_cpu));
        pthread_mutex_unlock(&data->mutexReadBuffer);
        sem_post(&data->semReadFull);
    }
    return NULL;
}
int readAmountOfCpu() {
    int amount = 0;
    FILE* file;
    file = fopen("/proc/stat", "r");
    if(file == NULL) {
        fprintf(stderr, "Cannot open /proc/stat %s", __func__ );
        return E_FILE;
    }
    char buf[255];

    while(1) {
        fscanf(file, "%s", buf);
        if (buf[0] != 'c') {
            return amount;
        }
        else{
            amount++;
        }
        int temp;
        for(int i = 0; i < 10; i++) {
            int valRead = fscanf(file, "%d", &temp);
            if (valRead == EOF)
                return E_FILE;
        }
    }
}
int getOneCpu(oneCpu* stat, FILE* file) {
    fscanf(file, "%s", stat->name);
    if(stat->name[0] != 'c') {
        return EOC;
    }
    int valRead = fscanf(file, "%lld %lld %lld %lld %lld %lld %lld %lld %lld %lld", &stat->user, &stat->nice,&stat->system,
                         &stat->idle, &stat->iowait ,&stat->irq, &stat->softirq, &stat->steal, &stat->guest, &stat->guest_nice);
    if(valRead == EOF)
        return E_FILE;
    else
        return SUCCESS;
}

int getStats(cpu* cpu, int cpuAmount) {
    if(cpu == NULL)
        return E_MALL;
    FILE* file = fopen("/proc/stat", "r");
    if(file == NULL) {
        perror("Cant open /proc/stat file\n");
        return E_FILE;
    }

    cpu->size = cpuAmount - 1;
    cpu->tab = malloc((cpuAmount - 1) * sizeof(oneCpu));

    if(getOneCpu(&(cpu->cpu0), file) != 0 )
        return -1;
    if(cpu->tab == NULL) {
        return E_MALL;
    }
    for(int i = 0; i < (cpuAmount-1); i++) {
        getOneCpu(&(cpu->tab[i]), file);
    }
    fclose(file);
    return SUCCESS;
}
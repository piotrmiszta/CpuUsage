//
// Created by programowanie on 27.01.23.
//

#ifndef STATCPU_READER_H
#define STATCPU_READER_H
#include "data.h"
#include <stdlib.h>
#include <stdio.h>
#include "defs.h"
#include "Logger.h"
typedef struct oneCpu{
    char name[7]; // CPUXX
    ui user;    //process executing in user mode
    ui nice;    //process executing with niced priority
    ui system;  //process in kernel mode
    ui idle;    //idling
    ui iowait;  //IO requests
    ui irq;     //interrupt request
    ui softirq; //servicing softirq
    ui steal;   //virtual envi
    ui guest;   //virtual CPU
    ui guest_nice;  //virtual CPU with niced priority
}oneCpu;

typedef struct cpu {

    oneCpu cpu0;
    oneCpu* tab;
    size_t size;

}cpu;

void* readerThread(void* args);
int readAmountOfCpu();
int getOneCpu(oneCpu* stat, FILE* file);
int getStats(cpu* cpu, int amount);

#endif //STATCPU_READER_H

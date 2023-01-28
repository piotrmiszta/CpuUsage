//
// Created by programowanie on 27.01.23.
//

#ifndef STATCPU_ANALYZER_H
#define STATCPU_ANALYZER_H
#include "data.h"
#include <stdlib.h>
#include <stdio.h>
#include "Reader.h"
#include "defs.h"
#include "Logger.h"
void* analyzerThread(void* args);
double* getPercent(cpu* prev, cpu* next);

#endif //STATCPU_ANALYZER_H

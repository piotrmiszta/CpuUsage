//
// Created by programowanie on 27.01.23.
//

#ifndef STATCPU_PRINTER_H
#define STATCPU_PRINTER_H
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "defs.h"
#include "Logger.h"
void* printerThread(void* arg);

double* getDouble(void* arg);



#endif //STATCPU_PRINTER_H

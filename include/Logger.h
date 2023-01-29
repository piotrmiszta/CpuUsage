//
// Created by programowanie on 28.01.23.
//

#ifndef STATCPU_LOGGER_H
#define STATCPU_LOGGER_H
#include <stdio.h>
#include <stdlib.h>
#include "defs.h"
#include "data.h"
#include <stdarg.h>
#include <time.h>
#include <string.h>
#include "Reader.h"
typedef enum LogType{
    DEBUG,
    INFO,
    WARNING,
    ERROR
}LogType;
typedef enum valType{
    INT,
    DOUBLE,
    CPU,
    PDOUBLE,
    NONE
}valType;
typedef struct Logger{
    char* msg;
    void* arg;
    valType valtype;
    LogType type;
    char func[100];
    int line;
    FILE* file;
}Logger;
int loggerInit(const char* filename, Logger* log);

int logger(Data* data, LogType type, const char* func, int line, char* msg, void* arg, valType val);
int loggerPrint(Data* data);
int printTime(FILE* file);
int closeLogger(Data* data);
void* loggerThread(void* arg);
#define LOG_DEBUG(data, msg, arg, val) logger(data, DEBUG, __FUNCTION__, __LINE__, msg, arg, val);
#endif //STATCPU_LOGGER_H

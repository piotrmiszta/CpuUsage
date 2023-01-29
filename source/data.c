//
// Created by programowanie on 27.01.23.
//

#include "../include/data.h"
#include "../include/Reader.h"
#include "../include/Analyzer.h"
#include <stdlib.h>
Data* createData() {
    Data *data = malloc(sizeof(Data));
    pthread_mutex_init(&data->mutexReadBuffer, NULL);
    pthread_mutex_init(&data->mutexAnalyzeBuffer, NULL);
    pthread_mutex_init(&data->mutexLogBuffer, NULL);

    sem_init(&data->semReadEmpty, 0, 10);
    sem_init(&data->semReadFull, 0, 0);
    sem_init(&data->semAnalyzeEmpty, 0, 10);
    sem_init(&data->semAnalyzeFull, 0, 0);
    sem_init(&data->semLogEmpty, 0, 1);
    sem_init(&data->semLogFull, 0, 0);

    data->readerTab = malloc(sizeof (Node));
    data->readerTab->data = NULL;
    data->readerTab->next = NULL;
    data->analyzerTab = malloc(sizeof(Node));
    data->analyzerTab->data = NULL;
    data->analyzerTab->next = NULL;

    data->end = 0;
    data->readerEnd = 0;
    data->loggerEnd = 0;
    data->printerEnd = 0;
    data->analyzerEnd = 0;

    data->amountCpu = readAmountOfCpu();
    data->logger = malloc(sizeof(Logger));
    loggerInit("log.txt", data->logger);
    return data;
}
void closeData(Data* data) {
    //free(data->readerTab);
   // free(data->analyzerTab);



    sem_destroy(&data->semReadEmpty);
    sem_destroy(&data->semReadFull);
    sem_destroy(&data->semAnalyzeEmpty);
    sem_destroy(&data->semAnalyzeFull);

    pthread_mutex_destroy(&data->mutexReadBuffer);
    pthread_mutex_destroy(&data->mutexAnalyzeBuffer);

    //free(data);
}
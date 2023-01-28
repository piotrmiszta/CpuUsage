#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include "../include/data.h"
#include "../include/Reader.h"
#include "../include/Analyzer.h"
#include "../include/Printer.h"
#include "../include/Logger.h"
int main(int argc, char* argv[]) {

    srand(time(NULL));

    Data* data = malloc(sizeof(Data));
    data->readerTab = malloc(sizeof (Node));
    data->readerTab->data = NULL;
    data->analyzerTab = malloc(sizeof(Node));
    data->analyzerTab->data = NULL;
    data->end = 0;
    data->amountCpu = readAmountOfCpu();
    data->logger = malloc(sizeof(Logger));
    loggerInit("log.txt", data->logger);
    pthread_t th, th2, th3, th4;
    pthread_mutex_init(&data->mutexReadBuffer, NULL);
    pthread_mutex_init(&data->mutexAnalyzeBuffer, NULL);
    pthread_mutex_init(&data->mutexLogBuffer, NULL);

    sem_init(&data->semReadEmpty, 0, 10);
    sem_init(&data->semReadFull, 0, 0);
    sem_init(&data->semAnalyzeEmpty, 0, 10);
    sem_init(&data->semAnalyzeFull, 0, 0);
    sem_init(&data->semLogEmpty, 0, 1);
    sem_init(&data->semLogFull, 0, 0);


    pthread_create(&th, NULL, readerThread, data);
    pthread_create(&th2, NULL, analyzerThread, data);
    pthread_create(&th3, NULL, printerThread, data);
    pthread_create(&th4, NULL, loggerThread, data);

    sleep(2);
    data->end = 1;
    pthread_join(th, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);


    sem_destroy(&data->semReadEmpty);
    sem_destroy(&data->semReadFull);
    sem_destroy(&data->semAnalyzeEmpty);
    sem_destroy(&data->semAnalyzeFull);

    pthread_mutex_destroy(&data->mutexReadBuffer);
    pthread_mutex_destroy(&data->mutexAnalyzeBuffer);

    free(data);
    return 0;
}
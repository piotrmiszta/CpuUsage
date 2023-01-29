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
#include <signal.h>

Data* data;
void term(int sig) {
    data->end = 1;
    while(data->printerEnd != 1 && data->loggerEnd != 1 && data->readerEnd != 1 && data->analyzerEnd != 1) {}
    closeData(data);


}
int main(int argc, char* argv[]) {
    struct sigaction action;
    memset(&action, 0 , sizeof (struct sigaction));
    action.sa_handler = term;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);

    data=createData();

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
    sleep(10);
    term(1);


    pthread_join(th, NULL);
    pthread_join(th2, NULL);
    pthread_join(th3, NULL);
    pthread_join(th4, NULL);
    closeData(data);


    return 0;
}
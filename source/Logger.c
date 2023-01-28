#include "../include/Logger.h"
int loggerInit(const char* filename, Logger* log) {
    if(log == NULL){
        fprintf(stderr, "Cant open %s in %s", filename, __FUNCTION__ );
        return E_ARG;
    }
    log->file = fopen(filename, "w");
#define DEBUGa
#ifdef DEBUGa
    fclose(log->file);
#endif
    return SUCCESS;
}
int loggerPrint(Data* data) {

    Logger *log = (Logger*)(data->logger);
#ifdef DEBUGa
    log->file = fopen("log.txt", "a");
#endif
    if(log->file == NULL) {
        fprintf(stderr, "File is null pointer in %s", __FUNCTION__ );
        return E_ARG;
    }

    switch (log->type) {
        case(DEBUG):
            fprintf(log->file, "[DEBUG] ");
            break;
        case(INFO):
            fprintf(log->file, "[INFO] ");
            break;
        case(WARNING):
            fprintf(log->file, "[WARNING] ");
            break;
        case(ERROR):
            fprintf(log->file, "[ERROR] ");
            break;
        default:
            fprintf(log->file, "[NONE] ");
            break;
    }
    printTime(log->file);
    fprintf(log->file, "%s ", log->func );
    fprintf(log->file, "%d ", log->line );
    switch (log->valtype) {
        case (INT):
            fprintf(log->file, log->msg, (*(int*)(log->arg)));
            break;
        case(DOUBLE):
            fprintf(log->file, log->msg, (*(double*)(log->arg)));
            break;
        case(PDOUBLE):
            fprintf(log->file, "%s ",log->msg);
            for(int i = 0; i < data->amountCpu; i++){
                fprintf(log->file, "%f ", ((double*)(log->arg))[i]);
            }
            break;
        case(CPU):
            fprintf(log->file, "%s \n", log->msg);
            cpu* cpus = log->arg;
            if(cpus == NULL){
                fprintf(log->file, "NULL");
            }
            for(int i = 0; i < cpus->size; i++) {
                fprintf(log->file, "%s %lld %lld %lld %lld %lld %lld %lld %lld %lld %lld\n", cpus->tab[i].name, cpus->tab[i].user, cpus->tab[i].nice, cpus->tab[i].system,
                        cpus->tab[i].idle, cpus->tab[i].iowait , cpus->tab[i].irq, cpus->tab[i].softirq, cpus->tab[i].steal, cpus->tab[i].guest, cpus->tab[i].guest_nice);
            }
            break;
        case(NONE):
            fprintf(log->file, "%s ", log->msg);
            break;
        default:
            fprintf(log->file, "%s", log->msg);
            break;
    }
    fprintf(log->file, "\n");
#ifdef DEBUGa
    fclose(log->file);
#endif
    return SUCCESS;
}

int logger(Data* data, LogType type, const char* func, int line, char* msg, void* arg, valType val) {
    Logger *log = (Logger*)(data->logger);
    sem_wait(&data->semLogEmpty);
    pthread_mutex_lock(&data->mutexLogBuffer);
    log->type = type;
    strcpy(log->func , func);
    log->line = line;
    log->msg = msg;
    log->arg = arg;
    log->valtype = val;
    pthread_mutex_unlock(&data->mutexLogBuffer);
    sem_post(&data->semLogFull);
    return SUCCESS;
}
int printTime(FILE* file) {
    time_t t = time(NULL);
    struct tm *tm  = localtime(&t);
    const char *d_time = asctime(tm);
    const char *datetime = strchr(d_time, '\n');
    int length = datetime - d_time;

    char *modified_date = malloc(length + 1);
    strncpy(modified_date, d_time, length);
    modified_date[length] = '\0';
    fprintf(file, "%s ", modified_date);

    free(modified_date);
    return SUCCESS;
}
int closeLogger(Data* data) {
    Logger* log = data->logger;
    fclose(log->file);
    return SUCCESS;
}
void* loggerThread(void* arg) {
    Data* data = (Data*)(arg);
    while(1) {
        sem_wait(&data->semLogFull);
        pthread_mutex_lock(&data->mutexLogBuffer);
        loggerPrint(data);
        pthread_mutex_unlock(&data->mutexLogBuffer);
        sem_post(&data->semLogEmpty);
    }
}
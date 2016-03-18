#include "pipe.h"
#include "logger.h"

#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

char *gtkPipePathOutput = "/tmp/baymax-gtk-output";
char *gtkPipePathInput = "/tmp/baymax-gtk";

char *senderPipePathOutput = "/tmp/baymax-sender-output";
char *senderPipePathInput = "/tmp/baymax-sender";

char *loggerPipePathOutput = "/tmp/baymax-logger-output";
char *loggerPipePathInput = "/tmp/baymax-logger";

char *connectionPipePathOutput = "/tmp/baymax-connection-output";
char *connectionPipePathInput = "/tmp/baymax-connection";

char *n = NULL;

pthread_t gtkReaderThreadId;
pthread_t senderReaderThreadId;
pthread_t loggerReaderThreadId;
pthread_t connectionReaderThreadId;

bool runningGtkReaderRunning = 1;
bool runningSenderReaderRunning = 1;
bool runningLoggerReaderRunning = 1;
bool runningConnectionReaderRunning = 1;

void createGtkPipe() {
    int err;
    mkfifo(gtkPipePathInput, 0666);
    mkfifo(gtkPipePathOutput, 0666);
    err = pthread_create(&gtkReaderThreadId, NULL, &gtkOutputReader, NULL);
    if (err != 0) {
        printAsManager("Cant create gtk pipe :((!");
    }
}

void createSenderPipe() {
    int err;
    mkfifo(senderPipePathInput, 0666);
    mkfifo(senderPipePathOutput, 0666);
    err = pthread_create(&senderReaderThreadId, NULL, &senderOutputReader, NULL);
    if (err != 0) {
        printAsManager("Cant create sender pipe :((!");
    }
}

void createLoggerPipe() {
    int err;
    mkfifo(loggerPipePathInput, 0666);
    mkfifo(loggerPipePathOutput, 0666);
    err = pthread_create(&loggerReaderThreadId, NULL, &loggerOutputReader, NULL);
    if (err != 0) {
        printAsManager("Cant create logger pipe :((!");
    }
}

void createConnectionPipe() {
    int err;
    mkfifo(connectionPipePathInput, 0666);
    mkfifo(connectionPipePathOutput, 0666);
    err = pthread_create(&connectionReaderThreadId, NULL, &connectionOutputReader, NULL);
    if (err != 0) {
        printAsManager("Cant create connection pipe :((!");
    } 
}

void deleteGtkPipe() {
    runningGtkReaderRunning = 0;
    unlink("/tmp/baymax-gtk-output");
    unlink("/tmp/baymax-gtk");
}

void deleteSenderPipe() {
    runningSenderReaderRunning = 0;
    unlink("/tmp/baymax-sender-output");
    unlink("/tmp/baymax-sender");
}

void deleteLoggerPipe() {
    runningLoggerReaderRunning = 0;
    unlink("/tmp/baymax-logger-output");
    unlink("/tmp/baymax-logger");
}

void deleteConnectionPipe() {
    runningConnectionReaderRunning = 0;
    unlink("/tmp/baymax-connection-output");
    unlink("/tmp/baymax-connection");
}

char *getGtkInputPipe() {
    return gtkPipePathInput;
}

char *getGtkOutputPipe() {
    return gtkPipePathOutput;
}

char *getSenderInputPipe() {
    return senderPipePathInput;
}

char *getSenderOutputPipe() {  
    return senderPipePathOutput;
}

char *getLoggerInputPipe() {   
    return loggerPipePathInput;
}

char *getLoggerOutputPipe() {
    return loggerPipePathOutput;
}

char *getConnectionInputPipe() {
    return connectionPipePathInput;
}

char *getConnectionOutputPipe() {
    return connectionPipePathOutput;
}

void* gtkOutputReader(void* data) {
    int fd;
    char buf[100];
    fd = open(gtkPipePathOutput, O_RDONLY);
    read(fd, buf, 100);
    printAsGtk(buf);
}

void* senderOutputReader(void* data) {
    int fd;
    char buf[100];
    fd = open(senderPipePathOutput, O_RDONLY);
    read(fd, buf, 100);
    printAsSender(buf);
}

void* loggerOutputReader(void* data) {  
    int fd;
    char buf[100];
    fd = open(loggerPipePathOutput, O_RDONLY);
    read(fd, buf, 100);
    printAsLogger(buf);
}

void* connectionOutputReader(void* data) {
    int fd;
    char buf[100];
    fd = open(connectionPipePathOutput, O_RDONLY);
    read(fd, buf, 100);
    printAsConnection(buf);
}

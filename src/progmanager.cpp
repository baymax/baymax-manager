#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "progmanager.h"
#include "logger.h"
#include "pipe.h"

void startAllModules() {
    startUiModule();
    startSenderModule();
    startLoggerModule();
    startConnectionModule();
}

void startUiModule() {
    char text[50];
    createGtkPipe();
    snprintf(text, 50, "baymax-gtk > %s &", getGtkOutputPipe());
    system(text);
    printAsManager("baymax-gtk module started!!");
}

void startSenderModule() {
    char text[50];
    createSenderPipe();
    snprintf(text, 50, "baymax-sender > %s &", getSenderOutputPipe());
    system(text);
    printAsManager("baymax-sender module started!!");    
}

void startLoggerModule() {
    char text[50];
    createLoggerPipe();
    snprintf(text, 50, "baymax-logger > %s &", getLoggerOutputPipe());
    system(text);
    printAsManager("baymax-logger module started!!");    
}

void startConnectionModule() {
    char text[50];
    createConnectionPipe();
    snprintf(text, 50, "baymax-connection > %s &", getConnectionOutputPipe());
    system(text);
    printAsManager("baymax-connection module started!!");   
}

void stopAllModules() {
    stopUiModule();
    stopSenderModule();
    stopLoggerModule();
    stopConnectionModule();
}

void stopUiModule() {
    printAsManager("Stopping baymax-gtk module...");
    char text[50];
    snprintf(text, 50, "kill %s", getPidOfProcess("baymax-gtk"));
    system(text);
    printAsManager("baymax-gtk module stopped");
    deleteGtkPipe();
}

void stopSenderModule() {
    printAsManager("Stopping baymax-sender module...");
    char text[50];
    snprintf(text, 50, "kill %s", getPidOfProcess("baymax-sender"));
    system(text);
    printAsManager("baymax-sender module stopped");    
    deleteSenderPipe();
}

void stopLoggerModule() {
    printAsManager("Stopping baymax-logger module...");
    char text[50];
    snprintf(text, 50, "kill %s", getPidOfProcess("baymax-logger"));
    system(text);
    printAsManager("baymax-logger module stopped");   
    deleteLoggerPipe();
}

void stopConnectionModule() {
    printAsManager("Stopping baymax-connection module...");
    char text[50];
    snprintf(text, 50, "kill %s", getPidOfProcess("baymax-connection"));
    system(text);
    printAsManager("baymax-connection module stopped");
    deleteConnectionPipe();   
}

char* getPidOfProcess(const char *programName) {
    int fd;
    char text[50];
    char buf[20];
    char *getPidPathOutput = "/tmp/baymax-getpid";
    mkfifo(getPidPathOutput , 0666);
    snprintf(text, 50, "pidof %s > %s &", programName, getPidPathOutput);
    system(text);
    fd = open(getPidPathOutput, O_RDONLY);
    read(fd, buf, 20);
    return buf;
    
}
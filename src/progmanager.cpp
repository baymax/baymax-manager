#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "progmanager.h"
#include "logger.h"
#include "pipe.h"


unsigned char gtkRunning = 0;
unsigned char senderRunning = 0;
unsigned char loggerRunning = 0;
unsigned char connectionRunning = 0;
unsigned char readerRunning = 0;


void startAllModules() {
    startUiModule();
    startSenderModule();
    startLoggerModule();
    startConnectionModule();
    startReaderModule();
}

void startUiModule() {
    char text[100];
    createGtkPipe();
    snprintf(text, 100, "baymax-gtk > %s < %s 2> %s &", gtkPipePathOutput, gtkPipePathInput, gtkPipePathError);
    system(text);
    openGtkOutputPipe();
    openGtkErrorPipe();
    printAsManager("baymax-gtk module started!");
}

void startSenderModule() {
    char text[100];
    createSenderPipe();
    snprintf(text, 100, "baymax-sender > %s < %s &", senderPipePathOutput, senderPipePathInput);
    system(text);
    printAsManager("baymax-sender module started!!");    
}

void startLoggerModule() {
    char text[100];
    createLoggerPipe();
    snprintf(text, 100, "baymax-logger > %s < %s &", loggerPipePathOutput, loggerPipePathInput);
    system(text);
    printAsManager("baymax-logger module started!!");    
}

void startConnectionModule() {
    char text[100];
    createConnectionPipe();
    snprintf(text, 100, "baymax-connection > %s < %s &", connectionPipePathOutput,connectionPipePathInput);
    system(text);
    printAsManager("baymax-connection module started!!");   
}

void startReaderModule() {
    char text[100];
    createReaderPipe();
    snprintf(text, 100, "baymax-reader > %s 2> %s &", readerPipePathOutput, readerPipePathError);
    //snprintf(text, 100, "baymax-reader > %s < %s 2> %s &", readerPipePathOutput, readerPipePathInput, readerPipePathError);
    system(text);
    openReaderOutputPipe();
    openReaderErrorPipe(); 
    printAsManager("baymax-reader module started!!");     
}

int stopAllModules() {
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
    //kill(itoa(getPidOfProcess("baymax-gtk")), SIGINT);
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

void stopReaderModule() {
    printAsManager("Stopping baymax-reader module...");
    char text[50];
    snprintf(text, 50, "kill %s", getPidOfProcess("baymax-reader"));
    system(text);
    //kill(itoa(getPidOfProcess("baymax-reader")), SIGINT);
    printAsManager("baymax-reader module stopped");
    deleteReaderPipe();  
    
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
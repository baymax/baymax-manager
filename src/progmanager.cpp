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
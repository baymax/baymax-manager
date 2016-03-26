#include "main.h"
#include "console.h"
#include "argsparser.h"
#include "logger.h"
#include "progmanager.h"

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void prosessSigint(int signum);
void registerSignals();

int main(int argc, char* argv[]) {
    registerSignals();
    managerStarted();
    //startReaderModule();///
    startGtkModule();
    startReaderModule();
    startSenderModule();
    consoleMain();
    return 0;
}


void prosessSigint(int signum) {
    printAsManager("Terminate signal reviced...");
    printAsManager("Shutting down all modules...");
    stopGtkModule();
    stopReaderModule();
    stopSenderModule();
    exit(EXIT_SUCCESS);
    /*if (1 == stopAllModules()) {
        printAsManager("All modules stopped succefully!");
    } else {
        printAsManager("Something went wrong!");
    }*/
    
}

void registerSignals() {
    signal(SIGINT, prosessSigint);    
}
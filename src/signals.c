#include "signals.h"
#include "logger.h"
#include "progmanager.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void prosessSigint(int signum) {
    printAsManager("Terminate signal reviced...");
    printAsManager("Shutting down all modules...");
    if (1 == stopAllModules()) {
        printAsManager("All modules stopped succefully!");
    } else {
        printAsManager("Something went wrong!");
    }
    
}

void registerSignals() {
    signal(SIGINT, prosessSigint);    
}
#include "main.h"
#include "console.h"
#include "argsparser.h"
#include "logger.h"
#include "progmanager.h"

int main(int argc, char* argv[]) {
    managerStarted();
    consoleMain();
    return 0;
}
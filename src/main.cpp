#include "main.h"
#include "console.h"
#include "argsparser.h"
#include "logger.h"

int main(int argc, char* argv[]) {
    managerStarted();
    parseArgs(argc, argv);
    return 0;
}
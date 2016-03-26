#ifndef PROGMANAGER_H
#define PROGMANAGER_H

void startAllModules();
void startGtkModule();
void startSenderModule();
void startLoggerModule();
void startConnectionModule();
void startReaderModule();

int stopAllModules();
void stopGtkModule();
void stopSenderModule();
void stopLoggerModule();
void stopConnectionModule();
void stopReaderModule();

char* getPidOfProcess(const char *programName);

#endif // PROGMANAGER_H
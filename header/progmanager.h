#ifndef PROGMANAGER_H
#define PROGMANAGER_H

void startAllModules();
void startUiModule();
void startSenderModule();
void startLoggerModule();
void startConnectionModule();

void stopAllModules();
void stopUiModule();
void stopSenderModule();
void stopLoggerModule();
void stopConnectionModule();

char* getPidOfProcess(const char *programName);

#endif // PROGMANAGER_H
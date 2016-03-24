#ifndef LOGGER_H
#define LOGGER_H

void managerStarted();
void printAsManager(const char* s);
void printAsGtk(const char* s);
void printAsSender(const char* s);
void printAsLogger(const char* s);
void printAsConnection(const char* s);
void printAsReader(const char* s);
char* managerText();
char* gtkText();
char* senderText();
char* loggerText();
char* connectionText();
char* readerText();

void reportError(unsigned char EMSG, int err);


#endif // LOGGER_H
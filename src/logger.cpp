#include "logger.h"

#include "logger.h"
#include "stdio.h"

#include <time.h>

char text[50];

unsigned char managerLoggerOn = 1;
unsigned char gtkLoggerOn = 1;
unsigned char senderLoggerOn = 1;
unsigned char loggerLoggerOn = 1;
unsigned char connectionLoggerOn = 1;
unsigned char readerLoggerOn = 1;

void managerStarted() {
	//char *msg = "[baymax-manager] Started"
	//printf("[baymax-manager] Started");
	printAsManager("Good morning sir !");
}

void printAsManager(const char* s) {
	if (managerLoggerOn) {
		char text [100];
		char *managerT = managerText();
		snprintf(text, 100, "%s %s", managerT, s);
		printf("%s\n", text);
	}
}

void printAsGtk(const char* s) {
	if (gtkLoggerOn) {
		char text [200];
		snprintf(text, 200, "%s %s",  gtkText(), s);
		printf("%s\n", text);	
	}
}

void printAsSender(const char* s) {
	if (senderLoggerOn) {
		char text [200];
		snprintf(text, 200, "%s %s",  senderText(), s);
		printf("%s\n", text);
	}
}

void printAsLogger(const char* s) {
	if (loggerLoggerOn) {
		char text [200];
		snprintf(text, 200, "%s %s",  loggerText(), s);
		printf("%s\n", text);
	}
}

void printAsConnection(const char* s) {
	if (connectionLoggerOn) {
		char text [200];
		snprintf(text, 200, "%s %s",  connectionText(), s);
		printf("%s\n", text);
	}
}

void printAsReader(const char* s) {
	if (readerLoggerOn) {
		char text[200];
		snprintf(text, 200, "%s %s",  readerText(), s);
		printf("%s\n", text);	
	}
}

char* managerText() {	
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(text, sizeof(text)-1, "[baymax-manager -- %d-%m-%Y %H:%M]", t);
	return text;	
}

char* gtkText() {
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(text, sizeof(text)-1, "[baymax-gtk -- %d-%m-%Y %H:%M]", t);
	return text;	
}

char* senderText() {
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(text, sizeof(text)-1, "[baymax-sender -- %d-%m-%Y %H:%M]", t);
	return text;
}

char* loggerText() {
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(text, sizeof(text)-1, "[baymax-logger -- %d-%m-%Y %H:%M]", t);
	return text;   
}

char* connectionText() {
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(text, sizeof(text)-1, "[baymax-connection -- %d-%m-%Y %H:%M]", t);
	return text;   
}

char* readerText() {
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(text, sizeof(text)-1, "[baymax-reader -- %d-%m-%Y %H:%M]", t);
	return text; 	
}


void reportError(unsigned char EMSG, int err) {
    
    
}

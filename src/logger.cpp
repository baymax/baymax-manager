#include "logger.h"
#include "stdio.h"

#include <time.h>

char text[50];

void managerStarted() {
	//char *msg = "[baymax-manager] Started"
	//printf("[baymax-manager] Started");
	printAsManager("Good morning sir !");
}

void printAsManager(const char* s) {
	char text [100];
	char *managerT = managerText();
	snprintf(text, 100, "%s %s", managerT, s);
	printf("%s\n", text);
}

char* managerText() {	
	time_t now = time(NULL);
	struct tm *t = localtime(&now);
	strftime(text, sizeof(text)-1, "[baymax-manager -- %d-%m-%Y %H:%M]", t);
	return text;	
}
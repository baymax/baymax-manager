#include "console.h"
#include "progmanager.h"

#include <stdio.h>

void consoleMain() {
	char cmd;
	while(1) {
		//printAllCommands();
		scanf("%d", &cmd);
		switch(cmd) {
			case 1:
				printStartCommands();
				scanf("%d", &cmd);
				switch(cmd) {
					case 1:
						startUiModule();
					break;
					case 2:
						startSenderModule();
					break;
					case 3:
						startLoggerModule();
					break;
					case 4:
						startConnectionModule();
					break;
					case 0:
						startAllModules();
					break;
				}
			break;
			case 2:
				printStopCommands();	
				scanf("%d", &cmd);
				switch(cmd) {
					case 1:
						stopUiModule();
					break;
					case 2:
						stopSenderModule();
					break;
					case 3:
						stopLoggerModule();
					break;
					case 4:
						stopConnectionModule();
					break;
					case 0:
						stopAllModules();
					break;
				}
			break;
			case 3:
		
			break;
			case 4:
		
			break;        
		}
	} 
}

void printAllCommands() {
	printf("1. Start module\n");
	printf("2. Stop module\n");
	
}

void printStartCommands() {
	printf("1. baymax-gtk\n");
	printf("2. baymax-sender\n");
	printf("3. baymax-logger\n");
	printf("4. baymax-connection\n");
}

void printStopCommands() {
	printf("1. baymax-gtk\n");
	printf("2. baymax-sender\n");
	printf("3. baymax-logger\n");
	printf("4. baymax-connection\n");	
}
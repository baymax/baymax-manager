#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

#include "progmanager.h"
#include "logger.h"
#include "pipe.h"
#include "errormsg.h"

#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>


unsigned char gtkRunning = 0;
unsigned char senderRunning = 0;
unsigned char loggerRunning = 0;
unsigned char connectionRunning = 0;
unsigned char readerRunning = 0;

pid_t gtkModulePid;
pid_t senderModulePid;
pid_t loggerModulePid;
pid_t connectionModulePid;
pid_t readerModulePid;

void startAllModules() {
	startGtkModule();
	startSenderModule();
	startLoggerModule();
	startConnectionModule();
	startReaderModule();
}

void startGtkModule() {
	//createGtkPipe();
	mkfifo(gtkPipePathOutput, 0666);
	mkfifo(gtkPipePathInput, 0666);
	mkfifo(gtkPipePathError, 0666);
	gtkModulePid = fork();
	if (gtkModulePid >= 0) {
		if (gtkModulePid == 0) {
			int fd;
			fd = open(gtkPipePathOutput, O_WRONLY);
			if (fd > -1) {
				//dup2(fd, STDOUT_FILENO);
				if (execl("/usr/bin/baymax-gtk", NULL) < 0) {
					reportError(GTK_PROGRAM_STATING_FAILED, errno);
				}
				printAsManager("Gtk is dead!");
		   }
		} else {
			printAsManager("gtk process created");
			openGtkOutputPipe();
		}
	} else {
		reportError(GTK_PROCESS_CREATION_FAILED, errno);
		printAsManager("gtk process creation failed");
	}
}

void startSenderModule() {
	mkfifo(senderPipePathInput, 0666);
	mkfifo(senderPipePathOutput, 0666);
	mkfifo(senderPipePathError, 0666);
	senderModulePid = fork();
	if (senderModulePid >= 0) {
		if (senderModulePid == 0) {
			int fd;
			fd = open(senderPipePathOutput, O_WRONLY);
			if (fd > -1) {
				if (execl("/usr/bin/baymax-sender", NULL) < 0) {
					reportError(SENDER_PROCESS_CREATION_FAILED, errno);
				}
				printAsManager("Sender is dead");
			}
		} else {
			printAsManager("sender process created");
			openSenderOutputPipe();
		}
	} else {
		reportError(SENDER_PROGRAM_STARTING_FAILED, errno);
		printAsManager("sender process creation failed");
	}
}

void startLoggerModule() {
	char text[100];
	createLoggerPipe();
	snprintf(text, 100, "baymax-logger > %s < %s &", loggerPipePathOutput, loggerPipePathInput);
	system(text);
	printAsManager("baymax-logger module started!!");    
}

void startConnectionModule() {
	char text[100];
	createConnectionPipe();
	snprintf(text, 100, "baymax-connection > %s < %s &", connectionPipePathOutput,connectionPipePathInput);
	system(text);
	printAsManager("baymax-connection module started!!");   
}

void startReaderModule() {
	mkfifo(readerPipePathInput, 0666);
	mkfifo(readerPipePathOutput, 0666);
	mkfifo(readerPipePathError, 0666);
	readerModulePid = fork();
	if (readerModulePid >= 0) {
		if (readerModulePid == 0) {
			int fd;
			fd = open(readerPipePathOutput, O_WRONLY);
			if (fd > -1) {
				//dup2(fd, STDOUT_FILENO);
				if (execl("/usr/bin/baymax-reader", NULL) < 0) {
					reportError(READER_PROGRAM_STARTING_FAILED, errno);
				}
		   }
		} else {
			printAsManager("reader process created");
			openReaderOutputPipe();
		}
	} else {
		reportError(READER_PROCESS_CREATION_FAILED, errno);
		printAsManager("reader process creation failed");
	}
	printAsManager("baymax-reader module started!!");
}

int stopAllModules() {
	stopGtkModule(); //
	stopSenderModule();
	stopLoggerModule();
	stopConnectionModule();
}

void stopGtkModule() {
	printAsManager("Stopping baymax-gtk module...");
	kill(gtkModulePid, SIGKILL);
	printAsManager("baymax-gtk module stopped");
	unlink(gtkPipePathInput);
	unlink(gtkPipePathError);
	unlink(gtkPipePathOutput);
	//deleteGtkPipe();
}

void stopSenderModule() {
	printAsManager("Stopping baymax-sender module...");
	kill(senderModulePid, SIGKILL);
	printAsManager("baymax-sender module stopped");    
	unlink(senderPipePathOutput);
	unlink(senderPipePathInput);
	unlink(senderPipePathError);
}

void stopLoggerModule() {
	printAsManager("Stopping baymax-logger module...");
	char text[50];
	snprintf(text, 50, "kill %s", getPidOfProcess("baymax-logger"));
	system(text);
	printAsManager("baymax-logger module stopped");   
	deleteLoggerPipe();
}

void stopConnectionModule() {
	printAsManager("Stopping baymax-connection module...");
	char text[50];
	snprintf(text, 50, "kill %s", getPidOfProcess("baymax-connection"));
	system(text);
	printAsManager("baymax-connection module stopped");
	deleteConnectionPipe();   
}

void stopReaderModule() {
	printAsManager("Stopping baymax-reader module...");
	kill(readerModulePid, SIGKILL);
	printAsManager("baymax-reader module stopped");
	unlink(readerPipePathOutput);
	unlink(readerPipePathInput);
	unlink(readerPipePathError); 
	
}

char* getPidOfProcess(const char *programName) {
	int fd;
	char text[50];
	char buf[20];
	char *getPidPathOutput = "/tmp/baymax-getpid";
	mkfifo(getPidPathOutput , 0666);
	snprintf(text, 50, "pidof %s > %s &", programName, getPidPathOutput);
	system(text);
	fd = open(getPidPathOutput, O_RDONLY);
	read(fd, buf, 20);
	return buf;
	
}
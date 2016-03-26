#include "pipe.h"

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include "logger.h"
#include "errormsg.h"


// Pipe paths

const char *gtkPipePathOutput = "/tmp/baymax-gtk-output";
const char *gtkPipePathInput = "/tmp/baymax-gtk";
const char *gtkPipePathError = "/tmp/baymax-gtk-error";

const char *senderPipePathOutput = "/tmp/baymax-sender-output";
const char *senderPipePathInput = "/tmp/baymax-sender";
const char *senderPipePathError = "/tmp/baymax-sender-error";

const char *loggerPipePathOutput = "/tmp/baymax-logger-output";
const char *loggerPipePathInput = "/tmp/baymax-logger";

const char *connectionPipePathOutput = "/tmp/baymax-connection-output";
const char *connectionPipePathInput = "/tmp/baymax-connection";

const char *readerPipePathOutput = "/tmp/baymax-reader-output";
const char *readerPipePathInput = "/tmp/baymax-reader";
const char *readerPipePathError = "/tmp/baymax-reader-error";

// Pipe filedescriptions

int gtkPipeOutputFd;
int gtkPipeInputFd;
int gtkPipeErrorFd;

int senderPipeOutputFd;

int readerPipeOutputFd;
int readerPipeInputFd;
int readerPipeErrorFd;



pthread_t gtkReaderThreadId;
pthread_t gtkErrorReaderThreadId;
pthread_t senderReaderThreadId;
pthread_t loggerReaderThreadId;
pthread_t connectionReaderThreadId;
pthread_t readerReaderThreadId;
pthread_t readerErrorReaderThreadId;


unsigned char runningGtkReaderRunning = 1;
unsigned char runningSenderReaderRunning = 1;
unsigned char runningLoggerReaderRunning = 1;
unsigned char runningConnectionReaderRunning = 1;
unsigned char readerReaderRunning = 1;
unsigned char errorReaderRunning = 1;

void createGtkPipe() {
	mkfifo(gtkPipePathInput, 0666);
	mkfifo(gtkPipePathOutput, 0666);
	mkfifo(gtkPipePathError, 0666);
}

void createSenderPipe() {
	mkfifo(senderPipePathInput, 0666);
	mkfifo(senderPipePathOutput, 0666);
	mkfifo(senderPipePathError, 0666);
}

void createLoggerPipe() {
	int err;
	mkfifo(loggerPipePathInput, 0666);
	mkfifo(loggerPipePathOutput, 0666);
	err = pthread_create(&loggerReaderThreadId, NULL, &loggerOutputReader, NULL);
	if (err != 0) {
		printAsManager("Cant create logger pipe :((!");
	}
}

void createConnectionPipe() {
	int err;
	mkfifo(connectionPipePathInput, 0666);
	mkfifo(connectionPipePathOutput, 0666);
	err = pthread_create(&connectionReaderThreadId, NULL, &connectionOutputReader, NULL);
	if (err != 0) {
		printAsManager("Cant create connection pipe :((!");
	} 
}

void createReaderPipe() {
	mkfifo(readerPipePathInput, 0666);
	mkfifo(readerPipePathOutput, 0666);
	mkfifo(readerPipePathError, 0666);
}

// Pipe opening and closing

// gtk
int openGtkOutputPipe() {
	gtkPipeOutputFd = open(gtkPipePathOutput, O_RDONLY);
	if (gtkPipeOutputFd < 0) {
		reportError(GTK_OUTPUT_PIPE_OPENING_FAILED, errno);
		return -1;
	}
	int err;
	err = pthread_create(&gtkReaderThreadId, NULL, &gtkOutputReader, NULL);
	if (err != 0) {
		reportError(GTK_OUTPUT_THREAD_CREATING_FAILED, errno);
		return GTK_OUTPUT_THREAD_CREATING_FAILED;
		//printAsManager("Cant create connection pipe :((!");
	}
	return gtkPipeOutputFd;
}

int closeGtkOutputPipe() {
	if (close(gtkPipeOutputFd) < 0) {
		reportError(GTK_ERROR_PIPE_OPENING_FAILED , errno);
		return GTK_ERROR_PIPE_OPENING_FAILED;
	}
	return 0;
}


int openGtkErrorPipe() {
	gtkPipeErrorFd = open(gtkPipePathError, O_RDONLY);
	if (gtkPipeErrorFd < 0) {
		reportError(GTK_ERROR_PIPE_OPENING_FAILED, errno);
		return GTK_ERROR_PIPE_OPENING_FAILED;
	}
	int err;
	err = pthread_create(&gtkErrorReaderThreadId, NULL, &gtkErrorReader, NULL);
	if (err != 0) {
		reportError(GTK_ERROR_THREAD_CREATING_FAILED , errno);
		return GTK_ERROR_THREAD_CREATING_FAILED ;
		//printAsManager("Cant create connection pipe :((!");
	}
	return 0;
}

int closeGtkErrorPipe() {
	if (close(readerPipeOutputFd) < 0) {
		reportError(READER_ERROR_PIPE_CLOSING_FAILED, errno);
		return READER_ERROR_PIPE_CLOSING_FAILED;
	}
	return 0;	
}

int openSenderOutputPipe() {
	//
	senderPipeOutputFd = open(senderPipePathOutput, O_RDONLY);
	if (senderPipeOutputFd < 0) {
		reportError(SENDER_OUTPUT_PIPE_OPENING_FAILED, errno);
		return SENDER_OUTPUT_PIPE_OPENING_FAILED;
	}
	return 0;
}

int closeSenderOutputPipe() {
	if (close(senderPipeOutputFd) < 0) {
		reportError(SENDER_OUTPUT_PIPE_CLOSING_FAILED, errno);
		return SENDER_OUTPUT_PIPE_CLOSING_FAILED;
	}
}

int openReaderOutputPipe() {
	readerPipeOutputFd = open(readerPipePathOutput, O_RDONLY);
	if (readerPipeOutputFd < 0) {
		reportError(READER_OUTPUT_PIPE_OPENING_FAILED, errno);
		return READER_OUTPUT_PIPE_OPENING_FAILED;
	}
	int err;
	err = pthread_create(&readerReaderThreadId, NULL, &readerOutputReader, NULL);
	if (err != 0) {
		reportError(READER_OUTPUT_THREAD_CREATING_FAILED, errno);
		return READER_OUTPUT_THREAD_CREATING_FAILED;
		//printAsManager("Cant create connection pipe :((!");
	}
	return 0;
}

int closeReaderOutputPipe() {
	if (close(readerPipeOutputFd) < 0) {
		reportError(READER_OUTPUT_PIPE_OPENING_FAILED, errno);
		return READER_OUTPUT_PIPE_OPENING_FAILED;
	}
	return 0;
}

int openReaderErrorPipe() {
	readerPipeErrorFd = open(readerPipePathError, O_RDONLY);
	if (readerPipeErrorFd < 0) {
		reportError(READER_ERROR_PIPE_OPENING_FAILED, errno);
		return READER_ERROR_PIPE_OPENING_FAILED;
	}
	int err;
	err = pthread_create(&readerErrorReaderThreadId, NULL, &readerErrorReader, NULL);
	if (err != 0) {
		reportError(READER_ERROR_THREAD_CREATING_FAILED , errno);
		return READER_ERROR_THREAD_CREATING_FAILED ;
		//printAsManager("Cant create connection pipe :((!");
	}
	return 0;
}

int closeReaderErrorPipe() {
	if (close(readerPipeOutputFd) < 0) {
		reportError(READER_ERROR_PIPE_CLOSING_FAILED, errno);
		return READER_ERROR_PIPE_CLOSING_FAILED;
	}
	return 0;	
}


// Module input simulations

void simulateReaderInput() {
	
}

// Pipe file deletion

void deleteGtkPipe() {
	runningGtkReaderRunning = 0;
	unlink(gtkPipePathOutput);
	unlink(gtkPipePathInput);
	unlink(gtkPipePathError);
}

void deleteSenderPipe() {
	runningSenderReaderRunning = 0;
	unlink(senderPipePathOutput);
	unlink(senderPipePathInput);
	unlink(senderPipePathError);
}

void deleteLoggerPipe() {
	runningLoggerReaderRunning = 0;
	unlink("/tmp/baymax-logger-output");
	unlink("/tmp/baymax-logger");
}

void deleteConnectionPipe() {
	runningConnectionReaderRunning = 0;
	unlink("/tmp/baymax-connection-output");
	unlink("/tmp/baymax-connection");
}

void deleteReaderPipe() {
	readerReaderRunning = 0;
	unlink(readerPipePathOutput);
	unlink(readerPipePathInput);
	unlink(readerPipePathError);
}


// Output Reader workers

void* gtkOutputReader(void* data) {
	char buf[100];
	int bytesRead;
	while(gtkPipeOutputFd > -1) {
		bytesRead = read(gtkPipeOutputFd, buf, 100);
		if (bytesRead > 0) {
			printAsGtk(buf);
			fflush(stdout);
		}
	}	
}

void* gtkErrorReader(void* data) {
	char buf[100];
	int bytesRead;
	while(gtkPipeErrorFd > -1) {
		bytesRead = read(gtkPipeErrorFd, buf, 100);
		if (bytesRead > 0) {
			printAsGtk(buf);
			fflush(stdout);
		}
	}	
}

void* senderOutputReader(void* data) {
	int fd;
	char buf[100];
	fd = open(senderPipePathOutput, O_RDONLY);
	read(fd, buf, 100);
	printAsSender(buf);
}

void* loggerOutputReader(void* data) {  
	int fd;
	char buf[100];
	fd = open(loggerPipePathOutput, O_RDONLY);
	read(fd, buf, 100);
	printAsLogger(buf);
}

void* connectionOutputReader(void* data) {
	int fd;
	char buf[100];
	fd = open(connectionPipePathOutput, O_RDONLY);
	read(fd, buf, 100);
	printAsConnection(buf);
}

void *readerOutputReader(void* data) {
	char buf[100];
	int bytesRead;
	while(readerPipeOutputFd > -1) {
		bytesRead = read(readerPipeOutputFd, buf, 100);
		if (bytesRead > 0) {
			printAsReader(buf);
			fflush(stdout);
		}
	}	
}

void *readerErrorReader(void* data) {
	char buf[100];
	int bytesRead;
	while(readerPipeErrorFd > -1) {
		bytesRead = read(readerPipeErrorFd, buf, 100);
		if (bytesRead > 0) {
			//printAsReader(buf);
			printf("%d", buf[0]);
			fflush(stdout);
		}
	}
}
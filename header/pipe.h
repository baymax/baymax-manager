#ifndef PIPE_H
#define PIPE_H

//#define gtkPipePathInput = "/tmp/baymax-gtk";

//char * senderPipePath = "/tmp/baymax-sender";

void createGtkPipe();
void createSenderPipe();
void createLoggerPipe();
void createConnectionPipe();

void* gtkOutputReader(void* data);
void* senderOutputReader(void* data);
void* loggerOutputReader(void* data);
void* connectionOutputReader(void* data);

char *getGtkInputPipe();
char *getGtkOutputPipe();
char *getSenderInputPipe();
char *getSenderOutputPipe();
char *getLoggerInputPipe();
char *getLoggerOutputPipe();
char *getConnectionInputPipe();
char *getConnectionOutputPipe();

#endif // PIPE_H
#ifndef PIPE_H
#define PIPE_H

extern const char *gtkPipePathOutput;
extern const char *gtkPipePathInput;
extern const char *gtkPipePathError;

extern const char *senderPipePathOutput;
extern const char *senderPipePathInput;
extern const char *senderPipePathError;

extern const char *loggerPipePathOutput;
extern const char *loggerPipePathInput;

extern const char *connectionPipePathOutput;
extern const char *connectionPipePathInput;

extern const char *readerPipePathOutput;
extern const char *readerPipePathInput;
extern const char *readerPipePathError;


extern int gtkPipeOutputFd;
extern int gtkPipeInputFd;
extern int gtkPipeErrorFd;

extern int readerPipeOutputFd;
extern int readerPipeInputFd;
extern int readerPipeErrorFd;

void createGtkPipe();
void createSenderPipe();
void createLoggerPipe();
void createConnectionPipe();
void createReaderPipe();

void deleteGtkPipe();
void deleteSenderPipe();
void deleteLoggerPipe();
void deleteConnectionPipe();
void deleteReaderPipe();

void* gtkOutputReader(void* data);
void* gtkErrorReader(void* data);

void* senderOutputReader(void* data);
void* loggerOutputReader(void* data);
void* connectionOutputReader(void* data);

int openGtkOutputPipe();
int openSenderOutputPipe();
int openReaderOutputPipe();

int closeGtkOutputPipe();
int closeSenderOutputPipe();
int closeReaderOutputPipe();

int openGtkErrorPipe();
int openReaderErrorPipe();

int closeGtkErrorPipe();
int closeReaderErrorPipe();

void simulateGtkInput();
void simulateReaderInput();

const char *getReaderOutputPipe();
const char *getReaderInputPipe();
const char *getReaderErrorPipe();

void *readerOutputReader(void* data);
void *readerErrorReader(void* data);

#endif // PIPE_H
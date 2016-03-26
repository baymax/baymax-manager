#ifndef ERRORMSG_H
#define ERRORMSG_H

const unsigned char READER_OUTPUT_PIPE_OPENING_FAILED = 1;
const unsigned char READER_OUTPUT_PIPE_CLOSING_FAILED = 2;
const unsigned char READER_OUTPUT_THREAD_CREATING_FAILED = 3;

const unsigned char READER_ERROR_PIPE_OPENING_FAILED = 4;
const unsigned char READER_ERROR_PIPE_CLOSING_FAILED = 5;
const unsigned char READER_ERROR_THREAD_CREATING_FAILED = 6;

const unsigned char GTK_OUTPUT_PIPE_OPENING_FAILED = 7;
const unsigned char GTK_OUTPUT_PIPE_CLOSING_FAILED = 8;
const unsigned char GTK_OUTPUT_THREAD_CREATING_FAILED = 9;

const unsigned char GTK_ERROR_PIPE_OPENING_FAILED = 10;
const unsigned char GTK_ERROR_PIPE_CLOSING_FAILED = 11;
const unsigned char GTK_ERROR_THREAD_CREATING_FAILED = 12;

const unsigned char GTK_PROCESS_CREATION_FAILED = 13;
const unsigned char GTK_PROGRAM_STATING_FAILED = 14;

const unsigned char READER_PROCESS_CREATION_FAILED = 15;
const unsigned char READER_PROGRAM_STARTING_FAILED = 16;

const unsigned char SENDER_OUTPUT_PIPE_OPENING_FAILED = 17;
const unsigned char SENDER_OUTPUT_PIPE_CLOSING_FAILED = 18;

const unsigned char SENDER_PROCESS_CREATION_FAILED = 19;
const unsigned char SENDER_PROGRAM_STARTING_FAILED = 20;

#endif // ERRORMSG_H
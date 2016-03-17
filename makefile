CC = gcc

CFLAGS =  -Iheader/
LDFLAGS = -pthread
HEADER_DIR = header/
SRC_DIR = src/
OBJ_DIR = obj/
BIN_DIR = executable/

HEADER_FILES = $(HEADER_DIR)*.h
SOURCE_FILES = $(SRC_DIR)*.cpp
OBJ_FILES = $(OBJ_DIR)*.o

EXECUTABLE = baymax

ALL: $(EXECUTABLE) connection logger sender ui

$(OBJ_DIR)progmanager.o: $(SRC_DIR)progmanager.cpp $(HEADER_DIR)progmanager.h $(OBJ_DIR)logger.o $(OBJ_DIR)pipe.o
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)pipe.o: $(SRC_DIR)pipe.cpp $(HEADER_DIR)pipe.h $(OBJ_DIR)logger.o
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)logger.o: $(SRC_DIR)logger.cpp $(HEADER_DIR)logger.h
	$(CC) -c -o $@ $< $(CFLAGS)


$(OBJ_DIR)argsparser.o: $(SRC_DIR)argsparser.cpp $(HEADER_DIR)argsparser.h
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(OBJ_DIR)console.o: $(SRC_DIR)console.cpp $(HEADER_DIR)console.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)main.o: $(SRC_DIR)main.cpp $(HEADER_DIR)main.h $(OBJ_DIR)console.o $(OBJ_DIR)argsparser.o $(OBJ_DIR)logger.o $(OBJ_DIR)progmanager.o
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXECUTABLE): $(OBJ_DIR)main.o
	$(CC) $(LDFLAGS) $(OBJ_FILES) -o $(BIN_DIR)$(EXECUTABLE)
	
clean:
	rm $(OBJ_FILES)

run:
	./$(BIN_DIR)$(EXECUTABLE)

debug: $(EXECUTABLE) run

install: $(EXECUTABLE)
	cp $(BIN_DIR)$(EXECUTABLE) /bin/
	chmod +x /bin/$(EXECUTABLE)
	

connection: testprogs/connection.c
	gcc testprogs/connection.c -o $(BIN_DIR)baymax-connection
	cp $(BIN_DIR)baymax-connection /bin/
	chmod +x /bin/baymax-connection

sender: testprogs/sender.c
	gcc testprogs/sender.c -o $(BIN_DIR)baymax-sender
	cp $(BIN_DIR)baymax-sender /bin/
	chmod +x /bin/baymax-sender

logger: testprogs/logger.c
	gcc testprogs/logger.c -o $(BIN_DIR)baymax-logger
	cp $(BIN_DIR)baymax-logger /bin/
	chmod +x /bin/baymax-logger

ui: testprogs/ui.c
	gcc testprogs/ui.c -o $(BIN_DIR)baymax-gtk
	cp $(BIN_DIR)baymax-gtk /bin/
	chmod +x /bin/baymax-gtk
	
cleanbin:
	rm $(BIN_DIR)* 
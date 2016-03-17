CC = g++


LIBS = `pkg-config --libs gtk+-3.0` -std=c++11

CFLAGS = `pkg-config --cflags gtk+-3.0` -std=c++11 -Iheader/
LDFLAGS = `pkg-config --libs gtk+-3.0`

HEADER_DIR = header/
SRC_DIR = src/
OBJ_DIR = obj/

HEADER_FILES = $(HEADER_DIR)*.h
SOURCE_FILES = $(SRC_DIR)*.cpp
OBJ_FILES = $(OBJ_DIR)*.o

EXECUTABLE = baymax

ALL: $(EXECUTABLE)

$(OBJ_DIR)console.o: $(SRC_DIR)console.cpp $(HEADER_DIR)console.
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DIR)main.o: $(SRC_DIR)main.cpp $(HEADER_DIR)main.h
	$(CC) -c -o $@ $< $(CFLAGS)

$(EXECUTABLE): $(OBJ_DIR)main.o
	$(CC) $(LDFLAGS) $(OBJ_FILES) -o executable/$(EXECUTABLE)
	
clean:
	rm $(OBJ_FILES)

run:
	./executable/$(EXECUTABLE)

debug: $(EXECUTABLE) run

install: $(EXECUTABLE)
	cp executable/$(EXECUTABLE) /bin/
	chmod +x /bin/$(EXECUTABLE)
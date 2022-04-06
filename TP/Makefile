CC = g++
CFLAGS = -std=c++11 -Wall
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/main.o $(OBJ)/Entidade.o $(OBJ)/Fita.o $(OBJ)/Heap.o $(OBJ)/memlog.o
HDRS = $(INC)/Entidade.h $(INC)/Fita.h $(INC)/Heap.h $(INC)/memlog.h $(INC)/msgassert.h 
CFLAGS = -std=c++11 -Wall -I$(INC)

EXE = $(BIN)/main

all: $(EXE)

$(BIN)/main: $(OBJS)
	$(CC) -g -o $(BIN)/main $(OBJS) $(LIBS)

$(OBJ)/main.o: $(HDRS) $(SRC)/main.cpp
	$(CC) $(CFLAGS) -g -o $(OBJ)/main.o -c $(SRC)/main.cpp 

$(OBJ)/Entidade.o: $(HDRS) $(SRC)/Entidade.cpp
	$(CC) $(CFLAGS) -g -o $(OBJ)/Entidade.o -c $(SRC)/Entidade.cpp 

$(OBJ)/Fita.o: $(HDRS) $(SRC)/Fita.cpp
	$(CC) $(CFLAGS) -g -o $(OBJ)/Fita.o -c $(SRC)/Fita.cpp 

$(OBJ)/Heap.o: $(HDRS) $(SRC)/Heap.cpp
	$(CC) $(CFLAGS) -g -o $(OBJ)/Heap.o -c $(SRC)/Heap.cpp 

$(OBJ)/memlog.o: $(HDRS) $(SRC)/memlog.c
	$(CC) $(CFLAGS) -g -o $(OBJ)/memlog.o -c $(SRC)/memlog.c
	
clean:
	rm $(EXE) $(OBJS)
# Variables
CC = gcc
CFLAGS = -Wall
LIBS = -lncurses
OBJ = main.o game.o frontend.o
TARGET = main

# Build the target
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAGS) $(LIBS)

# Compile source files into object files
%.o: %.c %.h
	$(CC) $< -c $(CFLAGS)

main.o: main.c
	$(CC) main.c -c $(CFLAGS)

# Clean up object files and the target
clean:
	rm -rf *.o

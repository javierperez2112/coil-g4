# Variables (compiler, options, libraries, object files, target)
CC = gcc
CFLAGS = -Wall
OBJ = main.o game.o frontend.o
TARGET = main

# Build main file
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(CFLAGS)

# Compile source into object
%.o: %.c %.h
	$(CC) $< -c $(CFLAGS)

main.o: main.c
	$(CC) main.c -c $(CFLAGS)

# Erase object files
clean:
	rm -rf *.o

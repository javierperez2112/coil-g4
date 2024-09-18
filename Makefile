# Variables (compiler, options, libraries, object files, target)
CC = gcc
FLAGS = -Wall
OBJ = main.o game.o frontend.o
TARGET = main

# Build main file
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(FLAGS)

# Compile source into object
%.o: %.c %.h
	$(CC) $< -c $(FLAGS)

# Erase object files
clean:
	rm -rf *.o

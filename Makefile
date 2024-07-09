main: main.o game.o frontend.c
	gcc main.o game.o frontend.o -o main -Wall
    
main.o: main.c
	gcc main.c -c -Wall

game.o: game.c game.h
	gcc game.c -c -Wall
	
frontend.o: frontend.c frontend.h
	gcc frontend.c -c -Wall

clean:
	rm -rf *.o
    

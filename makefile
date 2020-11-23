main: main.o
	gcc -o main main.c

clean:
	rm *.o
	rm main

run:
	./main

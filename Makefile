main: main.c
	gcc -Wall -Wextra -std=c11 main.c -o main

clean:
	rm *.o main
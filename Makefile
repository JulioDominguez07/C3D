all:
	gcc -o demo main.c C3D.c -lm -Wall -Wextra
	./demo
clean:
	rm demo
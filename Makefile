all:
	mkdir -p bin
	g++ -Wall -o bin/opensnap src/opensnap.c -lX11 -lXrandr
clean:
	rm bin/opensnap
